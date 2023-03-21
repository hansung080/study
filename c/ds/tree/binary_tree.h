#ifndef __BINARY_TREE_H__
#define __BINARY_TREE_H__

#pragma pack(push, 1)

// bt_data represents a node's data.
typedef struct _bt_data {
    int key;
    int value;
} bt_data;

// bt_node represents a binary tree's node and a binary tree itself.
typedef struct _bt_node {
    bt_data data;
    struct _bt_node* left;
    struct _bt_node* right;
} bt_node;

#pragma pack(pop)

/* Basic Functions */
bt_node* bt_create_node(void);
void bt_set_data(bt_node* node, bt_data data);
bt_data bt_get_data(const bt_node* node);
void bt_set_left(bt_node* node, bt_node* left);
void bt_set_right(bt_node* node, bt_node* right);
void bt_change_left(bt_node* node, bt_node* left);
void bt_change_right(bt_node* node, bt_node* right);
bt_node* bt_get_left(const bt_node* node);
bt_node* bt_get_right(const bt_node* node);
bt_node* bt_remove_left(bt_node* node);
bt_node* bt_remove_right(bt_node* node);
void bt_delete_left(bt_node* node);
void bt_delete_right(bt_node* node);
void bt_delete_all(bt_node* node);

/* Traverse Functions */
typedef void bt_action(bt_node* node);
void bt_visit_pre(bt_node* node, bt_action action);
void bt_visit_in(bt_node* node, bt_action action);
void bt_visit_post(bt_node* node, bt_action action);

#endif // __BINARY_TREE_H__