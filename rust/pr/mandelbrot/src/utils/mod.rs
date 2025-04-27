pub mod progress;

use std::str::FromStr;
use std::time::{Duration, Instant};
use num::Complex;

pub fn parse_pair<T: FromStr>(s: &str, sep: char) -> Option<(T, T)> {
    match s.find(sep) {
        Some(index) => {
            match (T::from_str(&s[..index]), T::from_str(&s[index + 1..])) {
                (Ok(left), Ok(right)) => Some((left, right)),
                _ => None,
            }
        },
        None => None,
    }
}

pub fn parse_complex(s: &str) -> Option<Complex<f64>> {
    match parse_pair(s, ',') {
        Some((re, im)) => Some(Complex { re, im }),
        None => None,
    }
}

pub fn elapsed_time(f: impl FnOnce()) -> Duration {
    let start = Instant::now();
    f();
    start.elapsed()
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn parse_pair_test() {
        assert_eq!(parse_pair::<i32>("", ','), None);
        assert_eq!(parse_pair::<i32>("10,", ','), None);
        assert_eq!(parse_pair::<i32>(",10", ','), None);
        assert_eq!(parse_pair::<i32>("10,20a", ','), None);
        assert_eq!(parse_pair::<i32>("10a,20", ','), None);
        assert_eq!(parse_pair::<i32>("10,20", ','), Some((10, 20)));
        assert_eq!(parse_pair::<f64>("0.5x1.5", 'x'), Some((0.5, 1.5)));
    }

    #[test]
    fn parse_complex_test() {
        assert_eq!(parse_complex("1.25,"), None);
        assert_eq!(parse_complex(",-0.0625"), None);
        assert_eq!(parse_complex("1.25,-0.0625"), Some(Complex { re: 1.25, im: -0.0625 }));
    }
}