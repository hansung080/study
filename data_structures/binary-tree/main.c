#include <stdio.h>
#include "binary_tree.h"

/*
    Binary Tree
        1
      2   3
    4  
*/
int main(int argc, const char** argv) {
    bt_node* node1 = bt_make_node();
    bt_node* node2 = bt_make_node();
    bt_node* node3 = bt_make_node();
    bt_node* node4 = bt_make_node();

    bt_set_data(node1, 1);
    bt_set_data(node2, 2);
    bt_set_data(node3, 3);
    bt_set_data(node4, 4);

    bt_set_left_subtree(node1, node2);
    bt_set_right_subtree(node1, node3);
    bt_set_left_subtree(node2, node4);

    printf("    %d\n", bt_get_data(node1));
    printf("  %d", bt_get_data(bt_get_left_subtree(node1)));
    printf("   %d\n", bt_get_data(bt_get_right_subtree(node1)));
    printf("%d\n", bt_get_data(bt_get_left_subtree(bt_get_left_subtree(node1))));
    return 0;
}
