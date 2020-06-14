use std::process;
use state_pattern;
use state_pattern::Config;

const USAGE: &'static str = "\
Usage) state-pattern <pattern>
  * pattern
    - 1: state pattern using conditional
    - 2: state pattern using polymorphism
    - 3: state pattern using type-system\
";

fn main() {
    let config = Config::new().unwrap_or_else(|err| {
        eprintln!("Failed to create config: {}", err);
        eprintln!("{}", USAGE);
        process::exit(1);
    });

    state_pattern::run(config);
}