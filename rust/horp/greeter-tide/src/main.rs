use std::fs;
use tide::prelude::*;

const SERVER_ADDR: &str = "0.0.0.0:1105";

#[derive(Deserialize, Debug)]
struct User {
    name: String,
}

#[async_std::main]
async fn main() -> tide::Result<()> {
    println!("Greeter-Tide is running on {}.", SERVER_ADDR);
    let mut app = tide::new();
    app.at("/").get(|_| async {
        println!("GET /");
        Ok(tide::Response::builder(200)
            .content_type(tide::http::mime::HTML)
            .body(fs::read_to_string("html/index.html")?)
            .build())
    });
    app.at("/hello").get(|req: tide::Request<()>| async move {
        let user: User = req.query()?;
        println!("GET /hello?name={}", user.name);
        Ok(tide::Response::builder(200)
            .content_type(tide::http::mime::HTML)
            .body(format!("<h1>Hello, {}!</h1>", user.name))
            .build())
    });
    app.at("/hello").post(|mut req: tide::Request<()>| async move {
        let user: User = req.body_form().await?;
        println!("POST /hello Form: {:?}", user);
        Ok(tide::Response::builder(200)
            .content_type(tide::http::mime::HTML)
            .body(format!("<h1>Hello, {}!</h1>", user.name))
            .build())
    });
    app.listen(SERVER_ADDR).await?;
    Ok(())
}
