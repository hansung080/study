use std::{env, fs, process};
use regex::Regex;
use text_colorizer::Colorize;

fn main() {
    let args = parse_args();

    let content = match fs::read_to_string(&args.in_filename) {
        Ok(content) => content,
        Err(e) => {
            eprintln!("{}: failed to read file {}: {:?}", "error".red().bold(), args.in_filename, e);
            process::exit(1);
        },
    };

    let replaced_content = match replace_all(&args.target, &args.replacement, &content) {
        Ok(content) => content,
        Err(e) => {
            eprintln!("{}: failed to replace content: {:?}", "error".red().bold(), e);
            process::exit(1);
        },
    };

    match fs::write(&args.out_filename, &replaced_content) {
        Ok(_) => {},
        Err(e) => {
            eprintln!("{}: failed to write file {}: {:?}", "error".red().bold(), args.out_filename, e);
            process::exit(1);
        },
    };
}

#[derive(Debug)]
struct Args {
    target: String,
    replacement: String,
    in_filename: String,
    out_filename: String,
}

fn print_usage() {
    eprintln!("{}: quick-replace <TARGET> <REPLACEMENT> <IN_FILE> <OUT_FILE>", "usage".blue());
}

fn parse_args() -> Args {
    let args: Vec<String> = env::args().skip(1).collect();
    if args.len() != 4 {
        eprintln!("{}: wrong number of arguments: expected 4, got {}", "error".red().bold(), args.len());
        print_usage();
        process::exit(1);
    }

    Args {
        target: args[0].clone(),
        replacement: args[1].clone(),
        in_filename: args[2].clone(),
        out_filename: args[3].clone(),
    }
}

fn replace_all(target: &str, replacement: &str, content: &str) -> Result<String, regex::Error> {
    let regex = Regex::new(target)?;
    Ok(regex.replace_all(content, replacement).to_string())
}