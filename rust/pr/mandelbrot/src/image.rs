use std::fs::File;
use std::io;
use std::io::Write;
use std::path::Path;
use anyhow::Result;
use image::codecs::png::PngEncoder;
use image::{ExtendedColorType, ImageEncoder, ImageFormat};
use num::Complex;
use crate::complex::ComplexArea;
use crate::escape_times;
use crate::utils::parse_pair;
use crate::utils::progress::Progresser;

const PIXEL_BLACK: u8 = 0;
const PIXEL_WHITE: u8 = 255;

pub struct Image {
    pixels: Vec<u8>, // grayscale pixels
    width: usize,
    height: usize,
}

impl Image {
    pub fn new(width: usize, height: usize) -> Self {
        Image {
            pixels: vec![0; width * height],
            width,
            height,
        }
    }

    pub fn from_str(size: &str) -> Self {
        let (width, height) = parse_pair(size, 'x').expect("failed to parse image size");
        Image::new(width, height)
    }

    pub fn render(&mut self, area: &ComplexArea) {
        let mut p = Progresser::new(self.width * self.height, 10);
        print!("rendering... ");
        io::stdout().flush().unwrap();
        for y in 0..self.height {
            for x in 0..self.width {
                p.progress();
                let complex = self.pixel_to_complex((x, y), area);
                self.pixels[y * self.width + x] = match escape_times(complex, 255) {
                    // If `complex` is not a member of Mandelbrot set,
                    // a pixel will be, the farther the distance from Mandelbrot set, the closer to white.
                    Some(times) => PIXEL_WHITE - times as u8,
                    // If `complex` is a member of Mandelbrot set, a pixel will be black.
                    None => PIXEL_BLACK,
                }
            }
        }
        println!();
    }

    fn pixel_to_complex(&self, (x, y): (usize, usize), area: &ComplexArea) -> Complex<f64> {
        Complex {
            re: area.upper_left.re + x as f64 * area.width() / self.width as f64,
            im: area.upper_left.im - y as f64 * area.height() / self.height as f64,
        }
    }

    pub fn save(&self, path: impl AsRef<Path>) -> Result<()> {
        let path = path.as_ref();
        if let None = path.extension() {
            image::save_buffer_with_format(path, &self.pixels, self.width as u32, self.height as u32, ExtendedColorType::L8, ImageFormat::Png)?;
        } else {
            image::save_buffer(path, &self.pixels, self.width as u32, self.height as u32, ExtendedColorType::L8)?;
        }
        Ok(())
    }

    pub fn save_png(&self, path: impl AsRef<Path>) -> Result<()> {
        let file = File::create(path)?;
        PngEncoder::new(file).write_image(&self.pixels, self.width as u32, self.height as u32, ExtendedColorType::L8)?;
        Ok(())
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn image_pixel_to_complex() {
        assert_eq!(Image::new(100, 200).pixel_to_complex(
            (25, 175),
            &ComplexArea::new(Complex { re: -1.0, im: 1.0 }, Complex { re: 1.0, im: -1.0 }),
        ), Complex { re: -0.5, im: -0.75 });

        assert_eq!(Image::from_str("100x200").pixel_to_complex(
            (25, 175),
            &ComplexArea::from_str("-1.0,1.0", "1.0,-1.0"),
        ), Complex { re: -0.5, im: -0.75 });
    }
}
