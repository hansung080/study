use std::iter;
use num::Complex;

// Return the nth triangular number.
pub fn triangle1(n: u32) -> u32 {
    if n == 0 {
        0
    } else {
        n + triangle1(n - 1)
    }
}

pub fn triangle2(n: u32) -> u32 {
    let mut sum = 0;
    for i in 1..=n {
        sum += i;
    }
    sum
}

// Rust inlines `fold` and the closure, then optimizes it into `n * (n + 1) / 2`.
pub fn triangle3(n: u32) -> u32 {
    (1..=n).fold(0, |sum, item| sum + item)
}

// Σ<k=1..n>k = n * (n + 1) / 2
pub fn triangle4(n: u32) -> u32 {
    n * (n + 1) / 2
}

// Return the lengths of `n` line segments whose endpoints are uniformly distributed
// over the interval [0, 1].
pub fn line_segment_lengths(n: usize) -> Vec<f64> {
    iter::from_fn(|| Some((rand::random::<f64>() - rand::random::<f64>()).abs()))
        .take(n)
        .collect()
}

pub fn escape_time1(c: Complex<f64>, limit: usize) -> Option<usize> {
    let mut z = Complex { re: 0.0, im: 0.0 };
    for i in 0..limit {
        if z.norm_sqr() > 4.0 {
            return Some(i);
        }
        z = z * z + c;
    }
    None
}

pub fn escape_time2(c: Complex<f64>, limit: usize) -> Option<usize> {
    let zero = Complex { re: 0.0, im: 0.0 };
    iter::successors(Some(zero), |&z| Some(z * z + c))
        .take(limit)
        .enumerate()
        .find(|(_i, z)| z.norm_sqr() > 4.0)
        .map(|(i, _z)| i)
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn triangle() {
        let cases = [
            (0, 0),
            (1, 1),
            (2, 3),
            (3, 6),
            (4, 10),
            (5, 15),
        ];

        for (n, expected) in cases {
            assert_eq!(triangle1(n), expected);
            assert_eq!(triangle2(n), expected);
            assert_eq!(triangle3(n), expected);
            assert_eq!(triangle4(n), expected);
        }
    }

    #[test]
    fn line_segment_lengths() {
        let lengths = super::line_segment_lengths(5);
        assert_eq!(lengths.len(), 5);
        for length in lengths {
            assert!(0.0 <= length && length <= 1.0);
        }
    }

    #[test]
    fn escape_time() {

    }
}
