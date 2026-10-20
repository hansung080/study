#[cfg(test)]
mod tests {
    use std::hash::{DefaultHasher, Hash, Hasher};
    use unicode_normalization::UnicodeNormalization;

    // Although `Hasher` is designed to accumulate the hash of a sequence of values,
    // the implementation below hashes a single value for simplicity, despite the inefficiency.
    fn hash<T: ?Sized + Hash>(value: &T) -> u64 {
        let mut hasher = DefaultHasher::new();
        value.hash(&mut hasher);
        hasher.finish()
    }

    // Unicode Character Forms
    //
    //   Composed form:
    //     It is closer to traditional text representations,
    //     making it less prone to compatibility issues,
    //     and is suitable for string formatting, such as with Rust's `format!` macro.
    //     For example, `thé` consists of three characters: `t`, `h`, and `é`,
    //     where `é` is a single Unicode character with the code point `U+00E9`.
    //     (e.g. th\u{e9}, Ph\u{1edf})
    //
    //   Decomposed form:
    //     It reveals the underlying structure of the text more clearly,
    //     making it suitable for displaying and searching text.
    //     For example, `thé` consists of four characters: `t`, `h`, `e`, and `\u{301}`,
    //     where `e` is a plain ASCII character without an accent,
    //     and the code point `U+0301` represents the `Combining Acute Accent` character,
    //     which adds an acute accent to the preceding character.
    //     (e.g. the\u{301}, Pho\u{31b}\u{309})
    //
    // Unicode Compatibility Equivalence
    //
    //   For example, the digit `5` (U+0035), the superscript digit `⁵` (U+2075),
    //   and the circled digit `⑤` (U+2464) are distinct Unicode characters
    //   but are compatibility-equivalent.
    //   The ligature `ﬃ` (U+FB03) and the three-character sequence `ffi` are
    //   distinct Unicode representations but are compatibility-equivalent.
    //
    // Unicode Normalization Forms
    //
    //   Canonical normalization does not collapse compatibility-equivalent sequences
    //   into the same normalized form.
    //   Compatibility normalization collapses compatibility-equivalent sequences
    //   into the same normalized form.
    //
    //   NFC (Normalization Form C):   canonical decomposition -> canonical composition
    //   NFD (Normalization Form D):   canonical decomposition
    //   NFKC (Normalization Form KC): compatibility decomposition -> canonical composition
    //   NFKD (Normalization Form KD): compatibility decomposition
    //
    //     Notes:
    //       - The World Wide Web Consortium's `Character Model for the World Wide Web`
    //         recommends using NFC for all content.
    //         (see https://www.w3.org/TR/charmod/)
    //       - The Unicode Standard Annex #31 `Unicode Identifiers and Syntax`
    //         recommends using NFKC for identifiers in programming languages.
    //         (see https://www.unicode.org/reports/tr31/)
    // Notes:
    //   - `thé` is French for tea.
    //   - `Phở` is Vietnamese for noodle soup.

    #[test]
    fn unicode() {
        assert_ne!("th\u{e9}", "the\u{301}");
        assert!("th\u{e9}" > "the\u{301}");
        assert_ne!(hash("th\u{e9}"), hash("the\u{301}"));

        assert_ne!("Ph\u{1edf}", "Pho\u{31b}\u{309}");
        assert!("Ph\u{1edf}" > "Pho\u{31b}\u{309}");
        assert_ne!(hash("Ph\u{1edf}"), hash("Pho\u{31b}\u{309}"));

        assert_ne!("⑤ Diﬃculty", "5 Difficulty");
        assert!("⑤ Diﬃculty" > "5 Difficulty");
        assert_ne!(hash("⑤ Diﬃculty"), hash("5 Difficulty"));
    }

    #[test]
    fn unicode_normalization() {
        assert_eq!("thé".nfc().collect::<String>(), "th\u{e9}");
        assert_eq!("thé".nfd().collect::<String>(), "the\u{301}");
        assert_eq!("thé".nfkc().collect::<String>(), "th\u{e9}");
        assert_eq!("thé".nfkd().collect::<String>(), "the\u{301}");

        assert_eq!("Phở".nfc().collect::<String>(), "Ph\u{1edf}");
        assert_eq!("Phở".nfd().collect::<String>(), "Pho\u{31b}\u{309}");
        assert_eq!("Phở".nfkc().collect::<String>(), "Ph\u{1edf}");
        assert_eq!("Phở".nfkd().collect::<String>(), "Pho\u{31b}\u{309}");

        assert_ne!("⑤ Diﬃculty".nfc().collect::<String>(), "5 Difficulty");
        assert_ne!("⑤ Diﬃculty".nfd().collect::<String>(), "5 Difficulty");
        assert_eq!("⑤ Diﬃculty".nfkc().collect::<String>(), "5 Difficulty");
        assert_eq!("⑤ Diﬃculty".nfkd().collect::<String>(), "5 Difficulty");
    }
}
