use regex::Regex;

#[cfg(test)]
mod tests {
    use std::error::Error;
    use super::*;

    #[test]
    fn regex() -> Result<(), Box<dyn Error>> {
        // For simplicity, neither regex has patterns for build metadata suffix
        // (e.g. `+build.123` and `+20261018235959`).
        // `semver_exact` is an anchored regex (e.g. `^...`, `...$`, and `^...$`).
        // `(...)` is a capturing group, and `(?:...)` is an non-capturing group.
        let semver = Regex::new(r"(\d+)\.(\d+)\.(\d+)(-[-.[:alnum:]]*)?")?;
        let semver_exact = Regex::new(r"^(\d+)\.(\d+)\.(\d+)(-[-.[:alnum:]]*)?$")?;

        let cases = [
            // valid SemVer
            ("11.22.33",          true,  true),
            ("11.22.33-",         true,  true),
            ("11.22.33-44",       true,  true),
            ("11.22.33-alpha",    true,  true),
            ("11.22.33-alpha-44", true,  true),
            ("11.22.33-alpha.44", true,  true),
            // invalid SemVer
            ("11",                false, false),
            ("11.22",             false, false),
            ("11.22.",            false, false),
            ("11.22.a",           false, false),
            ("11.22.33.alpha",    true,  false),
            ("11.22.33-alpha_44", true,  false),
            // valid SemVer (including build metadata suffix)
            ("11.22.33+build.123",            true, false),
            ("11.22.33+20261018235959",       true, false),
            ("11.22.33-alpha+build.123",      true, false),
            ("11.22.33-alpha+20261018235959", true, false),
        ];

        for (haystack, expected, expected_exact) in cases {
            assert_eq!(semver.is_match(haystack), expected);
            assert_eq!(semver_exact.is_match(haystack), expected_exact);
        }

        let haystack = r#"regex = "0.2.5", rand = "6.7.8""#;
        assert!(semver.is_match(haystack));

        let captures = semver.captures(haystack)
            .ok_or("regex `semver` should have matched")?;
        assert_eq!(captures.len(), 5);
        assert_eq!(&captures[0], "0.2.5");
        assert_eq!(&captures[1], "0");
        assert_eq!(&captures[2], "2");
        assert_eq!(&captures[3], "5");
        assert_eq!(captures.get(4), None);
        assert_eq!(captures.get(3).unwrap().start(), 13);
        assert_eq!(captures.get(3).unwrap().end(), 14);
        assert_eq!(captures.get(3).unwrap().as_str(), "5");

        let haystack = "In the beginning, there was 1.0.0. \
                             For a while, we used 1.0.1-beta, \
                             but in the end, we settled on 1.2.4.";
        let matches: Vec<&str> = semver.find_iter(haystack)
            .map(|match_| match_.as_str())
            .collect();
        assert_eq!(matches, ["1.0.0", "1.0.1-beta", "1.2.4"]);

        Ok(())
    }
}
