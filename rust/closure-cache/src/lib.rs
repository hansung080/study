mod cache;

use std::env;
use std::thread;
use std::time::Duration;
use cache::Cacher;

pub struct Config {
    count: i32,
}

impl Config {
    pub fn new() -> Result<Config, &'static str> {
        let mut args = env::args();
        args.next();
        let count = match args.next() {
            Some(arg) => arg,
            None => return Err("<count> argument is missing"),
        };

        let count: i32 = match count.parse() {
            Ok(count) => count,
            Err(_) => return Err("The first argument must be a number"),
        };

        Ok(Config { count })
    }
}

pub fn run(config: Config) -> i32 {
    let mut cacher = Cacher::new(|count| {
        println!("Running expensive operation...");
        thread::sleep(Duration::from_secs(2));
        count
    });
    
    match config.count {
        1 => {
            *cacher.result(&config.count)
        },
        2 => {
            cacher.result(&config.count) + cacher.result(&config.count)
        }
        _ => 0,
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn run_0() {
        assert_eq!(0, run(Config { count: 0 }));
    }

    #[test]
    fn run_1() {
        assert_eq!(1, run(Config { count: 1 }));
    }
    
    #[test]
    fn run_2() {
        assert_eq!(4, run(Config { count: 2 }));
    }
}
