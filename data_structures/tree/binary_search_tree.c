#include <stdio.h>
#include <stdlib.h>
#include "binary_search_tree.h"

void bst_init(bt_node** root) {
    *root = NULL;
}

void bst_insert_node(bt_node** root, bt_data data) {
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
            current = bt_get_left_node(current);
        else
            current = bt_get_right_node(current);
    }

    /* Create a new node */
    new = bt_create_node();
    bt_set_data(new, data);

    /* Connect a new node to a parent node */
    if (parent != NULL) {
        if (data.key < bt_get_data(parent).key)
            bt_set_left_node(parent, new);
        else
            bt_set_right_node(parent, new);
    } else {
        *root = new;
    }
}

bt_node* bst_find_node(bt_node* root, bt_data data) {
    bt_node* current = root;
    int current_key;

    /* Find the target node */
    while (current != NULL) {
        current_key = bt_get_data(current).key;
        if (data.key == current_key)
            return current;
        else if (data.key < current_key)
            current = bt_get_left_node(current);
        else
            current = bt_get_right_node(current);
    }

    return NULL;  
}

bt_data bst_get_data(bt_node* node) {
    return bt_get_data(node);
}

bt_node* bst_remove_node(bt_node** root, bt_data data) {
    // This virtual root node is created to get rid of the special case
    // that the removing node is the root node.
    bt_node* virtual = bt_create_node();
    bt_node* parent = virtual;
    bt_node* current = *root;
    bt_node* remove;
    int current_key;

    bt_change_right_node(virtual, *root);

    /* Find the removing node */
    while (current != NULL && data.key != (current_key = bt_get_data(current).key)) {
        parent = current;
        if (data.key < current_key)
            current = bt_get_left_node(current);
        else
            current = bt_get_right_node(current);
    }

    if (current == NULL) return NULL;

    remove = current;

    /* If the removing node has no children */
    if (bt_get_left_node(remove) == NULL && bt_get_right_node(remove) == NULL) {
        if (remove == bt_get_left_node(parent))
            bt_remove_left_node(parent);
        else
            bt_remove_right_node(parent);

    /* If the removing node has one child */
    } else if (bt_get_left_node(remove) == NULL || bt_get_right_node(remove) == NULL) {
        bt_node* child;
        if (bt_get_left_node(remove) != NULL)
            child = bt_get_left_node(remove);
        else
            child = bt_get_right_node(remove);

        if (remove == bt_get_left_node(parent))
            bt_change_left_node(parent, child);
        else
            bt_change_right_node(parent, child);

    /* If the removing node has two children */
    } else {
        // The substitute node will be the node with the minimum key 
        // in the right subtree of the removing node.
        bt_node* sub = bt_get_right_node(remove);
        bt_node* sub_parent = remove;
        bt_data remove_data;

        while (bt_get_left_node(sub) != NULL) {
            sub_parent = sub;
            sub = bt_get_left_node(sub);
        }

        remove_data = bt_get_data(remove);
        bt_set_data(remove, bt_get_data(sub));

        if (sub == bt_get_left_node(sub_parent))
            bt_change_left_node(sub_parent, bt_get_right_node(sub));
        else
            bt_change_right_node(sub_parent, bt_get_right_node(sub));
        
        remove = sub;
        bt_set_data(remove, remove_data);
    }

    // If the removing node is the root node
    if (bt_get_right_node(virtual) != *root)
        *root = bt_get_right_node(virtual);
    
    free(virtual);
    return remove;
}

static void action_print_data(bt_node* node) {
    printf("%d ", node->data.key);
}

void bst_print_data(bt_node* node) {
    bt_visit_in(node, action_print_data);
}
