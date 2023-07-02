pub trait Pushed<T> {
    fn pushed(&mut self, value: T) -> &mut Self;
    fn into_pushed(self, value: T) -> Self;
}

impl Pushed<char> for String {
    fn pushed(&mut self, value: char) -> &mut Self {
        self.push(value);
        self
    }

    fn into_pushed(mut self, value: char) -> Self {
        self.push(value);
        self
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn pushed() {
        let cases = [
            (String::from("a"), ' ', "a "),
            (String::from("a"), '\n', "a\n"),
            (String::from("a"), 'b', "ab"),
        ];

        for (mut s, ch, expected) in cases.clone() {
            assert_eq!(expected, s.pushed(ch));
        }

        for (s, ch, expected) in cases {
            assert_eq!(expected, s.into_pushed(ch));
        }
    }
}
