pub struct I32Range {
    pub start: i32,
    pub end: i32,
}

impl I32Range {
    pub fn new(start: i32, end: i32) -> Self {
        I32Range {
            start,
            end,
        }
    }
}

impl Iterator for I32Range {
    type Item = i32;

    fn next(&mut self) -> Option<Self::Item> {
        if self.start >= self.end {
            return None;
        }
        let result = self.start;
        self.start += 1;
        Some(result)
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn i32_range_collect() {
        let range = I32Range::new(1, 6);
        let v: Vec<i32> = range.collect();
        assert_eq!(v, vec![1, 2, 3, 4, 5]);

        let range = I32Range::new(-5, 5);
        let v: Vec<i32> = range.collect();
        assert_eq!(v, vec![-5, -4, -3, -2, -1, 0, 1, 2, 3, 4]);
    }

    #[test]
    fn i32_range_pi() {
        // Maclaurin series for arctangent:
        //   arctan(x) = Σ<k=0..∞>[[{(-1)^k}{x^(2k+1)}]/(2k+1)]
        //             = x - (x^3)/3 + (x^5)/5 - (x^7)/7 + ...
        //
        //   arctan(1) = Σ<k=0..∞>[{(-1)^k}/(2k+1)]  (Leibniz series for π/4)
        //             = 1 - 1/3 + 1/5 - 1/7 + ...
        //             = π/4
        //
        //   sqrt(3)arctan{1/sqrt(3)} = Σ<k=0..∞>[{(-1)^k}/{(2k+1)3^k}]
        //                            = 1 - 1/(3*3) + 1/(5*3^2) - 1/(7*3^3) + ...
        //                            = π/sqrt(12)
        //
        // Pi approximation:
        //   Σ<k=0..13>[{(-1)^k}/{(2k+1)3^k}]
        //   = 1 - 1/(3*3) + 1/(5*3^2) - 1/(7*3^3) + ... - 1/(27*3^13)
        //   ≈ π/sqrt(12)
        let mut pi = 0.0;
        let mut numerator = 1.0;

        for k in I32Range::new(0, 14) {
            pi += numerator / (2 * k + 1) as f64;
            numerator /= -3.0;
        }
        pi *= f64::sqrt(12.0);
        assert_eq!(pi as f32, std::f32::consts::PI);
    }
}
