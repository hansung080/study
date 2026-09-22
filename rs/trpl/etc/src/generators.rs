pub fn new_u32_generator() -> impl FnMut() -> u32 {
    let mut next = 0;
    move || {
        let result = next;
        next += 1;
        result
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn u32_generator() {
        let mut gen1 = new_u32_generator();
        let mut gen2 = new_u32_generator();

        assert_eq!(gen1(), 0);
        assert_eq!(gen1(), 1);
        assert_eq!(gen1(), 2);

        assert_eq!(gen2(), 0);
        assert_eq!(gen2(), 1);
        assert_eq!(gen2(), 2);
        assert_eq!(gen2(), 3);
        assert_eq!(gen2(), 4);

        assert_eq!(gen1(), 3);
        assert_eq!(gen1(), 4);
    }
}
