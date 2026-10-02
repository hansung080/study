use std::collections::HashSet;
use std::hash::Hash;

pub fn dedup<T>(v: &mut Vec<T>) -> &mut Vec<T>
where
    T: Eq + Hash + Copy,
{
    let mut seen = HashSet::new();
    v.retain(|&x| seen.insert(x));
    v
}

#[cfg(test)]
mod tests {

    #[test]
    fn dedup() {
        // Vector's adjacent-only deduplication methods:
        //   vec.dedup()
        //   vec.dedup_by(same)    where same(&mut elem1, &mut elem1)
        //   vec.dedup_by_key(key) where key(&mut elem1) == key(&mut elem2)
        //     e.g. errors.dedup_by_key(|err| err.to_string())
        let mut byte_vec = b"Misssssssissippi".to_vec();
        byte_vec.dedup();
        assert_eq!(byte_vec, b"Misisipi");

        // Custom deduplication function
        let mut byte_vec = b"Misssssssissippi".to_vec();
        super::dedup(&mut byte_vec);
        assert_eq!(byte_vec, b"Misp");
    }
}
