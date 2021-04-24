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

bt_node* bt_make_node(void);
void bt_set_data(bt_node* node, bt_data data);
bt_data bt_get_data(bt_node* node);
void bt_set_left_subtree(bt_node* node, bt_node* left);
void bt_set_right_subtree(bt_node* node, bt_node* right);
bt_node* bt_get_left_subtree(bt_node* node);
bt_node* bt_get_right_subtree(bt_node* node);

#endif // __BINARY_TREE_H__