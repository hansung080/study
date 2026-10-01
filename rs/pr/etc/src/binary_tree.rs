#[derive(Debug, PartialEq)]
pub enum BinaryTree<T> {
    Empty,
    NonEmpty(Box<TreeNode<T>>),
}

impl<T: Ord> BinaryTree<T> {
    pub fn add(&mut self, element: T) {
        // Due to Rust's ergonomics, explicit dereferencing and borrowing can be omitted.
        // ```
        // match *self {
        //     BinaryTree::Empty => { ... },
        //     BinaryTree::NonEmpty(ref mut node) => { ... },
        // }
        // ```
        match self {
            BinaryTree::Empty => {
                *self = BinaryTree::NonEmpty(Box::new(TreeNode {
                    element,
                    left: BinaryTree::Empty,
                    right: BinaryTree::Empty,
                }))
            },
            BinaryTree::NonEmpty(node) => {
                if element <= node.element {
                    node.left.add(element)
                } else {
                    node.right.add(element)
                }
            },
        }
    }

    pub fn iter(&self) -> TreeIter<T> {
        TreeIter::new(self)
    }
}

impl<'a, T: 'a + Ord> IntoIterator for &'a BinaryTree<T> {
    type Item = &'a T;
    type IntoIter = TreeIter<'a, T>;

    fn into_iter(self) -> Self::IntoIter {
        self.iter()
    }
}

#[derive(Debug, PartialEq)]
pub struct TreeNode<T> {
    element: T,
    left: BinaryTree<T>,
    right: BinaryTree<T>,
}

// `TreeIter` performs an in-order traversal of a `BinaryTree`.
pub struct TreeIter<'a, T> {
    // The node to be visited next is at the top of the stack, and its unvisited ancestors
    // are below it. The iteration ends when the stack becomes empty.
    unvisited: Vec<&'a TreeNode<T>>,
}

impl<'a, T: 'a> TreeIter<'a, T> {
    pub fn new(tree: &'a BinaryTree<T>) -> Self {
        let mut iter = TreeIter { unvisited: Vec::new() };
        iter.push_left_edge(tree);
        iter
    }

    fn push_left_edge(&mut self, mut tree: &'a BinaryTree<T>) {
        // Due to Rust's ergonomics, explicit dereferencing and borrowing can be omitted.
        // `while let BinaryTree::NonEmpty(ref node) = *tree`
        while let BinaryTree::NonEmpty(node) = tree {
            self.unvisited.push(node);
            tree = &node.left;
        }
    }
}

impl<'a, T> Iterator for TreeIter<'a, T> {
    type Item = &'a T;

    fn next(&mut self) -> Option<Self::Item> {
        let node = self.unvisited.pop()?;
        self.push_left_edge(&node.right);
        Some(&node.element)
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    // 9 Planets:
    //   Mercury, Venus, Earth, Mars, Jupiter, Saturn, Uranus, Neptune, Pluto
    //
    // Planet Tree
    //
    //                Saturn
    //         Mars            Uranus
    //   Jupiter  Mercury           Venus
    //
    fn create_planet_tree1() -> BinaryTree<&'static str> {
        use super::BinaryTree::*;

        let jupiter = NonEmpty(Box::new(TreeNode {
            element: "Jupiter",
            left: Empty,
            right: Empty,
        }));
        let mercury = NonEmpty(Box::new(TreeNode {
            element: "Mercury",
            left: Empty,
            right: Empty,
        }));
        let mars = NonEmpty(Box::new(TreeNode {
            element: "Mars",
            left: jupiter,
            right: mercury,
        }));

        let venus = NonEmpty(Box::new(TreeNode {
            element: "Venus",
            left: Empty,
            right: Empty,
        }));
        let uranus = NonEmpty(Box::new(TreeNode {
            element: "Uranus",
            left: Empty,
            right: venus,
        }));

        let saturn = NonEmpty(Box::new(TreeNode {
            element: "Saturn",
            left: mars,
            right: uranus,
        }));

        saturn
    }

    fn create_planet_tree2() -> BinaryTree<&'static str> {
        let mut tree = BinaryTree::Empty;
        let planets = ["Saturn", "Mars", "Uranus", "Jupiter", "Mercury", "Venus"];
        for planet in planets {
            tree.add(planet);
        }
        tree
    }

    #[test]
    fn binary_tree() {
        let bst1 = create_planet_tree1();
        let bst2 = create_planet_tree2();
        assert_eq!(bst1, bst2)
    }

    #[test]
    fn tree_iter() {
        let mut tree = BinaryTree::Empty;
        let robots = ["jaeger", "robot", "droid", "mecha"];
        for robot in robots {
            tree.add(robot);
        }

        let mut v = Vec::new();
        for &robot in &tree {
            v.push(robot);
        }
        assert_eq!(v, ["droid", "jaeger", "mecha", "robot"]);

        let mapped: Vec<_> = tree.iter()
            .map(|robot| format!("mega-{}", robot))
            .collect();
        assert_eq!(mapped, vec!["mega-droid", "mega-jaeger", "mega-mecha", "mega-robot"])
    }
}
