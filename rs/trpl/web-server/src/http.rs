use std::fmt;

// 1xx Informational
#[allow(unused)] pub const STATUS_CONTINUE: Status = Status::new(100, "Continue");
#[allow(unused)] pub const STATUS_SWITCHING_PROTOCOLS: Status = Status::new(101, "Switching Protocols");
#[allow(unused)] pub const STATUS_PROCESSING: Status = Status::new(102, "Processing");
#[allow(unused)] pub const STATUS_CHECKPOINT: Status = Status::new(103, "Checkpoint");

// 2xx Success
#[allow(unused)] pub const STATUS_OK: Status = Status::new(200, "OK");
#[allow(unused)] pub const STATUS_CREATED: Status = Status::new(201, "Created");
#[allow(unused)] pub const STATUS_ACCEPTED: Status = Status::new(202, "Accepted");
#[allow(unused)] pub const STATUS_NON_AUTHORITATIVE_INFORMATION: Status = Status::new(203, "Non-Authoritative Information");
#[allow(unused)] pub const STATUS_NO_CONTENT: Status = Status::new(204, "No Content");
#[allow(unused)] pub const STATUS_RESET_CONTENT: Status = Status::new(205, "Reset Content");
#[allow(unused)] pub const STATUS_PARTIAL_CONTENT: Status = Status::new(206, "Partial Content");
#[allow(unused)] pub const STATUS_MULTI_STATUS: Status = Status::new(207, "Multi-Status");
#[allow(unused)] pub const STATUS_ALREADY_REPORTED: Status = Status::new(208, "Already Reported");
#[allow(unused)] pub const STATUS_IM_USED: Status = Status::new(226, "IM Used");

// 3xx Redirection
#[allow(unused)] pub const STATUS_MULTIPLE_CHOICES: Status = Status::new(300, "Multiple Choices");
#[allow(unused)] pub const STATUS_MOVED_PERMANENTLY: Status = Status::new(301, "Moved Permanently");
#[allow(unused)] pub const STATUS_FOUND: Status = Status::new(302, "Found");
#[allow(unused)] #[deprecated] pub const STATUS_MOVED_TEMPORARILY: Status = Status::new(302, "Moved Temporarily");
#[allow(unused)] pub const STATUS_SEE_OTHER: Status = Status::new(303, "See Other");
#[allow(unused)] pub const STATUS_NOT_MODIFIED: Status = Status::new(304, "Not Modified");
#[allow(unused)] #[deprecated] pub const STATUS_USE_PROXY: Status = Status::new(305, "Use Proxy");
#[allow(unused)] pub const STATUS_TEMPORARY_REDIRECT: Status = Status::new(307, "Temporary Redirect");
#[allow(unused)] pub const STATUS_PERMANENT_REDIRECT: Status = Status::new(308, "Permanent Redirect");

// 4xx Client Error
#[allow(unused)] pub const STATUS_BAD_REQUEST: Status = Status::new(400, "Bad Request");
#[allow(unused)] pub const STATUS_UNAUTHORIZED: Status = Status::new(401, "Unauthorized");
#[allow(unused)] pub const STATUS_PAYMENT_REQUIRED: Status = Status::new(402, "Payment Required");
#[allow(unused)] pub const STATUS_FORBIDDEN: Status = Status::new(403, "Forbidden");
#[allow(unused)] pub const STATUS_NOT_FOUND: Status = Status::new(404, "Not Found");
#[allow(unused)] pub const STATUS_METHOD_NOT_ALLOWED: Status = Status::new(405, "Method Not Allowed");
#[allow(unused)] pub const STATUS_NOT_ACCEPTABLE: Status = Status::new(406, "Not Acceptable");
#[allow(unused)] pub const STATUS_PROXY_AUTHENTICATION_REQUIRED: Status = Status::new(407, "Proxy Authentication Required");
#[allow(unused)] pub const STATUS_REQUEST_TIMEOUT: Status = Status::new(408, "Request Timeout");
#[allow(unused)] pub const STATUS_CONFLICT: Status = Status::new(409, "Conflict");
#[allow(unused)] pub const STATUS_GONE: Status = Status::new(410, "Gone");
#[allow(unused)] pub const STATUS_LENGTH_REQUIRED: Status = Status::new(411, "Length Required");
#[allow(unused)] pub const STATUS_PRECONDITION_FAILED: Status = Status::new(412, "Precondition Failed");
#[allow(unused)] pub const STATUS_PAYLOAD_TOO_LARGE: Status = Status::new(413, "Payload Too Large");
#[allow(unused)] #[deprecated] pub const STATUS_REQUEST_ENTITY_TOO_LARGE: Status = Status::new(413, "Request Entity Too Large");
#[allow(unused)] pub const STATUS_URI_TOO_LONG: Status = Status::new(414, "URI Too Long");
#[allow(unused)] #[deprecated] pub const STATUS_REQUEST_URI_TOO_LONG: Status = Status::new(414, "Request-URI Too Long");
#[allow(unused)] pub const STATUS_UNSUPPORTED_MEDIA_TYPE: Status = Status::new(415, "Unsupported Media Type");
#[allow(unused)] pub const STATUS_REQUESTED_RANGE_NOT_SATISFIABLE: Status = Status::new(416, "Requested range not satisfiable");
#[allow(unused)] pub const STATUS_EXPECTATION_FAILED: Status = Status::new(417, "Expectation Failed");
#[allow(unused)] pub const STATUS_I_AM_A_TEAPOT: Status = Status::new(418, "I'm a teapot");
#[allow(unused)] #[deprecated] pub const STATUS_INSUFFICIENT_SPACE_ON_RESOURCE: Status = Status::new(419, "Insufficient Space On Resource");
#[allow(unused)] #[deprecated] pub const STATUS_METHOD_FAILURE: Status = Status::new(420, "Method Failure");
#[allow(unused)] #[deprecated] pub const STATUS_DESTINATION_LOCKED: Status = Status::new(421, "Destination Locked");
#[allow(unused)] pub const STATUS_UNPROCESSABLE_ENTITY: Status = Status::new(422, "Unprocessable Entity");
#[allow(unused)] pub const STATUS_LOCKED: Status = Status::new(423, "Locked");
#[allow(unused)] pub const STATUS_FAILED_DEPENDENCY: Status = Status::new(424, "Failed Dependency");
#[allow(unused)] pub const STATUS_TOO_EARLY: Status = Status::new(425, "Too Early");
#[allow(unused)] pub const STATUS_UPGRADE_REQUIRED: Status = Status::new(426, "Upgrade Required");
#[allow(unused)] pub const STATUS_PRECONDITION_REQUIRED: Status = Status::new(428, "Precondition Required");
#[allow(unused)] pub const STATUS_TOO_MANY_REQUESTS: Status = Status::new(429, "Too Many Requests");
#[allow(unused)] pub const STATUS_REQUEST_HEADER_FIELDS_TOO_LARGE: Status = Status::new(431, "Request Header Fields Too Large");
#[allow(unused)] pub const STATUS_UNAVAILABLE_FOR_LEGAL_REASONS: Status = Status::new(451, "Unavailable For Legal Reasons");

// 5xx Server Error
#[allow(unused)] pub const STATUS_INTERNAL_SERVER_ERROR: Status = Status::new(500, "Internal Server Error");
#[allow(unused)] pub const STATUS_NOT_IMPLEMENTED: Status = Status::new(501, "Not Implemented");
#[allow(unused)] pub const STATUS_BAD_GATEWAY: Status = Status::new(502, "Bad Gateway");
#[allow(unused)] pub const STATUS_SERVICE_UNAVAILABLE: Status = Status::new(503, "Service Unavailable");
#[allow(unused)] pub const STATUS_GATEWAY_TIMEOUT: Status = Status::new(504, "Gateway Timeout");
#[allow(unused)] pub const STATUS_HTTP_VERSION_NOT_SUPPORTED: Status = Status::new(505, "HTTP Version Not supported");
#[allow(unused)] pub const STATUS_VARIANT_ALSO_NEGOTIATES: Status = Status::new(506, "Variant Also Negotiates");
#[allow(unused)] pub const STATUS_INSUFFICIENT_STORAGE: Status = Status::new(507, "Insufficient Storage");
#[allow(unused)] pub const STATUS_LOOP_DETECTED: Status = Status::new(508, "Loop Detected");
#[allow(unused)] pub const STATUS_BANDWIDTH_LIMIT_EXCEEDED: Status = Status::new(509, "Bandwidth Limit Exceeded");
#[allow(unused)] pub const STATUS_NOT_EXTENDED: Status = Status::new(510, "Not Extended");
#[allow(unused)] pub const STATUS_NETWORK_AUTHENTICATION_REQUIRED: Status = Status::new(511, "Network Authentication Required");

// 6xx Custom Error
#[allow(unused)] pub const STATUS_SHUT_DOWN_SERVER: Status = Status::new(600, "Shut Down Server");

pub struct Status {
    code: u32,
    text: &'static str,
}

impl Status {
    const fn new(code: u32, text: &'static str) -> Self {
        Self { code, text }
    }

    pub fn code(&self) -> u32 {
        self.code
    }

    pub fn text(&self) -> &str {
        self.text
    }

    pub fn is_error(&self) -> bool {
        self.code >= 400
    }
}

impl fmt::Display for Status {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "{} ({})", self.text, self.code)
    }
}

impl PartialEq for Status {
    fn eq(&self, other: &Self) -> bool {
        self.code == other.code
    }

    fn ne(&self, other: &Self) -> bool {
        self.code != other.code
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn status_is_error() {
        let cases = [
            (399, false),
            (400, true),
            (401, true),
        ];

        for (input, expected) in cases {
            assert_eq!(expected, Status::new(input, "").is_error());
        }
    }
}