use std::slice::ChunksMut;
use crate::complex::ComplexArea;
use crate::image;
use crate::image::Image;

pub struct Band<'a> {
    pixels: &'a mut [u8],
    width: usize,
    height: usize,
    area: ComplexArea,
}

impl<'a> Band<'a> {
    pub fn render(&mut self, quiet: bool) {
        image::render(self.pixels, (self.width, self.height), &self.area, quiet);
    }
}

pub struct Bands<'a> {
    bands: ChunksMut<'a, u8>,
    width: usize,
    height: usize,
    area: ComplexArea,
    index: usize,
    rows_per_band: usize,
}

impl<'a> Bands<'a> {
    pub fn new(image: &'a mut Image, rows_per_band: usize) -> Self {
        let width= image.width;
        let height= image.height;
        let area = image.area.clone();
        Bands {
            // let bands: Vec<&mut [u8]> = image.chunks_mut(rows_per_band * width).collect();
            bands: image.chunks_mut(rows_per_band * width),
            width,
            height,
            area,
            index: 0,
            rows_per_band,
        }
    }
}

impl<'a> Iterator for Bands<'a> {
    type Item = Band<'a>;

    fn next(&mut self) -> Option<Self::Item> {
        match self.bands.next() {
            Some(band) => {
                let top = self.rows_per_band * self.index;
                let width = self.width;
                let height = band.len() / self.width;
                let upper_left = image::pixel_to_complex(
                    (self.width, self.height),
                    (0, top),
                    &self.area
                );
                let lower_right = image::pixel_to_complex(
                    (self.width, self.height),
                    (width, top + height),
                    &self.area
                );
                self.index += 1;

                Some(Band {
                    pixels: band,
                    width,
                    height,
                    area: ComplexArea::new(upper_left, lower_right),
                })
            },
            None => None,
        }
    }
}