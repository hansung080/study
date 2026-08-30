#![allow(unused)]

// Generic Type Parameter
pub struct Queue<T> {
    older: Vec<T>,
    younger: Vec<T>,
}

impl<T> Queue<T> {
    pub fn new() -> Self {
        Queue {
            older: Vec::new(),
            younger: Vec::new(),
        }
    }

    pub fn push(&mut self, value: T) {
        self.younger.push(value);
    }

    pub fn pop(&mut self) -> Option<T> {
        if self.older.is_empty() {
            if self.younger.is_empty() {
                return None;
            }
            use std::mem::swap;
            swap(&mut self.older, &mut  self.younger);
            self.older.reverse();
        }
        self.older.pop()
    }

    pub fn is_empty(&self) -> bool {
        self.older.is_empty() && self.younger.is_empty()
    }

    pub fn split(self) -> (Vec<T>, Vec<T>) {
        (self.older, self.younger)
    }
}

// Generic Liftime Parameter (Liftime Annotation)
pub struct Extrema<'elt> {
    greatest: &'elt i32,
    least: &'elt i32,
}

// IntelliJ IDEA warning: Parameter types contain explict lifetimes that could be elided
pub fn find_extrema<'s>(slice: &'s [i32]) -> Extrema<'s> {
    let mut greatest = &slice[0];
    let mut least = &slice[0];
    for i in 1..slice.len() {
        if slice[i] > *greatest {
            greatest = &slice[i];
        }
        if slice[i] < *least {
            least = &slice[i];
        }
    }
    Extrema { greatest, least }
}

// Generic Const Parameter
//
// Polynomial<N> represents an (n − 1)th-degree polynomial:
//   c_0 + c_1x + c_2x^2 + ... + c_(n-1)x^(n-1)
pub struct Polynomial<const N: usize> {
    coefficients: [f64; N],
}

impl<const N: usize> Polynomial<N> {
    pub fn new(coefficients: [f64; N]) -> Self {
        Polynomial { coefficients }
    }

    // An (n − 1)th-degree polynomial represented by Horner's rule:
    //   c_0 + x(c_1 + x(c_2 + ... + x(c_(n-2) + xc_(n-1))))
    pub fn eval(&self, x: f64) -> f64 {
        let mut sum = 0.0;
        for i in (0..N).rev() {
            sum = self.coefficients[i] + x * sum
        }
        sum
    }
}

// Generic Type, Liftime, and Const Parameters
pub struct LumpOfReferences<'a, T, const N: usize> {
    the_lump: [&'a T; N],
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn queue() {
        let mut q = Queue::new();
        q.push('0');
        q.push('1');
        assert_eq!(q.pop(), Some('0'));

        q.push('∞');
        assert_eq!(q.pop(), Some('1'));
        assert_eq!(q.pop(), Some('∞'));
        assert_eq!(q.pop(), None);

        assert!(q.is_empty());
        q.push(' ');
        assert!(!q.is_empty());

        let mut q = Queue::new();
        q.push('P');
        q.push('D');
        q.push('E');
        assert_eq!(q.pop(), Some('P'));
        q.push('X');
        q.push('Y');

        let (older, younger) = q.split();
        assert_eq!(older, vec!['E', 'D']);
        assert_eq!(younger, vec!['X', 'Y']);

        // Receiver Adjustment
        //
        //   Repeatedly dereferences the receiver type to generate candidate receiver types,
        //   then adds `&T` and `&mut T` candidates for each type when searching for
        //   a matching method.
        //
        //   autoref:
        //     T -> &T
        //     T -> &mut T
        //
        //   autoderef:
        //     &T     -> T
        //     &mut T -> T
        //     T      -> U where T: Deref<Target = U>
        //
        // Deref Coercion
        //
        //   &T     -> &U     where T: Deref<Target = U>
        //   &mut T -> &U     where T: Deref<Target = U>
        //   &mut T -> &mut U where T: DerefMut<Target = U>
        //
        // Receiver Adjustment Example in bq.push()
        //
        //                 autoderef       autoref
        //   Box<Queue<char>> -> Queue<char> -> &mut Queue<char>
        //
        let mut bq: Box<Queue<char>> = Box::new(Queue::new());
        bq.push('■');
        assert_eq!(bq.pop(), Some('■'));

        // turbofish syntax (::<T>) for explicit generic arguments
        let _q = Queue::<char>::new();
    }

    #[test]
    fn extrema() {
        let a = [0, -3, 0, 15, 48];
        let e = find_extrema(&a);
        assert_eq!(*e.greatest, 48);
        assert_eq!(*e.least, -3);
    }

    #[test]
    fn polynomial() {
        use std::f64::consts::FRAC_PI_2; // π/2

        // Taylor series:
        //   f(x) = f(a) + f'(a)(x-a) + (f''(a)/2!)(x-a)^2 + ...
        //
        // Maclaurin series:
        //   f(x) = f(0) + f'(0)x + (f''(0)/2!)x^2 + ...
        //
        // Maclaurin series for sine:
        //   sin(x) = x - x^3/3! + x^5/5! - x^7/7! + ...
        //
        // Sine approximation:
        //   sin(x) ≈ x - 1/6x^3 + 1/120x^5
        let sine_poly = Polynomial::new(
            [0.0, 1.0, 0.0, -1.0/6.0, 0.0, 1.0/120.0],
        );
        assert_eq!(sine_poly.eval(0.0), 0.0);
        assert!((sine_poly.eval(FRAC_PI_2) - 1.0).abs() < 0.005);
    }

    #[test]
    fn lump_of_references() {
        let lump = LumpOfReferences {
            the_lump: [&1, &2, &3],
        };
        assert_eq!(lump.the_lump.len(), 3);
    }
}
