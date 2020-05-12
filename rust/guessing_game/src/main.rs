mod guess {
    use std::cmp::Ordering;

    pub struct Guess {
        value: i32,
    }

    impl Guess {
        pub fn new(value: i32) -> Result<Guess, Error> {
            if value < 1 || value > 100 {
                return Err(Error::new(String::from("Number must be between 1 and 100")))
            }

            Ok(Guess { value })
        }

        pub fn value(&self) -> i32 {
            self.value
        }

        pub fn cmp(&self, other: &i32) -> Ordering {
            self.value.cmp(other)
        }
    }

    pub struct Error {
        msg: String,
    }

    impl Error {
        pub fn new(msg: String) -> Error {
            Error { msg }
        }

        pub fn msg(&self) -> &String {
            &self.msg
        }
    }
}

use std::io;
use std::cmp::Ordering;
use rand::Rng;
use crate::guess::Guess;

fn main() {
    println!("###################################");
    println!("########## Guessing Game ##########");
    println!("###################################");

    let answer = rand::thread_rng().gen_range(1, 101);
    //println!("Answer: {}", answer);

    loop {
        println!("Guess a number.");
        let mut guess = String::new();
        io::stdin().read_line(&mut guess).expect("Failed to read a number");
        let guess: i32 = match guess.trim().parse() {
            Ok(num) => num,
            Err(_) => {
                println!("You must input a number.");
                continue;
            },
        };
    
        let guess = match Guess::new(guess) {
            Ok(guess) => guess,
            Err(error) => {
                println!("{}.", error.msg());
                continue;
            }
        };

        match guess.cmp(&answer) {
            Ordering::Less => println!("{} is LESS than the answer.", guess.value()),
            Ordering::Greater => println!("{} is GREATER than the answer.", guess.value()),
            Ordering::Equal => {
                println!("{} is CORRECT. Congratulations~!!", guess.value());
                break;
            }
        }
    }
}
