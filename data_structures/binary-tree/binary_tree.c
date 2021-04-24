#include <stdlib.h>
#include "binary_tree.h"

bt_node* bt_make_node(void) {
    bt_node* node = (bt_node*)malloc(sizeof(bt_node));
    node->left = NULL;
    node->right = NULL;
    return node;
}

void bt_set_data(bt_node* node, bt_data data) {
    node->data = data;
}

bt_data bt_get_data(bt_node* node) {
    return node->data;
}

void bt_set_left_subtree(bt_node* node, bt_node* left) {
    if (node->left != NULL) free(node->left);
    node->left = left;
}

void bt_set_right_subtree(bt_node* node, bt_node* right) {
    if (node->right != NULL) free(node->right);
    node->right = right;
}

bt_node* bt_get_left_subtree(bt_node* node) {
    return node->left;
}

bt_node* bt_get_right_subtree(bt_node* node) {
    return node->right;
}