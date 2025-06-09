use hello::HelloName;
use hello_derive::HelloName;

#[derive(HelloName)]
struct Pancake;

fn main() {
    Pancake::hello_name(); // Hello, Pancake!
}
