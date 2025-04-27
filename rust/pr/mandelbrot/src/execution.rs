use std::io;
use std::io::Write;
use crate::args::Args;
use crate::complex::ComplexArea;
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
        let img_width = img.width();
        let img_height = img.height();
        let rows_per_band = img_height.div_ceil(self.args.threads);
        let bands: Vec<&mut [u8]> = img.chunks_mut(rows_per_band * img_width).collect();
        if !self.args.quiet { println!("rendering by {} scoped threads...", bands.len()); }
        crossbeam::scope(|spawner| {
            for (i, band) in bands.into_iter().enumerate() {
                let top = rows_per_band * i;
                let width = img_width;
                let height = band.len() / img_width;
                let upper_left = crate::image::pixel_to_complex((img_width, img_height), (0, top), area);
                let lower_right = crate::image::pixel_to_complex((img_width, img_height), (width, top + height), area);
                spawner.spawn(move |_| {
                    crate::image::render(band, (width, height), &ComplexArea::new(upper_left, lower_right), true);
                    if !self.args.quiet { println!("{i}th thread done.") }
                });
            }
        }).unwrap();
    }
}