use std::io::{self, BufRead};
use lazy_static::lazy_static;
use regex::Regex;

// `lazy_static!` initializes a static variable only once, on its first dereference.
// `lazy_static::initialize` allows a static variable to be explicitly initialized
// before its first dereference.
lazy_static! {
    // Regular Expression (abbreviated as regex)
    //
    //   - `^` and `$` denote anchors, so `^...`, `...$`, and `^...$` are anchored regexes.
    //   - `(...)` denotes a capturing group, and `(?:...)` denotes a non-capturing group.
    //
    // Semantic Versioning (abbreviated as SemVer)
    //
    //   major.minor.patch[-pre-release][+build-metadata]
    //
    //   - e.g. 1.0.0, 1.0.0-alpha.1, 1.0.0+build.123, and 1.0.0-alpha.1+build.123
    //   - NOTE: For simplicity, the following regexes have no patterns for build metadata suffix.
    //
    // Raw string literal: `r` allows `\` to be used literally without escaping it.
    static ref SEMVER: Regex = Regex::new(r"(\d+)\.(\d+)\.(\d+)(-[-.[:alnum:]]*)?")
        .expect("failed to create regex `SEMVER`");
    static ref SEMVER_EXACT: Regex = Regex::new(r"^(\d+)\.(\d+)\.(\d+)(-[-.[:alnum:]]*)?$")
        .expect("failed to create regex `SEMVER_EXACT`");
}

pub fn find_first_versions_per_line<R: BufRead>(reader: R) -> Result<Vec<String>, io::Error> {
    let mut versions = Vec::new();
    for line in reader.lines() {
        let line = line?;
        if let Some(match_) = SEMVER.find(&line) {
            versions.push(match_.as_str().to_string());
        }
    }
    Ok(versions)
}

pub fn find_all_versions_per_line<R: BufRead>(reader: R) -> Result<Vec<String>, io::Error> {
    let mut versions = Vec::new();
    for line in reader.lines() {
        let line = line?;
        for match_ in SEMVER.find_iter(&line) {
            versions.push(match_.as_str().to_string());
        }
    }
    Ok(versions)
}

#[cfg(test)]
mod tests {
    use std::error::Error;
    use std::io::Cursor;
    use super::*;

    #[test]
    fn semver() -> Result<(), Box<dyn Error>> {
        let cases = [
            // valid SemVer
            ("11.22.33",          true,  true),
            ("11.22.33-",         true,  true),
            ("11.22.33-44",       true,  true),
            ("11.22.33-alpha",    true,  true),
            ("11.22.33-alpha.44", true,  true),
            ("11.22.33-alpha-44", true,  true),
            // invalid SemVer
            ("11",                false, false),
            ("11.22",             false, false),
            ("11.22.",            false, false),
            ("11.22.a",           false, false),
            ("11.22.33.alpha",    true,  false),
            ("11.22.33-alpha_44", true,  false),
            // valid SemVer (including build metadata suffix)
            ("11.22.33+build.123",          true, false),
            ("11.22.33+20261018",           true, false),
            ("11.22.33-alpha.44+build.123", true, false),
            ("11.22.33-alpha.44+20261018",  true, false),
        ];

        for (haystack, expected, expected_exact) in cases {
            assert_eq!(SEMVER.is_match(haystack), expected);
            assert_eq!(SEMVER_EXACT.is_match(haystack), expected_exact);
        }

        // Raw string literal: `r#` allows `"` to be used literally without escaping it.
        let haystack = r#"regex = "0.2.5", rand = "6.7.8""#;
        assert!(SEMVER.is_match(haystack));

        let captures = SEMVER.captures(haystack)
            .ok_or("failed to capture regex `SEMVER`")?;
        assert_eq!(captures.len(), 5);
        assert_eq!(&captures[0], "0.2.5");
        assert_eq!(&captures[1], "0");
        assert_eq!(&captures[2], "2");
        assert_eq!(&captures[3], "5");
        assert_eq!(captures.get(4), None);
        assert_eq!(captures.get(3).unwrap().start(), 13);
        assert_eq!(captures.get(3).unwrap().end(), 14);
        assert_eq!(captures.get(3).unwrap().as_str(), "5");

        // Line continuation: `\` removes the newline and leading whitespace on the following line.
        let haystack = "In the beginning, there was 1.0.0. \
                             For a while, we used 1.0.1-beta, \
                             but in the end, we settled on 1.2.4.";
        let matches: Vec<&str> = SEMVER.find_iter(haystack)
            .map(|match_| match_.as_str())
            .collect();
        assert_eq!(matches, ["1.0.0", "1.0.1-beta", "1.2.4"]);

        Ok(())
    }

    #[test]
    fn find_versions_per_line() -> Result<(), Box<dyn Error>> {
        // No line continuation: Without `\` at the end of a line,
        //   the newline and leading whitespace on the following line are preserved.
        let haystack = "\
In the beginning, there was 1.0.0.
For a while, we used 1.0.1-alpha, then 1.0.1-beta, then 1.0.1,
but in the end, we settled on 1.2.4.";

        let versions = find_first_versions_per_line(Cursor::new(haystack))?;
        assert_eq!(versions, ["1.0.0", "1.0.1-alpha", "1.2.4"]);

        let versions = find_all_versions_per_line(Cursor::new(haystack))?;
        assert_eq!(versions, ["1.0.0", "1.0.1-alpha", "1.0.1-beta", "1.0.1", "1.2.4"]);
        Ok(())
    }
}
