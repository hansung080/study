#[derive(Debug)]
pub struct Error {
    msg: &'static str,
}

impl Error {
    pub fn new(msg: &'static str) -> Error {
        Error { msg }
    }

    pub fn msg(&self) -> &'static str {
        self.msg
    }
}

impl PartialEq for Error {
    fn eq(&self, other: &Self) -> bool {
        self.msg == other.msg
    }    
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn error_msg() {
        let error = Error::new("test error message");
        assert_eq!("test error message", error.msg());
    }
}