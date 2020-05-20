mod guess;

use std::cmp::Ordering;
use crate::guess::Guess;
use std::cmp::PartialEq;

#[derive(Debug)]
pub enum Result {
    NotNumber(&'static str),
    OutOfRange(&'static str),
    Less(&'static str),
    Greater(&'static str),
    Equal(&'static str),
}

impl PartialEq for Result {
    fn eq(&self, other: &Self) -> bool {
        match (self, other) {
            (Result::NotNumber(left), Result::NotNumber(right)) => left == right,
            (Result::OutOfRange(left), Result::OutOfRange(right)) => left == right,
            (Result::Less(left), Result::Less(right)) => left == right,
            (Result::Greater(left), Result::Greater(right)) => left == right,
            (Result::Equal(left), Result::Equal(right)) => left == right,
            _ => false,
        }
    }
}

pub fn check(guess: &str, answer: i32) -> Result {
    let guess: i32 = match guess.trim().parse() {
        Ok(num) => num,
        Err(_) => {
            return Result::NotNumber("You must input a number.");
        },
    };

    let guess = match Guess::new(guess) {
        Ok(guess) => guess,
        Err(error) => {
            return Result::OutOfRange(error.msg());
        }
    };

    match guess.cmp(&answer) {
        Ordering::Less => Result::Less("Your guess is LESS than the answer."),
        Ordering::Greater => Result::Greater("Your guess is GREATER than the answer."),
        Ordering::Equal => Result::Equal("Your guess is CORRECT. Congratulations~!!"),
    }
}
