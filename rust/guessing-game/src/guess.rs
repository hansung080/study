mod error;

use std::cmp::Ordering;
use std::cmp::PartialEq;
use self::error::Error;

#[derive(Debug)]
pub struct Guess {
    value: i32,
}

impl Guess {
    pub fn new(value: i32) -> Result<Self, Error> {
        if value < 1 || value > 100 {
            return Err(Error::new("Number must be between 1 and 100."));
        }

        Ok(Self { value })
    }

    #[allow(unused)]
    pub fn new_panic(value: i32) -> Self {
        if value < 1 || value > 100 {
            panic!("Number must be between 1 and 100.");
        }

        Self { value }
    }

    #[allow(unused)]
    pub fn value(&self) -> i32 {
        self.value
    }

    pub fn cmp(&self, other: &i32) -> Ordering {
        self.value.cmp(other)
    }
}

impl PartialEq for Guess {
    fn eq(&self, other: &Self) -> bool {
        self.value == other.value
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn guess_new_between() {
        let guess = Guess::new(50);
        assert_eq!(Ok(Guess { value: 50 }), guess);
    }

    #[test]
    fn guess_new_less() {
        let guess = Guess::new(0);
        assert_eq!(Err(Error::new("Number must be between 1 and 100.")), guess);
    }

    #[test]
    fn guess_new_greater() {
        let guess = Guess::new(101);
        assert_eq!(Err(Error::new("Number must be between 1 and 100.")), guess);
    }

    #[test]
    fn guess_new_panic_between() {
        let guess = Guess::new_panic(50);
        assert_eq!(Guess { value: 50 }, guess);
    }
    
    #[test]
    #[should_panic(expected = "Number must be between 1 and 100.")]
    fn guess_new_panic_less() {
        Guess::new_panic(0);
    }

    #[test]
    #[should_panic(expected = "Number must be between 1 and 100.")]
    fn guess_new_panic_greater() {
        Guess::new_panic(101);
    }

    #[test]
    fn guess_cmp_less() {
        let guess = match Guess::new(9) {
            Ok(guess) => guess,
            Err(error) => panic!("{}", error.msg()),
        };
        assert_eq!(Ordering::Less, guess.cmp(&10));
    }

    #[test]
    fn guess_cmp_greater() {
        let guess = match Guess::new(11) {
            Ok(guess) => guess,
            Err(error) => panic!("{}", error.msg()),
        };
        assert_eq!(Ordering::Greater, guess.cmp(&10))
    }

    #[test]
    fn guess_cmp_equal() {
        let guess = match Guess::new(10) {
            Ok(guess) => guess,
            Err(error) => panic!("{}", error.msg()),
        };
        assert_eq!(Ordering::Equal, guess.cmp(&10))
    }

    #[test]
    #[ignore]
    fn guess_ignore() {
        assert_ne!(3, 1 + 1);
    }
}
