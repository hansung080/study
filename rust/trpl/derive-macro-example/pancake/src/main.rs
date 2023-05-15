use hello_macro::HelloMacro;
use hello_macro_derive::HelloMacro;

#[derive(HelloMacro)]
struct Pancake;

fn main() {
    Pancake::hello_macro(); // Hello, macro! My name is Pancake.
}
