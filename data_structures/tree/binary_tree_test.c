#include <stdio.h>
#include "binary_tree.h"

/*
    Binary Tree (Key)
       1
     2   3
    4 5 6

    - preorder traverse:  1 2 4 5 3 6
    - inorder traverse:   4 2 5 1 6 3
    - postorder traverse: 4 5 2 6 3 1
*/

void action_print_data(bt_node* node) {
    printf("%d ", node->data.key);
}

int main(int argc, const char** argv) {
    /* Create Binary Tree */ 
    bt_node* node1 = bt_create_node();
    bt_node* node2 = bt_create_node();
    bt_node* node3 = bt_create_node();
    bt_node* node4 = bt_create_node();
    bt_node* node5 = bt_create_node();
    bt_node* node6 = bt_create_node();

    bt_data data1 = {1, 'a'};
    bt_data data2 = {2, 'b'};
    bt_data data3 = {3, 'c'};
    bt_data data4 = {4, 'd'};
    bt_data data5 = {5, 'e'};
    bt_data data6 = {6, 'f'};

    bt_set_data(node1, data1);
    bt_set_data(node2, data2);
    bt_set_data(node3, data3);
    bt_set_data(node4, data4);
    bt_set_data(node5, data5);
    bt_set_data(node6, data6);

    bt_set_left_node(node1, node2);
    bt_set_right_node(node1, node3);
    bt_set_left_node(node2, node4);
    bt_set_right_node(node2, node5);
    bt_set_left_node(node3, node6);

    /* Print Binary Tree (Key) */
    printf("Binary Tree (Key) \n");
    printf("   %d\n", bt_get_data(node1).key);
    printf(" %d", bt_get_data(bt_get_left_node(node1)).key);
    printf("   %d\n", bt_get_data(bt_get_right_node(node1)).key);
    printf("%d", bt_get_data(bt_get_left_node(bt_get_left_node(node1))).key);
    printf(" %d", bt_get_data(bt_get_right_node(bt_get_left_node(node1))).key);
    printf(" %d\n\n", bt_get_data(bt_get_left_node(bt_get_right_node(node1))).key);

    /* Traverse Binary Tree (Key) */
    printf("- preorder traverse:  ");
    bt_visit_pre(node1, action_print_data);
    printf("\n");

    printf("- inorder traverse:   ");
    bt_visit_in(node1, action_print_data);
    printf("\n");

    printf("- postorder traverse: ");
    bt_visit_post(node1, action_print_data);
    printf("\n\n");

    /* Print Binary Tree (Value) */
    printf("Binary Tree (Value) \n");
    printf("   %c\n", bt_get_data(node1).value);
    printf(" %c", bt_get_data(bt_get_left_node(node1)).value);
    printf("   %c\n", bt_get_data(bt_get_right_node(node1)).value);
    printf("%c", bt_get_data(bt_get_left_node(bt_get_left_node(node1))).value);
    printf(" %c", bt_get_data(bt_get_right_node(bt_get_left_node(node1))).value);
    printf(" %c\n\n", bt_get_data(bt_get_left_node(bt_get_right_node(node1))).value);

    /* Delete Binary Tree */
    bt_delete(node1);
    return 0;
}
