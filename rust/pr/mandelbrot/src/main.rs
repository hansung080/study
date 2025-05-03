use text_colorizer::Colorize;
use mandelbrot::execution::Executor;
use mandelbrot::utils;

fn main() {
    let duration = utils::elapsed_time(|| {
        Executor::new().execute();
    });
    println!("{}: {:?}", "elapsed time".blue(), duration);
}