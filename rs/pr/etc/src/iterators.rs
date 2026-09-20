use std::iter;
use std::iter::Peekable;
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

pub fn fibonacci() -> impl Iterator<Item=usize> {
    let mut state = (0, 1);
    iter::from_fn(move || {
        let term = state.0;
        state = (state.1, state.0 + state.1);
        Some(term)
    })
}

// Return the escape time of the Mandelbrot set.
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

pub fn extract_some_values<T>(options: Vec<Option<T>>) -> Vec<T> {
    options.into_iter()
        .flatten()
        .collect()
}

pub fn to_uppercase1(s: &str) -> String {
    s.chars()
        .map(char::to_uppercase)
        .flatten()
        .collect()
}

pub fn to_uppercase2(s: &str) -> String {
    s.chars()
        .flat_map(char::to_uppercase)
        .collect()
}

pub fn parse_number<I>(tokens: &mut Peekable<I>) -> u32
where
    I: Iterator<Item=char>,
{
    let mut num = 0;
    loop {
        match tokens.peek() {
            Some(token) if token.is_digit(10) => {
                num = num * 10 + token.to_digit(10).unwrap();
            },
            _ => return num,
        }
        tokens.next();
    }
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
    fn fibonacci() {
        assert_eq!(super::fibonacci().take(9).collect::<Vec<_>>(),
                   vec![0, 1, 1, 2, 3, 5, 8, 13, 21]);
    }

    #[test]
    fn escape_time() {
        let cases = [
            (-1.2, 0.35, 255, Some(9)),
            (-1.0, 0.2, 255, None),
        ];
        for (re, im, limit, expected) in cases {
            assert_eq!(escape_time1(Complex { re, im }, limit), expected);
            assert_eq!(escape_time2(Complex { re, im }, limit), expected);
        }
    }

    #[test]
    fn drain() {
        let mut outer = "Earth".to_string();
        let inner = String::from_iter(outer.drain(1..4));
        assert_eq!(outer, "Eh");
        assert_eq!(inner, "art");
    }

    #[test]
    fn extract_some_values() {
        let values = super::extract_some_values(
            vec![None, Some("day"), None, Some("one")]
        );
        assert_eq!(values, vec!["day", "one"]);
    }

    #[test]
    fn to_uppercase() {
        let cases = [
            ("Hello, Rust v1.85.0 ~!!", "HELLO, RUST V1.85.0 ~!!"),
            ("große", "GROSSE"),
        ];

        for (s, expected) in cases {
            assert_eq!(to_uppercase1(s), expected);
            assert_eq!(to_uppercase2(s), expected);
        }
    }

    #[test]
    fn parse_number() {
        let mut chars = "226153980,1766319049".chars().peekable();
        assert_eq!(super::parse_number(&mut chars), 226153980);
        assert_eq!(chars.next(), Some(','));
        assert_eq!(super::parse_number(&mut chars), 1766319049);
        assert_eq!(chars.next(), None);
    }
}
