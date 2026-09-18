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
}
