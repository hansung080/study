use clap::Parser;

#[derive(Parser, Debug)]
#[command(version, author, about)]
/// Mandelbrot image generator
pub struct Args {
    /// Image path to save
    #[arg(
        short = 'p',
        long = "image-path",
        value_name = "PATH",
        default_value = "mandel.png",
    )]
    pub image_path: String,

    /// Image size
    #[arg(
        short = 's',
        long = "image-size",
        value_name = "SIZE",
        default_value = "4000x3000",
    )]
    pub image_size: String,

    /// Upper left point of complex area
    #[arg(
        short = 'u',
        long = "upper-left",
        value_name = "POINT",
        default_value = "-1.2,0.35",
    )]
    pub upper_left: String,

    /// Lower right point of complex area
    #[arg(
        short = 'l',
        long = "lower-right",
        value_name = "POINT",
        default_value = "-1.0,0.2",
    )]
    pub lower_right: String,

    /// The number of threads to run. 0 specifies the same number as CPU cores
    #[arg(
        short = 't',
        long = "threads",
        value_name = "THREADS",
        default_value = "1",
    )]
    pub threads: usize,

    /// Do not print log messages
    #[arg(
        short = 'q',
        long = "quiet",
    )]
    pub quiet: bool,
}