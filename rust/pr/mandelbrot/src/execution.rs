use std::io;
use std::io::Write;
use clap::Parser;
use crate::args::Args;
use crate::image::Image;

pub struct Executor {
    args: Args,
    image: Image,
}

impl Executor {
    pub fn new() -> Self {
        let mut args = Args::parse();
        if args.threads == 0 { args.threads = num_cpus::get() };
        if !args.quiet { println!("{args:?}"); }
        let image = Image::from_str(&args.image_size, &args.upper_left, &args.lower_right);
        Executor { args, image }
    }

    pub fn execute(&mut self) {
        if self.args.threads == 1 {
            self.render_by_single_thread();
        } else {
            self.render_by_scoped_thread();
        }
        self.image.save(&self.args.image_path).expect("failed to save image");
    }

    fn render_by_single_thread(&mut self) {
        if !self.args.quiet {
            print!("rendering by single thread... ");
            io::stdout().flush().unwrap();
        }
        self.image.render(self.args.quiet);
        if !self.args.quiet { println!(); }
    }

    fn render_by_scoped_thread(&mut self) {
        let quiet = self.args.quiet;
        if !quiet { println!("rendering by {} scoped threads...", self.args.threads); }
        crossbeam::scope(|spawner| {
            let rows_per_band = self.image.height().div_ceil(self.args.threads);
            for (i, mut band) in self.image.bands(rows_per_band).enumerate() {
                spawner.spawn(move |_| {
                    band.render(true);
                    if !quiet { println!("thread {i} done."); }
                });
            }
        }).unwrap();
    }
}