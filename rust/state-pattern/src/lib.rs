use std::env;

mod conditional;
mod polymorphism;
mod type_system;

const PATTERN_CONDITIONAL: i32 = 1;
const PATTERN_POLYMORPHISM: i32 = 2;
const PATTERN_TYPESYSTEM: i32 = 3;

pub struct Config {
    pattern: i32,
}

impl Config {
    pub fn new() -> Result<Config, &'static str> {
        let mut args = env::args();
        args.next();

        let pattern = match args.next() {
            Some(arg) => arg,
            None => return Err("<pattern> not provided"),
        };
        
        let pattern: i32 = match pattern.parse() {
            Ok(pattern) => pattern,
            Err(_) => return Err("<pattern> must be a integer"),
        };

        if pattern < 1 || pattern > 3 {
           return Err("<pattern> must be between 1 and 3");
        }

        Ok(Config { pattern })
    }
}

pub fn run(config: Config) {
    match config.pattern {
        PATTERN_CONDITIONAL => conditional::run(),
        PATTERN_POLYMORPHISM => polymorphism::run(),
        PATTERN_TYPESYSTEM => type_system::run(),
        _ => (),
    }
}
