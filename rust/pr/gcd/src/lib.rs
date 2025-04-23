pub fn gcd_rec(a: u64, b: u64) -> u64 {
    if b == 0 {
        assert_ne!(a, 0, "invalid argument: arguments cannot both be 0");
        return a;
    }
    gcd_rec(b, a % b)
}

pub fn gcd_iter(mut a: u64, mut b: u64) -> u64 {
    assert!(a != 0 || b != 0, "invalid argument: arguments cannot both be 0");
    while b != 0 {
        (a, b) = (b, a % b);
    }
    a
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn gcd_test() {
        let cases = [
            (6, 0, 6),
            (0, 6, 6),
            (24, 10, 2),
            (10, 24, 2),
            (206, 40, 2),
            (14, 15, 1),
            (2 * 3 * 5 * 11 * 17, 3 * 7 * 11 * 13 * 19, 3 * 11),
        ];

        for (a, b, expected) in cases {
            assert_eq!(gcd_rec(a, b), expected, "gcd_rec({a}, {b}) != {expected}");
            assert_eq!(gcd_iter(a, b), expected, "gcd_iter({a}, {b}) != {expected}");
        }
    }

    #[test]
    #[should_panic(expected = "invalid argument: arguments cannot both be 0")]
    fn gcd_rec_error() {
        gcd_rec(0, 0);
    }

    #[test]
    #[should_panic(expected = "invalid argument: arguments cannot both be 0")]
    fn gcd_iter_error() {
        gcd_iter(0, 0);
    }
}