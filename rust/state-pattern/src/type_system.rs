mod blog;

use blog::Post;

pub fn run() {
    let mut post = Post::new();
    
    post.add_text("I ate a salad for lunch today.");

    let post = post.request_review();

    let post = post.approve();
    assert_eq!("I ate a salad for lunch today.", post.content());

    println!("State pattern using type-system completed.");
}