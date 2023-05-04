use std::cmp::Ordering;

pub type Error = String;

#[derive(PartialEq, Debug)]
pub struct Guess {
    value: i32,
}

impl Guess {
    pub fn new(value: i32) -> Result<Self, Error> {
        if value < 1 || value > 100 {
            return Err(format!("{} is not between 1 and 100", value));
        }
        Ok(Self { value })
    }

    #[allow(unused)]
    pub fn new_with_panic(value: i32) -> Self {
        if value < 1 || value > 100 {
            panic!("{} is not between 1 and 100", value);
        }
        Self { value }
    }

    pub fn from_string(value: &str) -> Result<Self, Error> {
        let value: i32 = match value.parse() {
            Ok(value) => value,
            Err(_) => return Err(format!("{} is not a number", value)),
        };
        Self::new(value)
    }

    #[allow(unused)]
    pub fn value(&self) -> i32 {
        self.value
    }

    pub fn cmp(&self, other: i32) -> Ordering {
        self.value.cmp(&other)
    }
}

#[cfg(test)]
mod tests {
    use rand::Rng;
    use super::*;

    #[test]
    fn guess_new() {
        for value in [1, 50, 100] {
            assert_eq!(Ok(Guess { value }), Guess::new(value));
        }

        for value in [0, 101] {
            assert_eq!(Err(format!("{} is not between 1 and 100", value)), Guess::new(value));
        }
    }

    #[test]
    #[ignore]
    fn guess_new_random() {
        for _ in 1..11 {
            let value = rand::thread_rng().gen_range(1, 101);
            assert_eq!(Ok(Guess { value }), Guess::new(value));
        }
    }

    #[test]
    fn guess_new_with_panic() {
        for value in [1, 50, 100] {
            assert_eq!(Guess { value }, Guess::new_with_panic(value));
        }
    }

    #[test]
    #[should_panic(expected = "is not between 1 and 100")]
    fn guess_new_with_panic_0() {
        Guess::new_with_panic(0);
    }

    #[test]
    #[should_panic(expected = "is not between 1 and 100")]
    fn guess_new_with_panic_101() {
        Guess::new_with_panic(101);
    }

    #[test]
    fn guess_from_string() {
        for value in [1, 50, 100] {
            assert_eq!(Ok(Guess { value }), Guess::from_string(&value.to_string()));
        }

        for value in [0, 101] {
            assert_eq!(Err(format!("{} is not between 1 and 100", value)), Guess::from_string(&value.to_string()));
        }

        assert_eq!(Err(format!("{} is not a number", "a")), Guess::from_string("a"));
    }
}
