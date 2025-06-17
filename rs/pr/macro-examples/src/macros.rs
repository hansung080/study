// The `macro_export` attribute exports the macro in order to be used by other crates outside.
// And other crates can access the macro with paths.
#[macro_export]
macro_rules! my_assert_eq {
    ($left:expr, $right:expr $(,)?) => {
        match (&$left, &$right) {
            (left_val, right_val) => {
                if !(*left_val == *right_val) {
                    ::std::panic!("assertion `left == right` failed\n  \
                           left: {:?}\n right: {:?}",
                           &*left_val, &*right_val);
                }
            },
        }
    };
    ($left:expr, $right:expr, $($arg:tt)+) => {
        match (&$left, &$right) {
            (left_val, right_val) => {
                if !(*left_val == *right_val) {
                    ::std::panic!($($arg)+);
                }
            },
        }
    };
}

#[macro_export]
macro_rules! my_vec {
    () => {
        ::std::vec::Vec::new()
    };
    ($elem:expr; $n:expr) => {
        ::std::vec::from_elem($elem, $n)
    };
    ($($x:expr),+ $(,)?) => {
        <[_]>::into_vec(::std::boxed::Box::new([$($x),+]))
    };
}

#[allow(unused_macros)]
macro_rules! my_vec2 {
    ($elem:expr; $n:expr) =>  {
        ::std::vec::from_elem($elem, $n)
    };
    ($($x:expr),*) => {
        {
            #[allow(unused_mut)]
            let mut v = ::std::vec::Vec::new();
            $(v.push($x);)*
            v
        }
    };
    ($($x:expr),+ ,) => {
        my_vec2![$($x),+]
    }
}

#[macro_export]
macro_rules! json {
    (null) => {
        $crate::json::Json::Null
    };
    ([$($elem:tt),*]) => {
        $crate::json::Json::Array($crate::my_vec![$($crate::json!($elem)),*])
    };
    ({ $($key:tt: $value:tt),* }) => {
        // $crate::json::Json::Object(::std::boxed::Box::new($crate::my_vec![
        //     $(($key.to_string(), $crate::json!($value))),*
        // ].into_iter().collect()))

        {
            let mut fields = ::std::boxed::Box::new(::std::collections::HashMap::new());
            $(fields.insert(::std::string::ToString::to_string($key), $crate::json!($value));)*
            $crate::json::Json::Object(fields)
        }
    };
    ($other:tt) => {
        $crate::json::Json::from($other)
    };
}

#[cfg(test)]
mod tests {
    #[test]
    fn my_assert_eq() {
        my_assert_eq!(1, 1);
        my_assert_eq!(1, 1, );

        let mut v = my_vec![1, 2, 3];
        my_assert_eq!(v.pop(), Some(3));
        my_assert_eq!(v, my_vec![1, 2]);
    }

    #[test]
    #[should_panic]
    fn my_assert_eq_error1() {
        my_assert_eq!(1, 2);
    }

    #[test]
    #[should_panic(expected = "assertion failed: 1 != 2")]
    fn my_assert_eq_error2() {
        my_assert_eq!(1, 2, "assertion failed: {} != {}", 1, 2);
    }

    #[test]
    fn my_vec() {
        let v: Vec<()> = my_vec![];
        my_assert_eq!(v, vec![]);
        my_assert_eq!(my_vec![1; 3], vec![1, 1, 1]);
        my_assert_eq!(my_vec![1], vec![1]);
        my_assert_eq!(my_vec![1, 2], vec![1, 2]);
        my_assert_eq!(my_vec![1, 2, 3], vec![1, 2, 3]);
        my_assert_eq!(my_vec![1, 2, 3, ], vec![1, 2, 3]);
    }

    #[test]
    fn my_vec2() {
        let v: Vec<()> = my_vec2![];
        my_assert_eq!(v, vec![]);
        my_assert_eq!(my_vec2![1; 3], vec![1, 1, 1]);
        my_assert_eq!(my_vec2![1], vec![1]);
        my_assert_eq!(my_vec2![1, 2], vec![1, 2]);
        my_assert_eq!(my_vec2![1, 2, 3], vec![1, 2, 3]);
        my_assert_eq!(my_vec2![1, 2, 3, ], vec![1, 2, 3]);
    }
}