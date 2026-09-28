use std::collections::HashMap;

// WORSE: Key hashing occurs 2 or 3 times per iteration.
pub fn char_counts1(s: &str) -> HashMap<char, u32> {
    let mut counts = HashMap::new();
    for c in s.chars() {
        if !counts.contains_key(&c) {
            counts.insert(c, 0);
        }
        let count = counts.get_mut(&c).unwrap();
        *count += 1;
    }
    counts
}

// BAD: Key hashing occurs 1 or 2 times per iteration.
pub fn char_counts2(s: &str) -> HashMap<char, u32> {
    let mut counts = HashMap::new();
    for c in s.chars() {
        let count = counts.get_mut(&c);
        match count {
            Some(count) => *count += 1,
            None => {
                counts.insert(c, 1);
            },
        }
    }
    counts
}

// GOOD: Key hashing occurs 1 time per iteration.
pub fn char_counts3(s: &str) -> HashMap<char, u32> {
    let mut counts = HashMap::new();
    for c in s.chars() {
        let count = counts.entry(c).or_insert(0);
        *count += 1;
    }
    counts
}

// GOOD: Key hashing occurs 1 time per iteration.
pub fn char_counts4(s: &str) -> HashMap<char, u32> {
    let mut counts = HashMap::new();
    for c in s.chars() {
        // let count = counts.entry(c).or_insert_with(|| 0);
        let count = counts.entry(c).or_insert_with(<u32 as Default>::default);
        *count += 1;
    }
    counts
}

// GOOD: Key hashing occurs 1 time per iteration.
pub fn char_counts5(s: &str) -> HashMap<char, u32> {
    let mut counts = HashMap::new();
    for c in s.chars() {
        let count = counts.entry(c).or_default();
        *count += 1;
    }
    counts
}

// GOOD: Key hashing occurs 1 time per iteration.
pub fn char_counts6(s: &str) -> HashMap<char, u32> {
    let mut counts = HashMap::new();
    for c in s.chars() {
        counts.entry(c)
            .and_modify(|count| *count += 1)
            .or_insert(1);
    }
    counts
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn char_counts() {
        let cases = [
            ("", HashMap::from([])),
            ("a", HashMap::from([('a', 1)])),
            ("apple", HashMap::from([('a', 1), ('p', 2), ('l', 1), ('e', 1)])),
            ("banana", HashMap::from([('b', 1), ('a', 3), ('n', 2)])),
        ];

        for (s, expected) in cases {
            assert_eq!(char_counts1(s), expected);
            assert_eq!(char_counts2(s), expected);
            assert_eq!(char_counts3(s), expected);
            assert_eq!(char_counts4(s), expected);
            assert_eq!(char_counts5(s), expected);
            assert_eq!(char_counts6(s), expected);
        }
    }
}
