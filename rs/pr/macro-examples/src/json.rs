use std::collections::HashMap;

#[allow(unused)]
#[derive(Debug, Clone, PartialEq)]
pub enum Json {
    Null,
    Boolean(bool),
    Number(f64),
    String(String),
    Array(Vec<Json>),
    Object(Box<HashMap<String, Json>>),
}

impl From<bool> for Json {
    fn from(b: bool) -> Self {
        Json::Boolean(b)
    }
}

impl From<String> for Json {
    fn from(s: String) -> Self {
        Json::String(s)
    }
}

impl<'a> From<&'a str> for Json {
    fn from(s: &'a str) -> Self {
        Json::String(s.to_string())
    }
}

macro_rules! impl_from_num_for_json {
    ($($typ:ident)*) => {
        $(
            impl From<$typ> for Json {
                fn from(n: $typ) -> Self {
                    Json::Number(n as f64)
                }
            }
        )*
    };
}

impl_from_num_for_json!(u8 u16 u32 u64 u128 usize i8 i16 i32 i64 i128 isize f32 f64);

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn json1() {
        let students = json!([
            {
                "name": "Jim Blandy",
                "classOf": 1926,
                "major": "Tibetan throat singing",
                "onLeaveOfAbsence": false
            },
            {
                "name": "Json Orendorff",
                "classOf": 1702.0,
                "major": null,
                "onLeaveOfAbsence": true
            }
        ]);

        let expected = Json::Array(my_vec![
            Json::Object(Box::new(my_vec![
                ("name".to_string(), Json::String("Jim Blandy".to_string())),
                ("classOf".to_string(), Json::Number(1926.0)),
                ("major".to_string(), Json::String("Tibetan throat singing".to_string())),
                ("onLeaveOfAbsence".to_string(), Json::Boolean(false)),
            ].into_iter().collect())),
            Json::Object(Box::new(my_vec2![
                ("name".to_string(), Json::String("Json Orendorff".to_string())),
                ("classOf".to_string(), Json::Number(1702.0)),
                ("major".to_string(), Json::Null),
                ("onLeaveOfAbsence".to_string(), Json::Boolean(true)),
            ].into_iter().collect())),
        ]);

        my_assert_eq!(students, expected);
    }

    #[test]
    fn json2() {
        let width = 4.0;
        let size = json!({
            "width": width,
            // These parentheses are required because `$value:tt` requires a single token tree.
            "height": (width * 9.0 / 4.0)
        });

        let expected = Json::Object(Box::new(my_vec![
            ("width".to_string(), Json::Number(width)),
            ("height".to_string(), Json::Number(width * 9.0 / 4.0)),
        ].into_iter().collect()));

        my_assert_eq!(size, expected);
    }
}