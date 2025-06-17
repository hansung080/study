// use macro_examples::{json, my_assert_eq, my_vec};
// use macro_examples::json::Json;

#[test]
fn exported_macros() {
    let students = macro_examples::json!([
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

    let expected = macro_examples::json::Json::Array(macro_examples::my_vec![
        macro_examples::json::Json::Object(Box::new(macro_examples::my_vec![
            ("name".to_string(), macro_examples::json::Json::String("Jim Blandy".to_string())),
            ("classOf".to_string(), macro_examples::json::Json::Number(1926.0)),
            ("major".to_string(), macro_examples::json::Json::String("Tibetan throat singing".to_string())),
            ("onLeaveOfAbsence".to_string(), macro_examples::json::Json::Boolean(false)),
        ].into_iter().collect())),
        macro_examples::json::Json::Object(Box::new(macro_examples::my_vec![
            ("name".to_string(), macro_examples::json::Json::String("Json Orendorff".to_string())),
            ("classOf".to_string(), macro_examples::json::Json::Number(1702.0)),
            ("major".to_string(), macro_examples::json::Json::Null),
            ("onLeaveOfAbsence".to_string(), macro_examples::json::Json::Boolean(true)),
        ].into_iter().collect())),
    ]);

    macro_examples::my_assert_eq!(students, expected);
}