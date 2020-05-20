use std::io;
use rand::Rng;
use guessing_game;
use guessing_game::Result;

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
        match guessing_game::check(&guess, answer) {
            Result::NotNumber(msg) => {
                println!("{}", msg);
                continue;
            },
            Result::OutOfRange(msg) => {
                println!("{}", msg);
                continue;
            },
            Result::Less(msg) => {
                println!("{}", msg);
                continue;
            },
            Result::Greater(msg) => {
                println!("{}", msg);
                continue;
            },
            Result::Equal(msg) => {
                println!("{}", msg);
                break;
            },
        }
    }
}
