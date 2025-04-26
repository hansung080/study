use clap::Parser;
use mandelbrot::complex::ComplexArea;
use mandelbrot::image::Image;

fn main() {
    let args = Args::parse();
    println!("{args:?}");
    let mut img = Image::from_str(&args.image_size);
    img.render(&ComplexArea::from_str(&args.upper_left, &args.lower_right));
    img.save(&args.image_path).expect("failed to save image");
}

#[derive(Parser, Debug)]
#[command(version, author, about)]
/// Mandelbrot image generator
struct Args {
    /// Image path to save
    #[arg(
        short = 'p',
        long = "image-path",
        value_name = "PATH",
        default_value = "mandel.png",
    )]
    image_path: String,

    /// Image size
    #[arg(
        short = 's',
        long = "image-size",
        value_name = "SIZE",
        default_value = "4000x3000",
    )]
    image_size: String,

    /// Upper left point of complex area
    #[arg(
        short = 'u',
        long = "upper-left",
        value_name = "POINT",
        default_value = "-1.2,0.35",
    )]
    upper_left: String,

    /// Lower right point of complex area
    #[arg(
        short = 'l',
        long = "lower-right",
        value_name = "POINT",
        default_value = "-1.0,0.2",
    )]
    lower_right: String,

    /// The number of threads to run. 0 specifies the same number of CPU cores
    #[arg(
        short = 't',
        long = "threads",
        value_name = "THREADS",
        default_value = "1",
        value_parser = clap::value_parser!(u32),
    )]
    threads: u32,
}