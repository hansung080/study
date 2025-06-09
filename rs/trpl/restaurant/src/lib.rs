mod front_of_house;
mod back_of_house;

pub use crate::front_of_house::hosting; // absolute path (recommended)
// use self::front_of_house::hosting;   // relative path
use crate::back_of_house::Breakfast;
use crate::back_of_house::Appetizer;

pub fn eat_at_restaurant() {
    // crate::front_of_house::hosting::add_to_waitlist(); // absolute path
    // front_of_house::hosting::add_to_waitlist();        // relative path
    hosting::add_to_waitlist(); // use path

    // Choose Breakfast.
    let mut meal = Breakfast::summer("rye");
    meal.toast = String::from("wheat");
    // meal.seasonal_fruit = String::from("blueberry"); // compile error: field `seasonal_fruit` of struct `Breakfast` is private

    // Choose Appetizer.
    let _appetizer1 = Appetizer::Soup;
    let _appetizer2 = Appetizer::Salad;
}