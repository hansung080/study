#ifndef __BINARY_SEARCH_TREE_H__
#define __BINARY_SEARCH_TREE_H__

#include "binary_tree.h"

void bst_init(bt_node** root);
void bst_insert_node(bt_node** root, bt_data data);
bt_node* bst_find_node(bt_node* root, bt_data data);
bt_data bst_get_data(bt_node* node);
bt_node* bst_remove_node(bt_node** root, bt_data data);
void bst_print_data(bt_node* node);

#endif // __BINARY_SEARCH_TREE_H__