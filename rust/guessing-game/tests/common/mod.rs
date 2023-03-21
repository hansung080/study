pub fn assert_err<T, E>(result: Result<T, E>, msg: &str) {
    if let Ok(_) = result {
        panic!("{}", msg);
    }
}