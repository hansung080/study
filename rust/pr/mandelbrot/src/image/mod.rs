pub mod band;

use std::fs::File;
use std::path::Path;
use std::slice::ChunksMut;
use anyhow::Result;
use image::codecs::png::PngEncoder;
use image::{ExtendedColorType, ImageEncoder, ImageFormat};
use num::Complex;
use crate::complex::ComplexArea;
use crate::escape_times;
use crate::image::band::Bands;
use crate::utils;
use crate::utils::progress::Progresser;

const PIXEL_BLACK: u8 = 0;
const PIXEL_WHITE: u8 = 255;

pub struct Image {
    pixels: Vec<u8>, // grayscale pixels
    width: usize,
    height: usize,
    area: ComplexArea,
}

impl Image {
    pub fn new(width: usize, height: usize, area: ComplexArea) -> Self {
        Image {
            pixels: vec![0; width * height],
            width,
            height,
            area
        }
    }

    pub fn from_str(size: &str, upper_left: &str, lower_right: &str) -> Self {
        let (width, height) = utils::parse_pair(size, 'x').expect("failed to parse image size");
        Image::new(width, height, ComplexArea::from_str(upper_left, lower_right))
    }

    pub fn render(&mut self, quiet: bool) {
        render(&mut self.pixels, (self.width, self.height), &self.area, quiet);
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

    pub fn bands(&mut self, rows_per_band: usize) -> Bands {
        Bands::new(self, rows_per_band)
    }

    pub fn chunks_mut(&mut self, chunk_size: usize) -> ChunksMut<'_, u8> {
        self.pixels.chunks_mut(chunk_size)
    }

    pub fn width(&self) -> usize {
        self.width
    }

    pub fn height(&self) -> usize {
        self.height
    }
}

pub fn pixel_to_complex((width, height): (usize, usize), (x, y): (usize, usize), area: &ComplexArea) -> Complex<f64> {
    Complex {
        re: area.upper_left().re + x as f64 * area.width() / width as f64,
        im: area.upper_left().im - y as f64 * area.height() / height as f64,
    }
}

pub fn render(pixels: &mut [u8], (width, height): (usize, usize), area: &ComplexArea, quiet: bool) {
    let mut p = if !quiet {
        Some(Progresser::new(width * height, 10))
    } else {
        None
    };

    for y in 0..height {
        for x in 0..width {
            if let Some(ref mut p) = p {
                p.progress();
            }

            let complex = pixel_to_complex((width, height), (x, y), area);
            pixels[y * width + x] = match escape_times(complex, 255) {
                // If `complex` is not a member of Mandelbrot set,
                // a pixel will be, the farther the distance from Mandelbrot set, the closer to white.
                Some(times) => PIXEL_WHITE - times as u8,
                // If `complex` is a member of Mandelbrot set, a pixel will be black.
                None => PIXEL_BLACK,
            }
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn pixel_to_complex_test() {
        assert_eq!(pixel_to_complex(
            (100, 200),
            (25, 175),
            &ComplexArea::new(Complex { re: -1.0, im: 1.0 }, Complex { re: 1.0, im: -1.0 }),
        ), Complex { re: -0.5, im: -0.75 });
    }
}
