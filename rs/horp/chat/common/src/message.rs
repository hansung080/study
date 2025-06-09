use std::string::ToString;
use serde::{Deserialize, Serialize};

#[derive(Serialize, Deserialize, Debug, PartialEq)]
pub struct Message {
    pub kind: usize,
    pub from: String,
    pub to: String,
    pub content: String,
    pub error: String,
}

impl Message {
    pub const KIND_REGISTER: usize = 1;
    pub const KIND_CHAT: usize = 2;
    pub const KIND_EXIT: usize = 3;

    pub const CMD_EXIT: &'static str = "exit";

    pub fn new(kind: usize, from: String, to: String, content: String) -> Self {
        Message::new_with_error(kind, from, to, content, "".to_string())
    }

    pub fn new_with_error(kind: usize, from: String, to: String, content: String, error: String) -> Self {
        Message { kind, from, to, content, error }
    }

    pub fn from_json(json: &str) -> Self {
        serde_json::from_str(json).expect(&format!("failed to deserialize json: {}", json))
    }

    pub fn to_json(&self) -> String {
        serde_json::to_string(self).expect(&format!("failed to serialize json: {:?}", self))
    }
}

#[cfg(test)]
mod tests {
    use crate::util::Pushed;
    use super::*;

    #[test]
    fn message_json() {
        let msg = Message::new_with_error(
            Message::KIND_CHAT,
            "Alice".to_string(),
            "Bob".to_string(),
            "Hi, Bob!".to_string(),
            "Bob not found".to_string(),
        );
        let json = msg.to_json().into_pushed('\n');
        let msg2 = Message::from_json(&json);
        assert_eq!(msg, msg2);
    }
}
