#include <stdio.h>
#include "binary_tree.h"

/*
    Binary Tree
       1
     2   3
    4 5 6

    - preorder traverse:  1 2 4 5 3 6
    - inorder traverse:   4 2 5 1 6 3
    - postorder traverse: 4 5 2 6 3 1
*/

void action_print_data(bt_node* node) {
    printf("%d ", node->data);
}

int main(int argc, const char** argv) {
    /* Create Binary Tree */ 
    bt_node* node1 = bt_create_node();
    bt_node* node2 = bt_create_node();
    bt_node* node3 = bt_create_node();
    bt_node* node4 = bt_create_node();
    bt_node* node5 = bt_create_node();
    bt_node* node6 = bt_create_node();

    bt_set_data(node1, 1);
    bt_set_data(node2, 2);
    bt_set_data(node3, 3);
    bt_set_data(node4, 4);
    bt_set_data(node5, 5);
    bt_set_data(node6, 6);

    bt_set_left_node(node1, node2);
    bt_set_right_node(node1, node3);
    bt_set_left_node(node2, node4);
    bt_set_right_node(node2, node5);
    bt_set_left_node(node3, node6);

    /* Print Binary Tree */
    printf("Binary Tree\n");
    printf("   %d\n", bt_get_data(node1));
    printf(" %d", bt_get_data(bt_get_left_node(node1)));
    printf("   %d\n", bt_get_data(bt_get_right_node(node1)));
    printf("%d", bt_get_data(bt_get_left_node(bt_get_left_node(node1))));
    printf(" %d", bt_get_data(bt_get_right_node(bt_get_left_node(node1))));
    printf(" %d\n\n", bt_get_data(bt_get_left_node(bt_get_right_node(node1))));

    /* Traverse Binary Tree */
    printf("- preorder traverse:  ");
    bt_visit_pre(node1, action_print_data);
    printf("\n");

    printf("- inorder traverse:   ");
    bt_visit_in(node1, action_print_data);
    printf("\n");

    printf("- postorder traverse: ");
    bt_visit_post(node1, action_print_data);
    printf("\n");

    /* Delete Binary Tree */
    bt_delete_node(node1);
    return 0;
}
