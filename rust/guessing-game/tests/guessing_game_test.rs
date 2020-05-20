mod common;

use guessing_game;
use guessing_game::Result;

#[test]
fn check_not_number() {
    common::setup();
    assert_eq!(Result::NotNumber("You must input a number."), guessing_game::check("a", 50));
}

#[test]
fn check_out_of_range_below() {
    assert_eq!(Result::OutOfRange("Number must be between 1 and 100."), guessing_game::check("0", 50));
}

#[test]
fn check_out_of_range_over() {
    assert_eq!(Result::OutOfRange("Number must be between 1 and 100."), guessing_game::check("101", 50));
}

#[test]
fn check_less() {
    assert_eq!(Result::Less("Your guess is LESS than the answer."), guessing_game::check("49", 50));
}

#[test]
fn check_greater() {
    assert_eq!(Result::Greater("Your guess is GREATER than the answer."), guessing_game::check("51", 50));
}

#[test]
fn check_equal() {
    assert_eq!(Result::Equal("Your guess is CORRECT. Congratulations~!!"), guessing_game::check("50", 50));
}