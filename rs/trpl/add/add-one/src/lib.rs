use rand::Rng;

pub fn add_one(x: i32) -> i32 {
    x + 1
}

pub fn add_random(x: i32) -> i32 {
    x + rand::thread_rng().gen_range(0, 10)
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn add_one1() {
        assert_eq!(3, add_one(2));
    }

    #[test]
    fn add_random1() {
        for num in 0..10 {
            let result = add_random(num);
            assert!(num <= result && result < num + 10);
        }
    }
}