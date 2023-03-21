mod common;

use std::cmp::Ordering;
use guessing_game as game;
use common::assert_err;

#[test]
fn can_exit() {
    assert!(game::can_exit("exit"));
    assert!(game::can_exit("quit"));
    assert!(!game::can_exit("50"));
}

#[test]
fn compare() {
    let answer = 50;
    assert_err(game::compare("a", answer), "a should cause the not-number-error");
    assert_err(game::compare("0", answer), "0 should cause the out-of-range-error");
    assert_err(game::compare("101", answer), "101 should cause the out-of-range-error");
    assert_eq!(Ok(Ordering::Less), game::compare("1", answer));
    assert_eq!(Ok(Ordering::Greater), game::compare("100", answer));
    assert_eq!(Ok(Ordering::Equal), game::compare("50", answer));
}
