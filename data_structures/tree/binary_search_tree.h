#ifndef __BINARY_SEARCH_TREE_H__
#define __BINARY_SEARCH_TREE_H__

#include "binary_tree.h"

void bst_init(bt_node** root);
void bst_insert(bt_node** root, bt_data data);
bt_node* bst_find(bt_node* root, bt_data data);
bt_data bst_get_data(const bt_node* node);
bt_node* bst_remove(bt_node** root, bt_data data);
void bst_delete(bt_node** root, bt_data data);
void bst_print_key(bt_node* root);

#endif // __BINARY_SEARCH_TREE_H__