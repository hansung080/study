#include <stdio.h>
#include "binary_search_tree.h"

void bst_init(bt_node** root) {
    *root = NULL;
}

void bst_insert_data(bt_node** root, bt_data data) {
    bt_node* current = *root;
    bt_node* parent = NULL;
    bt_node* new = NULL;
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
