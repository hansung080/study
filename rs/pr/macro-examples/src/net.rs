#![allow(unused)]

struct Session;

struct ServerSocket {
    session: Session,
}

impl ServerSocket {
    fn new() -> Self {
        ServerSocket {
            session: Session,
        }
    }

    fn session(&self) -> &Session {
        &self.session
    }
}

struct ServerRequest<'a> {
    session: &'a Session,
}

impl<'a> ServerRequest<'a> {
    fn new(session: &'a Session) -> Self {
        ServerRequest { session }
    }

    fn do_something(&self) {}
}

macro_rules! setup_req {
    // Hygienic macro mangles the variable names declared inside macro.
    // Thus, getting the variable names declared outside macro is required.
    ($req:ident, $server_socket:ident) => {
        let $req = ServerRequest::new($server_socket.session());
    };
}

fn handle_http_request(server_socket: &ServerSocket) {
    setup_req!(req, server_socket);
    req.do_something();
}
