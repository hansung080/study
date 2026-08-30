#[derive(Debug, PartialEq)]
pub enum BinaryTree<T> {
    Empty,
    NonEmpty(Box<TreeNode<T>>),
}

impl<T: Ord> BinaryTree<T> {
    pub fn add(&mut self, value: T) {
        // Due to Rust's match ergonomics, explicit dereferencing and mutable borrowing
        // like the following can be omitted.
        // ```
        // match *self {
        //     BinaryTree::Empty => { ... },
        //     BinaryTree::NonEmpty(ref mut node) => { ... },
        // }
        // ```
        match self {
            BinaryTree::Empty => {
                *self = BinaryTree::NonEmpty(Box::new(TreeNode {
                    element: value,
                    left: BinaryTree::Empty,
                    right: BinaryTree::Empty,
                }))
            },
            BinaryTree::NonEmpty(node) => {
                if value <= node.element {
                    node.left.add(value)
                } else {
                    node.right.add(value)
                }
            },
        }
    }
}

#[derive(Debug, PartialEq)]
pub struct TreeNode<T> {
    element: T,
    left: BinaryTree<T>,
    right: BinaryTree<T>,
}

#[cfg(test)]
mod tests {
    use super::*;

    // 9 Planets:
    //   Mercury, Venus, Earth, Mars, Jupiter, Saturn, Uranus, Neptune, Pluto
    //
    // Binary Search Tree Example
    //
    //                Saturn
    //         Mars            Uranus
    //   Jupiter  Mercury           Venus
    //
    fn create_bst1() -> BinaryTree<&'static str> {
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

    fn create_bst2() -> BinaryTree<&'static str> {
        let mut tree = BinaryTree::Empty;
        let planets = ["Saturn", "Mars", "Uranus", "Jupiter", "Mercury", "Venus"];
        for planet in planets {
            tree.add(planet);
        }
        tree
    }

    #[test]
    fn binary_tree() {
        let bst1 = create_bst1();
        let bst2 = create_bst2();
        assert_eq!(bst1, bst2)
    }
}
