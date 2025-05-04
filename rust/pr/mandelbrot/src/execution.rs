use std::io;
use std::io::Write;
use clap::Parser;
use crate::args::Args;
use crate::image::Image;
use crate::utils::thread::ScopedThreadPool;

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
            if self.args.thread_pool {
                self.render_by_scoped_thread_pool();
            } else {
                self.render_by_scoped_thread();
            }
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
        if !quiet { println!("rendering by {} threads...", self.args.threads); }
        crossbeam::scope(|scope| {
            let rows_per_band = self.image.height().div_ceil(self.args.threads);
            for (i, mut band) in self.image.bands(rows_per_band).enumerate() {
                scope.spawn(move |_| {
                    band.render(true);
                    if !quiet { println!("thread {i} terminated."); }
                });
            }
        }).unwrap();
    }

    fn render_by_scoped_thread_pool(&mut self) {
        if !self.args.quiet { println!("rendering by {}-sized thread pool...", self.args.threads); }
        crossbeam::scope(|scope| {
            let pool = ScopedThreadPool::new(scope, self.args.threads, self.args.quiet);
            for mut band in self.image.bands(1) {
                pool.execute(move || {
                    band.render(true);
                });
            }
        }).unwrap();
    }
}