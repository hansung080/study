pub struct Counter {
    current: i32,
    end: i32,
}

impl Counter {
    pub fn new() -> Self {
        Counter {
            current: 0,
            end: i32::MAX,
        }
    }

    pub fn from_range(start: i32, end: i32) -> Self {
        Counter {
            current: start,
            end,
        }
    }
}

impl Iterator for Counter {
    type Item = i32;

    fn next(&mut self) -> Option<Self::Item> {
        if self.current >= self.end {
            return None;
        }
        let result = self.current;
        self.current += 1;
        Some(result)
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn counter_next() {
        let mut counter = Counter::new();
        assert_eq!(counter.next(), Some(0));
        assert_eq!(counter.next(), Some(1));
        assert_eq!(counter.next(), Some(2));
        assert_eq!(counter.next(), Some(3));
        assert_eq!(counter.next(), Some(4));
        assert_eq!(counter.next(), Some(5));

        let mut counter = Counter::from_range(1, 6);
        assert_eq!(counter.next(), Some(1));
        assert_eq!(counter.next(), Some(2));
        assert_eq!(counter.next(), Some(3));
        assert_eq!(counter.next(), Some(4));
        assert_eq!(counter.next(), Some(5));
        assert_eq!(counter.next(), None);
    }

    #[test]
    fn counter_collect() {
        let counter = Counter::new().take(5);
        let v: Vec<i32> = counter.collect();
        assert_eq!(v, vec![0, 1, 2, 3, 4]);

        let counter = Counter::from_range(1, 6);
        let v: Vec<i32> = counter.collect();
        assert_eq!(v, vec![1, 2, 3, 4, 5]);

        let counter = Counter::from_range(-5, 5);
        let v: Vec<i32> = counter.collect();
        assert_eq!(v, vec![-5, -4, -3, -2, -1, 0, 1, 2, 3, 4]);
    }

    #[test]
    fn counter_for() {
        let counter = Counter::from_range(1, 6);
        let mut sum = 0;
        for count in counter {
            sum += count;
        }
        assert_eq!(sum, 15);
    }

    #[test]
    fn counter_fold() {
        let counter = Counter::from_range(1, 6);
        let sum = counter.fold(0, |sum, count| sum + count);
        assert_eq!(sum, 15);
    }

    #[test]
    fn counter_others() {
        let sum: i32 = Counter::from_range(1, 6)
            .zip(Counter::from_range(1, 6).skip(1))
            .map(|(a, b)| a * b)
            .filter(|x| x % 3 == 0)
            .sum();
        assert_eq!(sum, 18);
    }
}
