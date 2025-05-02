use std::slice::ChunksMut;
use crate::complex::ComplexArea;
use crate::image;
use crate::image::Image;

pub struct Band<'a> {
    pub pixels: &'a mut [u8],
    pub width: usize,
    pub height: usize,
    pub area: ComplexArea,
}

pub struct Bands<'a> {
    img_width: usize,
    img_height: usize,
    area: &'a ComplexArea,
    bands: ChunksMut<'a, u8>,
    index: usize,
    rows_per_band: usize,
}

impl<'a> Bands<'a> {
    pub fn new(img: &'a mut Image, area: &'a ComplexArea, rows_per_band: usize) -> Self {
        Bands {
            img_width: img.width,
            img_height: img.height,
            area,
            // let bands: Vec<&mut [u8]> = img.chunks_mut(rows_per_band * img.width).collect();
            bands: img.chunks_mut(rows_per_band * img.width),
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
                let width = self.img_width;
                let height = band.len() / self.img_width;
                let upper_left = image::pixel_to_complex(
                    (self.img_width, self.img_height),
                    (0, top),
                    self.area
                );
                let lower_right = image::pixel_to_complex(
                    (self.img_width, self.img_height),
                    (width, top + height),
                    self.area
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