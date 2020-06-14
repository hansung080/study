enum State {
    Draft,
    PendingReview,
    Published,
}

pub struct Post {
    state: State,
    content: String,
}

impl Post {
    pub fn new() -> Post {
        Post {
            state: State::Draft,
            content: String::new(),
        }
    }

    pub fn add_text(&mut self, text: &str) {
        self.content.push_str(text);
    }

    pub fn request_review(&mut self) {
        if let State::Draft = self.state {
            self.state = State::PendingReview;
        }
    }

    pub fn approve(&mut self) {
        if let State::PendingReview = self.state {
            self.state = State::Published;
        }
    }

    pub fn content(&self) -> &str {
        if let State::Published = self.state {
            &self.content
        } else {
            ""
        }
    }
}