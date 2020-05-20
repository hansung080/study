use std::process;
use minigrep::Config;

const USAGE: &'static str = "Usage) minigrep <query> <filename>";

fn main() {
    let config = Config::new().unwrap_or_else(|err| {
        eprintln!("Failed to create config: {}", err);
        eprintln!("{}", USAGE);
        process::exit(1);
    });

    if let Err(e) = minigrep::run(config) {
        eprintln!("Failed to run application: {}", e);
        process::exit(1);
    }
}
