#include <stdlib.h>
#include "binary_tree.h"

bt_node* bt_create_node(void) {
    bt_node* node = (bt_node*)malloc(sizeof(bt_node));
    node->left = NULL;
    node->right = NULL;
    return node;
}

void bt_set_data(bt_node* node, bt_data data) {
    node->data = data;
}

bt_data bt_get_data(const bt_node* node) {
    return node->data;
}

void bt_set_left_node(bt_node* node, bt_node* left) {
    if (node->left != NULL) bt_delete_node(node->left);
    node->left = left;
}

void bt_set_right_node(bt_node* node, bt_node* right) {
    if (node->right != NULL) bt_delete_node(node->right);
    node->right = right;
}

void bt_change_left_node(bt_node* node, bt_node* left) {
    node->left = left;
}

void bt_change_right_node(bt_node* node, bt_node* right) {
    node->right = right;
}

bt_node* bt_get_left_node(const bt_node* node) {
    return node->left;
}

bt_node* bt_get_right_node(const bt_node* node) {
    return node->right;
}

bt_node* bt_remove_left_node(bt_node* node) {
    bt_node* remove = NULL;
    if (node != NULL) {
        remove = node->left;
        node->left = NULL;
    }
    return remove;
}

bt_node* bt_remove_right_node(bt_node* node) {
    bt_node* remove = NULL;
    if (node != NULL) {
        remove = node->right;
        node->right = NULL;
    }
    return remove;
}

void bt_delete_left_node(bt_node* node) {
    if (node != NULL && node->left != NULL) {
        bt_delete_node(node->left);
        node->left = NULL;
    }
}

void bt_delete_right_node(bt_node* node) {
    if (node != NULL && node->right != NULL) {
        bt_delete_node(node->right);
        node->right = NULL;
    }
}

static void action_delete_node(bt_node* node) {
    free(node);
}

void bt_delete_node(bt_node* node) {
    bt_visit_post(node, action_delete_node);
}

void bt_visit_pre(bt_node* node, bt_action action) {
    if (node == NULL) return;
    action(node);
    bt_visit_pre(node->left, action);
    bt_visit_pre(node->right, action);
}

void bt_visit_in(bt_node* node, bt_action action) {
    if (node == NULL) return;
    bt_visit_in(node->left, action);
    action(node);
    bt_visit_in(node->right, action);
}

void bt_visit_post(bt_node* node, bt_action action) {
    if (node == NULL) return;
    bt_visit_post(node->left, action);
    bt_visit_post(node->right, action);
    action(node);
}
