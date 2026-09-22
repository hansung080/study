pub fn new_int_generator() -> impl FnMut() -> u32 {
    let mut next = 0;
    move || {
        next += 1;
        next
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn int_generator() {
        let mut gen1 = new_int_generator();
        let mut gen2 = new_int_generator();

        assert_eq!(gen1(), 1);
        assert_eq!(gen1(), 2);
        assert_eq!(gen1(), 3);

        assert_eq!(gen2(), 1);
        assert_eq!(gen2(), 2);
        assert_eq!(gen2(), 3);
        assert_eq!(gen2(), 4);
        assert_eq!(gen2(), 5);

        assert_eq!(gen1(), 4);
        assert_eq!(gen1(), 5);
    }
}
