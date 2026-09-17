#![allow(unused)]

use std::collections::HashMap;

pub enum Method {
    Get,
    Post,
    Put,
    Delete,
    Head,
    Connect,
    Options,
    Trace,
    Patch,
}

pub struct Request {
    method: Method,
    path: String,
    headers: HashMap<String, String>,
    body: Vec<u8>,
}

pub struct Response {
    status_code: u32,
    headers: HashMap<String, String>,
    body: Vec<u8>,
}

type Handler = Box<dyn Fn(&Request) -> Response>;

pub struct BasicRouter {
    routes: HashMap<String, Handler>,
}

impl BasicRouter {
    pub fn new() -> Self {
        BasicRouter { routes: HashMap::new() }
    }

    pub fn add_route<F>(&mut self, path: &str, handler: F)
    where
        F: Fn(&Request) -> Response + 'static,
    {
        self.routes.insert(path.to_string(), Box::new(handler));
    }

    pub fn handle_request(&self, request: &Request) -> Response {
        match self.routes.get(&request.path) {
            None => not_found_error(request),
            Some(handler) => handler(request),
        }
    }
}

pub struct FnPointerRouter {
    routes: HashMap<String, fn(&Request) -> Response>,
}

impl FnPointerRouter {
    pub fn new() -> Self {
        FnPointerRouter { routes: HashMap::new() }
    }

    pub fn add_route(&mut self, path: &str, handler: fn(&Request) -> Response) {
        self.routes.insert(path.to_string(), handler);
    }

    pub fn handle_request(&self, request: &Request) -> Response {
        match self.routes.get(&request.path) {
            None => not_found_error(request),
            Some(handler) => handler(request),
        }
    }
}

fn not_found_error(request: &Request) -> Response {
    Response {
        status_code: 404,
        headers: HashMap::from([
            ("Content-Type".to_string(), "text/html; charset=utf-8".to_string()),
        ]),
        body: format!("Page ({}) not found", request.path).into_bytes(),
    }
}

fn get_index(_request: &Request) -> Response {
    Response {
        status_code: 200,
        headers: HashMap::from([
            ("Content-Type".to_string(), "text/html; charset=utf-8".to_string()),
        ]),
        body: r#"
<title>GCD Calculator</title>
<form action="/gcd" method="post">
  <input type="text" name="a"/>
  <input type="text" name="b"/>
  <button type="submit">Compute GCD</button>
</form>
        "#.to_string().into_bytes(),
    }
}

fn post_gcd(_request: &Request) -> Response {
    let a = 40;
    let b = 206;
    let gcd = 2;

    Response {
        status_code: 201,
        headers: HashMap::from([
            ("Content-Type".to_string(), "text/html; charset=utf-8".to_string()),
        ]),
        body: format!("The GCD of {} and {} is <b>{}</b>.", a, b, gcd).into_bytes(),
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use super::Method::*;

    fn make_request(method: Method, path: &str) -> Request {
        Request {
            method,
            path: path.to_string(),
            headers: HashMap::from([
                ("Host".to_string(), "localhost".to_string()),
            ]),
            body: Vec::new(),
        }
    }

    #[test]
    fn basic_router() {
        let mut router = BasicRouter::new();
        router.add_route("/", get_index);
        router.add_route("/gcd", post_gcd);

        assert_eq!(router.handle_request(&make_request(Get, "/")).status_code, 200);
        assert_eq!(router.handle_request(&make_request(Post, "/gcd")).status_code, 201);
        assert_eq!(router.handle_request(&make_request(Get, "/unknown")).status_code, 404);
    }

    #[test]
    fn fn_pointer_router() {
        let mut router = FnPointerRouter::new();
        router.add_route("/", get_index);
        router.add_route("/gcd", post_gcd);

        assert_eq!(router.handle_request(&make_request(Get, "/")).status_code, 200);
        assert_eq!(router.handle_request(&make_request(Post, "/gcd")).status_code, 201);
        assert_eq!(router.handle_request(&make_request(Get, "/unknown")).status_code, 404);
    }
}
