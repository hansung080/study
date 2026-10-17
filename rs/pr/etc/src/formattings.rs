use std::env;
use std::fmt::Arguments;
use std::fs::OpenOptions;
use std::io::Write;

pub fn logging_enabled() -> bool {
    env::var("PR_ETC_LOGGING").is_ok()
}

pub fn write_log_entry(entry: Arguments) {
    if !logging_enabled() {
        return;
    }

    // NOTE: For simplicity, open the file each time for now.
    let mut log_file = OpenOptions::new()
        .append(true)
        .create(true)
        .open("etc.log")
        .expect("failed to open file `etc.log`");

    log_file.write_fmt(entry)
        .expect("failed to write to file `etc.log`");
}

// BAD: `log1!` handles pattern matching directly.
#[macro_export]
macro_rules! log1 {
    ($format:tt, $($arg:expr),*) => {
        $crate::formattings::write_log_entry(::std::format_args!($format, $($arg),*))
    };
    ($format:tt) => {
        $crate::formattings::write_log_entry(::std::format_args!($format))
    };
}

// GOOD: `log2!` delegates pattern matching to `format_args!`
//       (as `format!`, `print!`, `println!`, `write!`, and `writeln!` do).
#[macro_export]
macro_rules! log2 {
    ($($arg:tt)*) => {
        $crate::formattings::write_log_entry(::std::format_args!($($arg)*))
    };
}

#[cfg(test)]
mod tests {

    #[test]
    fn write_log_entry() {
        let mysterious_value = Some("mysterious value");
        super::write_log_entry(format_args!("LOG 1: Hark! {:?}\n", mysterious_value));
        super::write_log_entry(format_args!("LOG 2: Hark! {mysterious_value:?}\n"));
        log1!("LOG 3: O day and night, but this is wondrous strange! {:?}\n", mysterious_value);
        log1!("LOG 4: O day and night, but this is wondrous strange! {mysterious_value:?}\n");
        log2!("LOG 5: O day and night, but this is wondrous strange! {:?}\n", mysterious_value);
        log2!("LOG 6: O day and night, but this is wondrous strange! {mysterious_value:?}\n");
    }
}
