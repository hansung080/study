use clap::Parser;
use text_colorizer::Colorize;
use mandelbrot::args::Args;
use mandelbrot::execution::Executor;
use mandelbrot::utils;

fn main() {
    let duration = utils::elapsed_time(|| {
        Executor::new(Args::parse()).execute();
    });
    println!("{}: {:?}", "elapsed time".blue(), duration);
}