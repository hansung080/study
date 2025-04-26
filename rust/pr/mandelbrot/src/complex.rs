use num::Complex;
use crate::utils::parse_complex;

pub struct ComplexArea {
    pub upper_left: Complex<f64>,
    pub lower_right: Complex<f64>,
}

impl ComplexArea {
    pub fn new(upper_left: Complex<f64>, lower_right: Complex<f64>) -> Self {
        ComplexArea { upper_left, lower_right }
    }

    pub fn from_str(upper_left: &str, lower_right: &str) -> Self {
        ComplexArea {
            upper_left: parse_complex(upper_left).expect("failed to parse upper left point"),
            lower_right: parse_complex(lower_right).expect("failed to parse lower right point"),
        }
    }

    pub fn width(&self) -> f64 {
        self.lower_right.re - self.upper_left.re
    }

    pub fn height(&self) -> f64 {
        self.upper_left.im - self.lower_right.im
    }
}