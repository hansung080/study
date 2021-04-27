#include <stdio.h>
#include "avl_rebalance.h"

static int avl_get_height(const bt_node* node) {
    int left;
    int right;

    if (node == NULL) return 0; 
    left = avl_get_height(bt_get_left(node));
    right = avl_get_height(bt_get_right(node));
    if (left > right) return left + 1;
    else return right + 1;
}

static int avl_get_height_diff(const bt_node* node) {
    int left;
    int right;

    if (node == NULL) return 0;
    left = avl_get_height(bt_get_left(node));
    right = avl_get_height(bt_get_right(node));
    return left - right;
}

static bt_node* avl_rotate_ll(bt_node* node) {
    bt_node* parent = node;
    bt_node* child = bt_get_left(parent);

    bt_change_left(parent, bt_get_right(child));
    bt_change_right(child, parent);
    return child;
}

static bt_node* avl_rotate_rr(bt_node* node) {
    bt_node* parent = node;
    bt_node* child = bt_get_right(parent);

    bt_change_right(parent, bt_get_left(child));
    bt_change_left(child, parent);
    return child;
}

static bt_node* avl_rotate_lr(bt_node* node) {
    bt_node* parent = node;
    bt_node* child = bt_get_left(parent);

    bt_change_left(parent, avl_rotate_rr(child));
    return avl_rotate_ll(parent);
}

static bt_node* avl_rotate_rl(bt_node* node) {
    bt_node* parent = node;
    bt_node* child = bt_get_right(parent);

    bt_change_right(parent, avl_rotate_ll(child));
    return avl_rotate_rr(parent);
}

void avl_rebalance(bt_node** root) {
    int diff = avl_get_height_diff(*root);
    if (diff > 1) {
        if (avl_get_height_diff(bt_get_left(*root)) > 0)
            *root = avl_rotate_ll(*root);
        else
            *root = avl_rotate_lr(*root);
    }

    if (diff < -1) {
        if (avl_get_height_diff(bt_get_right(*root)) < 0)
            *root = avl_rotate_rr(*root);
        else
            *root = avl_rotate_rl(*root);
    }
}
