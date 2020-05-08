use std::io;
use std::cmp::Ordering;
use rand::Rng;

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
    
        match guess.cmp(&answer) {
            Ordering::Less => println!("{} is LESS than the answer.", guess),
            Ordering::Greater => println!("{} is GREATER than the answer.", guess),
            Ordering::Equal => {
                println!("{} is CORRECT. Congratulations~!!", guess);
                break;
            }
        }
    }
}
