#include <stdio.h>
#include <stdlib.h>
#include "binary_search_tree.h"
#include "avl_rebalance.h"

void bst_init(bt_node** root) {
    *root = NULL;
}

void bst_insert(bt_node** root, bt_data data) {
    bt_node* parent = NULL;
    bt_node* current = *root;
    bt_node* new;
    int current_key;

    /* Find the position for a new node */
    while (current != NULL) {
        current_key = bt_get_data(current).key;

        // The key can't be duplicated.
        if (data.key == current_key) return;

        parent = current;

        if (data.key < current_key)
            current = bt_get_left(current);
        else
            current = bt_get_right(current);
    }

    /* Create a new node */
    new = bt_create_node();
    bt_set_data(new, data);

    /* Connect a new node to a parent node */
    if (parent != NULL) {
        if (data.key < bt_get_data(parent).key)
            bt_set_left(parent, new);
        else
            bt_set_right(parent, new);
    } else {
        *root = new;
    }

    avl_rebalance(root);
}

bt_node* bst_find(bt_node* root, bt_data data) {
    bt_node* current = root;
    int current_key;

    /* Find the target node */
    while (current != NULL) {
        current_key = bt_get_data(current).key;
        if (data.key == current_key)
            return current;
        else if (data.key < current_key)
            current = bt_get_left(current);
        else
            current = bt_get_right(current);
    }

    return NULL;  
}

bt_data bst_get_data(const bt_node* node) {
    return bt_get_data(node);
}

bt_node* bst_remove(bt_node** root, bt_data data) {
    // This virtual root node is created to get rid of the special case
    // that the removing node is the root node.
    bt_node* virtual = bt_create_node();
    bt_node* parent = virtual;
    bt_node* current = *root;
    bt_node* remove;
    int current_key;

    bt_change_right(virtual, *root);

    /* Find the removing node */
    while (current != NULL && data.key != (current_key = bt_get_data(current).key)) {
        parent = current;
        if (data.key < current_key)
            current = bt_get_left(current);
        else
            current = bt_get_right(current);
    }

    if (current == NULL) return NULL;

    remove = current;

    /* If the removing node has no children */
    if (bt_get_left(remove) == NULL && bt_get_right(remove) == NULL) {
        if (remove == bt_get_left(parent))
            bt_remove_left(parent);
        else
            bt_remove_right(parent);

    /* If the removing node has one child */
    } else if (bt_get_left(remove) == NULL || bt_get_right(remove) == NULL) {
        bt_node* child;
        if (bt_get_left(remove) != NULL)
            child = bt_get_left(remove);
        else
            child = bt_get_right(remove);

        if (remove == bt_get_left(parent))
            bt_change_left(parent, child);
        else
            bt_change_right(parent, child);

    /* If the removing node has two children */
    } else {
        // The substitute node will be the node with the minimum key 
        // in the right subtree of the removing node.
        bt_node* sub = bt_get_right(remove);
        bt_node* sub_parent = remove;
        bt_data remove_data;

        while (bt_get_left(sub) != NULL) {
            sub_parent = sub;
            sub = bt_get_left(sub);
        }

        remove_data = bt_get_data(remove);
        bt_set_data(remove, bt_get_data(sub));

        if (sub == bt_get_left(sub_parent))
            bt_change_left(sub_parent, bt_get_right(sub));
        else
            bt_change_right(sub_parent, bt_get_right(sub));
        
        remove = sub;
        bt_set_data(remove, remove_data);
    }

    // If the removing node is the root node
    if (bt_get_right(virtual) != *root)
        *root = bt_get_right(virtual);
    
    free(virtual);
    avl_rebalance(root);
    return remove;
}

void bst_delete(bt_node** root, bt_data data) {
    free(bst_remove(root, data));
}

static void action_print_key(bt_node* node) {
    printf("%d ", node->data.key);
}

void bst_print_key(bt_node* root) {
    bt_visit_in(root, action_print_key);
    printf("\n");
}
