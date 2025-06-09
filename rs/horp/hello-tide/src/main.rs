const SERVER_ADDR: &str = "0.0.0.0:1104";

#[async_std::main]
async fn main() -> tide::Result<()> {
    println!("Hello-Tide is running on {}.", SERVER_ADDR);
    let mut app = tide::new();
    app.at("/").get(|_| async { Ok("Hello, Tide!") });
    app.listen(SERVER_ADDR).await?;
    Ok(())
}