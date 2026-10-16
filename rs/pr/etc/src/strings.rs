use std::borrow::Cow;
use std::env;

// BAD: An unnecessary allocation is made for the default string.
pub fn get_name1() -> String {
    // `USER` is for macOS and Linux, `USERNAME` is for Windows.
    env::var("USER")
        .unwrap_or("whoever you are".to_string())
}

// GOOD: The default string is borrowed, avoiding an unnecessary allocation.
//       Cow defers cloning of the borrowed data until ownership or mutable access is required
//       (e.g. cow.into_owned() and cow.to_mut()).
pub fn get_name2() -> Cow<'static, str> {
    env::var("USER")
        .map(|name| Cow::Owned(name))
        .unwrap_or(Cow::Borrowed("whoever you are"))
}

// GOOD: same as `get_name2`.
pub fn get_name3() -> Cow<'static, str> {
    env::var("USER")
        .map(|name| name.into())
        .unwrap_or("whoever you are".into())
}

pub fn get_title(key: char) -> Option<&'static str> {
    match key {
        'B' | 'b' => Some("B.S."),  // Bachelor of Science
        'E' | 'e' => Some("Esq."),  // Esquire
        'J' | 'j' => Some("Jr."),   // Junior
        'M' | 'm' => Some("M.S."),  // Master of Science
        'P' | 'p' => Some("Sc.D."), // Doctor of Science
        'S' | 's' => Some("Sr."),   // Senior
        _ => None,
    }
}

#[cfg(test)]
mod tests {
    use std::fmt::Write;
    use super::*;

    #[test]
    fn get_name_and_title() {
        // --- Ownership Or Mutable Access Not Required ---
        //
        //   get_name1: The default string allocation has already occurred.
        //   get_name2: The default string allocation will not occur.
        //   get_name3: same as `get_name2`.
        //
        println!("# CASE 1: Greetings, {}!", get_name1());
        println!("# CASE 2: Greetings, {}!", get_name2());
        println!("# CASE 3: Greetings, {}!", get_name3());

        // --- Mutable Access Required ---
        //
        //   get_name1: The default string allocation has already occurred.
        //   get_name2: The default string allocation will occur only when `to_mut` is called.
        //   get_name3: same as `get_name2`.
        //
        let mut name = get_name1();
        if let Some(title) = get_title('E') {
            name.push_str(", ");
            name.push_str(title);

            name += ", "; // not required to import std::ops::AddAssign
            name += title;

            write!(name, ", {title}").unwrap(); // required to import std::fmt::Write
        }
        println!("# CASE 4: Greetings, {name}!");

        let mut name = get_name2();
        if let Some(title) = get_title('E') {
            name.to_mut().push_str(", ");
            name.to_mut().push_str(title);

            name += ", ";
            name += title;

            write!(name.to_mut(), ", {title}").unwrap();
        }
        println!("# CASE 5: Greetings, {name}!");

        let mut name = get_name3();
        if let Some(title) = get_title('E') {
            name.to_mut().push_str(", ");
            name.to_mut().push_str(title);

            name += ", ";
            name += title;

            write!(name.to_mut(), ", {title}").unwrap();
        }
        println!("# CASE 6: Greetings, {name}!");
    }
}
