use std::process;
use closure_cache::Config;

const USAGE: &'static str = "Usage) closure-cache <count>";

fn main() {
    let config = Config::new().unwrap_or_else(|err| {
        eprintln!("Failed to create config: {}", err);
        eprintln!("{}", USAGE);
        process::exit(1);
    });

    println!("The total count is {}.", closure_cache::run(config));
}