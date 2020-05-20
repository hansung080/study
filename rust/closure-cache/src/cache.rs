use std::collections::HashMap;
use std::hash::Hash;
use std::cmp::Eq;

pub struct Cacher<'a, F, K, V>
where
    F: Fn(&K) -> &V,
    K: Hash + Eq,
{
    closure: F,
    results: HashMap<&'a K, &'a V>,
}

impl<'a, F, K, V> Cacher<'a, F, K, V>
where
    F: Fn(&K) -> &V,
    K: Hash + Eq,
{
    pub fn new(closure: F) -> Cacher<'a, F, K, V> {
        Cacher {
            closure,
            results: HashMap::new(),
        }
    }

    pub fn result(&mut self, arg: &'a K) -> &'a V {
        match self.results.get(arg) {
            Some(result) => result,
            None => {
                let result = (self.closure)(arg);
                self.results.insert(arg, result);
                result
            }
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn call_with_diff_i32() {
        let mut cacher = Cacher::new(|x| x);
        assert_eq!(&1, cacher.result(&1));
        assert_eq!(&2, cacher.result(&2));
    }

    #[test]
    fn call_with_diff_string() {
        let mut cacher = Cacher::new(|x| x);
        let a = String::from("apple");
        let b = String::from("banana");

        assert_eq!(&String::from("apple"), cacher.result(&a));
        assert_eq!(&String::from("banana"), cacher.result(&b));
    }
}