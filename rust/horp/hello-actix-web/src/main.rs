use std::io;
use actix_web::{App, HttpRequest, HttpServer, web};

const SERVER_ADDR: &str = "0.0.0.0:1102";

#[actix_web::main]
async fn main() -> io::Result<()> {
    println!("Hello-Actix-Web is running on {}.", SERVER_ADDR);
    HttpServer::new(|| {
        App::new()
            .route("/", web::get().to(index))
    })
    .bind(SERVER_ADDR)?
    .run()
    .await
}

async fn index(req: HttpRequest) -> &'static str {
    println!("request: {:?}", req);
    "Hello, Actix Web!"
}