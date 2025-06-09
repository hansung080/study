use std::env;
use std::process;
use minigrep::Config;

const USAGE: &str = "\
Usage) CASE_INSENSITIVE=1 minigrep <query> <filename>";

fn main() {
    let config = Config::new(env::args()).unwrap_or_else(|err| {
        eprintln!("failed to create config: {}", err);
        eprintln!("{}", USAGE);
        process::exit(1);
    });

    if let Err(e) = minigrep::run(config) {
        eprintln!("failed to run minigrep: {}", e);
        process::exit(1);
    }
}