use std::cmp::Ordering;
use std::io;
use std::io::Write;
use rand::Rng;
use guessing_game;

fn main() {
    println!("#######################################");
    println!("##### Welcome to Guessing Game~!! #####");
    println!("#######################################");

    let answer = rand::thread_rng().gen_range(1, 101);
    loop {
        print!("> Guess the number between 1 and 100: ");
        io::stdout().flush().unwrap();

        let mut guess = String::new();
        io::stdin().read_line(&mut guess).expect("failed to read the number");
        let guess = guess.trim();
        if guessing_game::can_exit(guess) {
            println!("Bye~!! See you again.");
            break;
        }

        match guessing_game::compare(guess, answer) {
            Ok(ordering) => match ordering {
                Ordering::Less => println!("Sorry. {} is less than the answer.", guess),
                Ordering::Greater => println!("Sorry. {} is greater than the answer.", guess),
                Ordering::Equal => {
                    println!("Congratulations~!! The answer is {}.", answer);
                    break;
                }
            }
            Err(e) => println!("Error. {}.", e),
        }
    }
}
