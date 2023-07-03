use std::{fs, io};
use actix_web::{App, Error, get, HttpRequest, HttpResponse, HttpServer, post, web};
use serde::Deserialize;

const SERVER_ADDR: &str = "0.0.0.0:1103";

#[actix_web::main]
async fn main() -> io::Result<()> {
    println!("BMI-Actix-Web is running on {}.", SERVER_ADDR);
    HttpServer::new(|| {
        App::new()
            .service(index)
            .service(get_calc)
            .service(post_calc)
    })
    .bind(SERVER_ADDR)?
    .run()
    .await
}

#[get("/")]
async fn index(_: HttpRequest) -> Result<HttpResponse, Error> {
    println!("GET /");
    Ok(HttpResponse::Ok()
        .content_type("text/html; charset=utf-8")
        .body(fs::read_to_string("html/index.html")?))
}

#[derive(Deserialize, Debug)]
pub struct Bmi {
    height: f64,
    weight: f64,
}

impl Bmi {
    pub fn new(height: f64, weight: f64) -> Self {
        Bmi { height, weight }
    }
}


#[get("/calc")]
async fn get_calc(b: web::Query<Bmi>) -> Result<HttpResponse, Error> {
    println!("GET /calc?height={}&weight={}", b.height, b.weight);
    do_calc(Bmi::new(b.height, b.weight))
}

#[post("/calc")]
async fn post_calc(b: web::Form<Bmi>) -> Result<HttpResponse, Error> {
    println!("POST /calc {:?}", b);
    do_calc(Bmi::new(b.height, b.weight))
}

fn do_calc(b: Bmi) -> Result<HttpResponse, Error> {
    let h = b.height / 100.0; // cm -> m
    let bmi = b.weight / (h * h);
    let obesity = (bmi / 22.0) * 100.0; // obesity rate (%)
    Ok(HttpResponse::Ok()
        .content_type("text/html; charset=utf-8")
        .body(format!("<h1>BMI Report</h1><p>BMI = {:.1}<br/>Obesity = {:.0}%</p>", bmi, obesity)))
}