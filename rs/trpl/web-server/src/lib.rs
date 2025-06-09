extern crate core;

mod http;
mod util;

use std::{fs, io, thread};
use std::collections::HashMap;
use std::fmt;
use std::io::{Read, Write};
use std::net::{TcpListener, TcpStream};
use std::sync::{Arc, Mutex};
use std::time::Duration;
use handlebars::Handlebars;
use crate::util::{FirstLine, split_address};

pub use crate::util::thread_pool::ThreadPool;

pub fn run(addr: &str) {
    let listener = TcpListener::bind(addr).expect(&format!("failed to bind address {}", addr));
    let pool = ThreadPool::new(4);
    let mut handlebars = Handlebars::new();
    handlebars.set_strict_mode(false);
    handlebars.register_template_string("error.html", include_str!("../html/error.html")).expect("failed to register template 'error.html'");
    let handlebars = Arc::new(handlebars);
    let breaks = Arc::new(Mutex::new(false));
    let port: u32 = split_address(addr).1.parse().unwrap();
    println!("Web server is running on {}.", addr);

    for stream in listener.incoming() {
        let mut stream = match stream {
            Ok(stream) => stream,
            Err(e) => {
                eprintln!("failed to accept connection: {}", e);
                continue
            },
        };

        if *breaks.lock().unwrap() {
            break;
        }

        let handlebars = Arc::clone(&handlebars);
        let breaks = Arc::clone(&breaks);
        pool.execute(move || {
            if let Err(e) = handle_request(&mut stream) {
                eprintln!("failed to handle request: {}", e);
                if e.status == http::STATUS_SHUT_DOWN_SERVER {
                    *breaks.lock().unwrap() = true;
                    let _ = TcpStream::connect(format!("127.0.0.1:{}", port));
                } else {
                    let mut data = HashMap::new();
                    data.insert("error", e.to_string());
                    let content = handlebars.render("error.html", &data).expect("failed to render template 'error.html'");
                    if let Err(e) = send_response(&mut stream, &e.status, &content) {
                        eprintln!("failed to send error response: {}", e);
                    }
                }
            }
        });
    }

    println!("Web server shuts down.");
}

fn handle_request(stream: &mut TcpStream) -> Result<()> {
    let mut request = [0; 512];
    stream.read(&mut request)?;
    let start_line = (&request[..]).first_line();
    println!("http request: {}", String::from_utf8_lossy(start_line));

    let (status, filename) = if start_line.eq(b"GET / HTTP/1.1") {
        (http::STATUS_OK, "index.html")
    } else if start_line.eq(b"GET /sleep HTTP/1.1") {
        thread::sleep(Duration::from_secs(5));
        (http::STATUS_OK, "index.html")
    } else if start_line.eq(b"GET /error HTTP/1.1") {
        return Err(Error::new(http::STATUS_INTERNAL_SERVER_ERROR, "error on purpose".to_string()))
    } else if start_line.eq(b"GET /panic HTTP/1.1") {
        panic!("panic on purpose")
    } else if start_line.eq(b"GET /shutdown HTTP/1.1") {
        return Err(Error::new_without_detail(http::STATUS_SHUT_DOWN_SERVER))
    } else {
        return Err(Error::new_without_detail(http::STATUS_NOT_FOUND))
    };

    let content = fs::read_to_string("html/".to_string() + filename)?;
    send_response(stream, &status, &content)
}

fn send_response(stream: &mut TcpStream, status: &http::Status, body: &str) -> Result<()> {
    // FIXME: This response works in Safari, but does not work in Chrome.
    let response = format!("HTTP/1.1 {} {}\r\n\r\n{}", status.code(), status.text(), body);
    println!("http response: {}", (&response[..]).first_line());
    stream.write(response.as_bytes())?;
    stream.flush()?;
    Ok(())
}

pub type Result<T> = std::result::Result<T, Error>;

pub struct Error {
    status: http::Status,
    detail: String,
}

impl Error {
    pub fn new(status: http::Status, detail: String) -> Self {
        assert!(status.is_error());
        Self { status, detail }
    }

    pub fn new_without_detail(status: http::Status) -> Self {
        Error::new(status, "".to_string())
    }
}

impl From<io::Error> for Error {
    fn from(value: io::Error) -> Self {
        Error::new(http::STATUS_INTERNAL_SERVER_ERROR, value.to_string())
    }
}

impl fmt::Display for Error {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        if self.detail.is_empty() {
            write!(f, "{}", self.status)
        } else {
            write!(f, "{} - {}", self.status, self.detail)
        }
    }
}

#[cfg(test)]
mod tests {
    use std::sync::Once;
    use super::*;

    const SERVER_ADDRESS: &str = "127.0.0.1:7878";
    static SET_UP: Once = Once::new();
    static SET_UP_COUNT: Mutex<u32> = Mutex::new(0);

    fn set_up() -> TearDown {
        {
            let mut count = SET_UP_COUNT.lock().unwrap();
            *count += 1;
        }
        SET_UP.call_once(|| {
            thread::spawn(|| run(SERVER_ADDRESS));
        });
        TearDown
    }

    struct TearDown;

    impl Drop for TearDown {
        fn drop(&mut self) {
            let mut count = SET_UP_COUNT.lock().unwrap();
            *count -= 1;
            if *count == 0 {
                drop(count);
                let mut stream = TcpStream::connect(SERVER_ADDRESS).unwrap();
                let request = b"GET /shutdown HTTP/1.1\r\n\r\n";
                stream.write(request).unwrap();
            }
        }
    }

    fn assert_eq_http(request: &[u8], expected_response: &[u8]) {
        let mut stream = TcpStream::connect(SERVER_ADDRESS).unwrap();
        stream.write(request).unwrap();
        let mut response = [0; 1024];
        stream.read(&mut response).unwrap();
        assert_eq!(expected_response, (&response[..]).first_line());
    }

    #[test]
    fn http_get_all() {
        let _tear_down = set_up();
        let cases = [
            ("GET / HTTP/1.1\r\n\r\n", format!("HTTP/1.1 {} {}", http::STATUS_OK.code(), http::STATUS_OK.text())),
            ("GET /error HTTP/1.1\r\n\r\n", format!("HTTP/1.1 {} {}", http::STATUS_INTERNAL_SERVER_ERROR.code(), http::STATUS_INTERNAL_SERVER_ERROR.text())),
            ("GET /unknown HTTP/1.1\r\n\r\n", format!("HTTP/1.1 {} {}", http::STATUS_NOT_FOUND.code(), http::STATUS_NOT_FOUND.text())),
        ];

        for _ in 0..10 {
            for case in cases.iter() {
                assert_eq_http(case.0.as_bytes(), case.1.as_bytes());
            }
        }
    }

    #[test]
    #[ignore]
    fn http_get_sleep() {
        let _tear_down = set_up();
        let case = ("GET /sleep HTTP/1.1\r\n\r\n", format!("HTTP/1.1 {} {}", http::STATUS_OK.code(), http::STATUS_OK.text()));
        assert_eq_http(case.0.as_bytes(), case.1.as_bytes());
    }
}
