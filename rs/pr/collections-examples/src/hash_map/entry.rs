use std::collections::HashMap;

// NOTE: This function is inefficient, because HashMap query occurs 2 times which is unnecessary.
pub fn char_frequency1(s: &str) -> HashMap<char, u32> {
    let mut result = HashMap::new();
    for c in s.chars() {
        if !result.contains_key(&c) {
            result.insert(c, 0);
        }
        let freq = result.get_mut(&c).unwrap();
        *freq += 1;
    }
    result
}

pub fn char_frequency2(s: &str) -> HashMap<char, u32> {
    let mut result = HashMap::new();
    for c in s.chars() {
        let freq = result.get_mut(&c);
        match freq {
            Some(freq) => *freq += 1,
            None => {
                result.insert(c, 1);
            },
        }
    }
    result
}

pub fn char_frequency3(s: &str) -> HashMap<char, u32> {
    let mut result = HashMap::new();
    for c in s.chars() {
        let freq = result.entry(c).or_insert(0);
        *freq += 1;
    }
    result
}

pub fn char_frequency4(s: &str) -> HashMap<char, u32> {
    let mut result = HashMap::new();
    for c in s.chars() {
        // let freq = result.entry(c).or_insert_with(|| 0);
        let freq = result.entry(c).or_insert_with(<u32 as Default>::default);
        *freq += 1;
    }
    result
}

pub fn char_frequency5(s: &str) -> HashMap<char, u32> {
    let mut result = HashMap::new();
    for c in s.chars() {
        let freq = result.entry(c).or_default();
        *freq += 1;
    }
    result
}

pub fn char_frequency6(s: &str) -> HashMap<char, u32> {
    let mut result = HashMap::new();
    for c in s.chars() {
        result.entry(c)
            .and_modify(|freq| *freq += 1)
            .or_insert(1);
    }
    result
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn char_frequency() {
        let cases = [
            ("", HashMap::from([])),
            ("a", HashMap::from([('a', 1)])),
            ("apple", HashMap::from([('a', 1), ('p', 2), ('l', 1), ('e', 1)])),
            ("banana", HashMap::from([('b', 1), ('a', 3), ('n', 2)])),
        ];

        for (s, expected) in cases {
            assert_eq!(char_frequency1(s), expected);
            assert_eq!(char_frequency2(s), expected);
            assert_eq!(char_frequency3(s), expected);
            assert_eq!(char_frequency4(s), expected);
            assert_eq!(char_frequency5(s), expected);
            assert_eq!(char_frequency6(s), expected);
        }
    }
}