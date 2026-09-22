pub struct Counter {
    current: i32,
    end: i32,
}

impl Counter {
    pub fn new(start: i32, end: i32) -> Self {
        Counter {
            current: start,
            end
        }
    }
}

impl Iterator for Counter {
    type Item = i32;

    fn next(&mut self) -> Option<Self::Item> {
        if self.current >= self.end {
            return None;
        }
        let current = self.current;
        self.current += 1;
        Some(current)
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn counter_next() {
        let mut counter = Counter::new(1, 6);
        assert_eq!(counter.next(), Some(1));
        assert_eq!(counter.next(), Some(2));
        assert_eq!(counter.next(), Some(3));
        assert_eq!(counter.next(), Some(4));
        assert_eq!(counter.next(), Some(5));
        assert_eq!(counter.next(), None);
    }

    #[test]
    fn counter_collect() {
        let counter = Counter::new(-5, 5);
        let v: Vec<i32> = counter.collect();
        assert_eq!(v, vec![-5, -4, -3, -2, -1, 0, 1, 2, 3, 4]);
    }

    #[test]
    fn counter_for() {
        let counter = Counter::new(1, 6);
        let mut sum = 0;
        for count in counter {
            sum += count;
        }
        assert_eq!(sum, 15);
    }

    #[test]
    fn counter_for_each() {
        let counter = Counter::new(2, 5);
        let mut sum = 0;
        counter.for_each(|count| sum += count);
        assert_eq!(sum, 9);
    }

    #[test]
    fn counter_others() {
        let sum: i32 = Counter::new(1, 6)
            .zip(Counter::new(1, 6).skip(1))
            .map(|(item1, item2)| item1 * item2)
            .filter(|item | item % 3 == 0)
            .sum();
        assert_eq!(sum, 18);
    }
}
