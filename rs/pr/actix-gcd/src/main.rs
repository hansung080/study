use std::io;
use actix_web::{App, Error, get, HttpRequest, HttpResponse, HttpServer, main, post, web};
use serde::Deserialize;

const SERVER_ADDR: &str = "0.0.0.0:3000";

#[main]
async fn main() -> io::Result<()> {
    println!("Actix-gcd is running on {SERVER_ADDR}.");
    HttpServer::new(|| {
        App::new()
            .service(get_index)
            .service(post_gcd)
    })
        .bind(SERVER_ADDR)?
        .run()
        .await
}

#[get("/")]
async fn get_index(_: HttpRequest) -> Result<HttpResponse, Error> {
    println!("GET /");
    Ok(
        HttpResponse::Ok()
            .content_type("text/html; charset=utf-8")
            .body(r#"
<title>GCD Calculator</title>
<form action="/gcd" method="post">
  <input type="text" name="a"/>
  <input type="text" name="b"/>
  <button type="submit">Compute GCD</button>
</form>
            "#)
    )
}

#[derive(Deserialize, Debug)]
struct GcdParams {
    a: u64,
    b: u64,
}

#[post("/gcd")]
async fn post_gcd(form: web::Form<GcdParams>) -> Result<HttpResponse, Error> {
    println!("POST /gcd {:?}", form);
    if form.a == 0 && form.b == 0 {
        return Ok(
            HttpResponse::BadRequest()
                .content_type("text/html; charset=utf-8")
                .body("gcd calculation error: inputs cannot both be 0")
        );
    }

    Ok(
        HttpResponse::Ok()
            .content_type("text/html; charset=utf-8")
            .body(format!("gcd({}, {}) => <b>{}</b>", form.a, form.b, gcd::gcd_iter(form.a, form.b)))
    )
}