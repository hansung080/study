mod guess;

use std::cmp::Ordering;
use guess::{Error, Guess};

pub fn can_exit(input: &str) -> bool {
    input.eq("exit") || input.eq("quit")
}

pub fn compare(guess: &str, answer: i32) -> Result<Ordering, Error> {
    let guess = Guess::from_string(guess)?;
    Ok(guess.cmp(answer))
}