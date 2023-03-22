use std::env;
use std::process;
use minigrep::Config;

const USAGE: &str = "\
Usage) CASE_INSENSITIVE=1 minigrep <query> <filename>";

fn main() {
    let args: Vec<String> = env::args().collect();
    let config = Config::new(&args).unwrap_or_else(|err| {
        eprintln!("failed to create config: {}", err);
        eprintln!("{}", USAGE);
        process::exit(1);
    });

    if let Err(e) = minigrep::run(config) {
        eprintln!("failed to run minigrep: {}", e);
        process::exit(1);
    }
}