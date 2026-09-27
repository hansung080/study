use crate::cons_list::List::{Cons, Nil};

#[derive(Debug)]
pub enum List<T> {
    Cons(T, Box<List<T>>),
    Nil,
}

impl<T> List<T> {
    pub fn car(&self) -> Option<&T> {
        match self {
            Cons(value, _) => Some(value),
            Nil => None,
        }
    }

    pub fn car_mut(&mut self) -> Option<&mut T> {
        match self {
            Cons(value, _) => Some(value),
            Nil => None,
        }
    }

    pub fn cdr(&self) -> &List<T> {
        match self {
            Cons(_, next) => next,
            Nil => self,
        }
    }

    pub fn cdr_mut(&mut self) -> &mut List<T> {
        match self {
            Cons(_, next) => next,
            Nil => self,
        }
    }

    pub fn iter(&self) -> Iter<T> {
        Iter::new(self)
    }

    pub fn iter_mut(&mut self) -> IterMut<T> {
        IterMut::new(self)
    }
}

pub struct Iter<'a, T: 'a> {
    current: &'a List<T>,
}

impl<'a, T> Iter<'a, T> {
    pub fn new(head: &'a List<T>) -> Self {
        Iter { current: head }
    }
}

impl<'a, T> Iterator for Iter<'a, T> {
    type Item = &'a T;

    fn next(&mut self) -> Option<Self::Item> {
        let value = self.current.car();
        self.current = self.current.cdr();
        value
    }
}

pub struct IterMut<'a, T: 'a> {
    current: &'a mut List<T>,
}

impl<'a, T> IterMut<'a, T> {
    pub fn new(head: &'a mut List<T>) -> Self {
        IterMut { current: head }
    }
}

impl<'a, T> Iterator for IterMut<'a, T> {
    type Item = &'a mut T;

    fn next(&mut self) -> Option<Self::Item> {
        let value = match self.current.car_mut() {
            Some(value) => Some(unsafe { &mut *(value as *mut T) }),
            None => None,
        };
        self.current = unsafe { &mut *(self.current.cdr_mut() as *mut List<T>) };
        value
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn list_car_cdr() {
        let list = Cons(1, Box::new(Cons(2, Box::new(Cons(3, Box::new(Nil))))));
        assert_eq!(Some(&1), list.car());
        assert_eq!(Some(&2), list.cdr().car());
        assert_eq!(Some(&3), list.cdr().cdr().car());
        assert_eq!(None, list.cdr().cdr().cdr().car());
    }

    #[test]
    fn list_iter() {
        let list = Cons(1, Box::new(Cons(2, Box::new(Cons(3, Box::new(Nil))))));
        let mut sum = 0;
        for item in list.iter() {
            sum += item;
        }
        assert_eq!(6, sum);

        let v: Vec<&i32> = list.iter().collect();
        assert_eq!(vec![&1, &2, &3], v);

        let v: Vec<&i32> = list.iter().filter(|&item| item % 2 == 1).collect();
        assert_eq!(vec![&1, &3], v);

        let v: Vec<i32> = list.iter().map(|item| item * 2).collect();
        assert_eq!(vec![2, 4, 6], v);

        let sum: i32 = list.iter().sum();
        assert_eq!(6, sum);
    }

    #[test]
    fn list_iter_mut() {
        let mut list = Cons(1, Box::new(Cons(2, Box::new(Cons(3, Box::new(Nil))))));
        for item in list.iter_mut() {
            *item *= 2;
        }
        let v: Vec<&mut i32> = list.iter_mut().collect();
        assert_eq!(vec![&mut 2, &mut 4, &mut 6], v);
    }
}
