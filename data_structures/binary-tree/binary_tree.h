#ifndef __BINARY_TREE_H__
#define __BINARY_TREE_H__

typedef int bt_data;

#pragma pack(push, 1)

// bt_node represents a binary tree's node and a binary tree itself.
typedef struct _bt_node {
    bt_data data;
    struct _bt_node* left;
    struct _bt_node* right;
} bt_node;

#pragma pack(pop)

/* Basic Functions */
bt_node* bt_create_node(void);
void bt_delete_node(bt_node* node);
void bt_set_data(bt_node* node, bt_data data);
bt_data bt_get_data(bt_node* node);
void bt_set_left_node(bt_node* node, bt_node* left);
void bt_set_right_node(bt_node* node, bt_node* right);
bt_node* bt_get_left_node(bt_node* node);
bt_node* bt_get_right_node(bt_node* node);

/* Traverse Functions */
typedef void bt_action(bt_node* node);
void bt_visit_pre(bt_node* node, bt_action action);
void bt_visit_in(bt_node* node, bt_action action);
void bt_visit_post(bt_node* node, bt_action action);

#endif // __BINARY_TREE_H__