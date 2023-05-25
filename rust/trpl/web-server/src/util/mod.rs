pub mod thread_pool;

pub trait FirstLine {
    fn first_line(&self) -> Self;
}

impl FirstLine for &[u8] {
    fn first_line(&self) -> Self {
        let pos = match self.iter().position(|&x| x == '\r' as u8 || x == '\n' as u8) {
            Some(pos) => pos,
            None => self.len(),
        };
        &self[..pos]
    }
}

impl FirstLine for &str {
    fn first_line(&self) -> Self {
        let pos = match self.find("\r") {
            Some(pos) => pos,
            None => match self.find("\n") {
                Some(pos) => pos,
                None => self.len(),
            },
        };
        &self[..pos]
    }
}

pub fn split_address(addr: &str) -> (&str, &str) {
    let pos = addr.find(":").unwrap();
    (&addr[..pos], &addr[pos+1..])
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn u8slice_first_line() {
        let cases = [
            (&b""[..], &b""[..]),
            (&b"aaa"[..], &b"aaa"[..]),
            (&b"aaa\r\nbbb"[..], &b"aaa"[..]),
            (&b"aaa\r\nbbb\r\nccc"[..], &b"aaa"[..]),
            (&b"aaa\nbbb"[..], &b"aaa"[..]),
            (&b"aaa\nbbb\nccc"[..], &b"aaa"[..]),
        ];

        for (input, expected) in cases {
            assert_eq!(expected, input.first_line());
        }
    }

    #[test]
    fn str_first_line() {
        let cases = [
            (&""[..], &""[..]),
            (&"aaa"[..], &"aaa"[..]),
            (&"aaa\r\nbbb"[..], &"aaa"[..]),
            (&"aaa\r\nbbb\r\nccc"[..], &"aaa"[..]),
            (&"aaa\nbbb"[..], &"aaa"[..]),
            (&"aaa\nbbb\nccc"[..], &"aaa"[..]),
        ];

        for (input, expected) in cases {
            assert_eq!(expected, input.first_line());
        }
    }

    #[test]
    #[should_panic]
    fn split_address_panic() {
        let _ = split_address("127.0.0.1");
    }

    #[test]
    fn split_address_ok() {
        let (ip, port) = split_address("127.0.0.1:1234");
        assert_eq!("127.0.0.1", ip);
        assert_eq!("1234", port);
    }
}