use std::str::FromStr;
use std::{env, process};

fn main() {
    let mut nums = Vec::new();
    for arg in env::args().skip(1) {
        nums.push(u64::from_str(&arg).expect(&format!("invalid argument: {arg} is not a integer")));
    }

    if nums.len() == 0 {
        eprintln!("Usage: gcd [NUMBERS]...");
        process::exit(1);
    }

    let mut a = nums[0];
    for b in &nums[1..] {
        a = gcd::gcd(a, *b);
    }

    println!("gcd({nums:?}) => {a}");
}
