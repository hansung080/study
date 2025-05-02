use std::io;
use std::io::Write;
use crate::args::Args;
use crate::complex::ComplexArea;
use crate::image;
use crate::image::Image;

pub struct Executor {
    args: Args,
}

impl Executor {
    pub fn new(mut args: Args) -> Self {
        if args.threads == 0 { args.threads = num_cpus::get() };
        if !args.quiet { println!("{args:?}"); }
        Executor { args }
    }

    pub fn execute(&self) {
        let mut img = Image::from_str(&self.args.image_size);
        let area = ComplexArea::from_str(&self.args.upper_left, &self.args.lower_right);
        if self.args.threads == 1 {
            self.render_by_single_thread(&mut img, &area);
        } else {
            self.render_by_scoped_thread(&mut img, &area);
        }
        img.save(&self.args.image_path).expect("failed to save image");
    }

    fn render_by_single_thread(&self, img: &mut Image, area: &ComplexArea) {
        if !self.args.quiet {
            print!("rendering by single thread... ");
            io::stdout().flush().unwrap();
        }
        img.render(&area, self.args.quiet);
        if !self.args.quiet { println!(); }
    }

    fn render_by_scoped_thread(&self, img: &mut Image, area: &ComplexArea) {
        if !self.args.quiet { println!("rendering by {} scoped threads...", self.args.threads); }
        let rows_per_band = img.height().div_ceil(self.args.threads);
        crossbeam::scope(|spawner| {
            for (i, band) in img.bands(area, rows_per_band).enumerate() {
                spawner.spawn(move |_| {
                    image::render(band.pixels, (band.width, band.height), &band.area, true);
                    if !self.args.quiet { println!("thread {i} done.") }
                });
            }
        }).unwrap();
    }
}