#include <stdio.h>
#include "binary_search_tree.h"

int main(int argc, const char** argv) {
    bt_node* root;
    bt_node* left;
    bt_node* right;

    /* Initialize AVL Tree */
    bst_init(&root);

    /* Insert data into AVL Tree */
    bt_data data1 = {1, 101};
    bt_data data2 = {2, 102};
    bt_data data3 = {3, 103};
    bt_data data4 = {4, 104};
    bt_data data5 = {5, 105};
    bt_data data6 = {6, 106};
    bt_data data7 = {7, 107};
    bt_data data8 = {8, 108};
    bt_data data9 = {9, 109};

    bst_insert(&root, data1);
    bst_insert(&root, data2);
    bst_insert(&root, data3);
    bst_insert(&root, data4);
    bst_insert(&root, data5);
    bst_insert(&root, data6);
    bst_insert(&root, data7);
    bst_insert(&root, data8);
    bst_insert(&root, data9);

    /* Print AVL Tree */
    printf("### AVL Tree Test ###\n");
    printf("root : %d\n", bt_get_data(root).key);

    left = bt_get_left(root);
    right = bt_get_right(root);
    printf("left1: %d, right1: %d\n", bt_get_data(left).key, bt_get_data(right).key);

    left = bt_get_left(left);
    right = bt_get_right(right);
    printf("left2: %d, right2: %d\n", bt_get_data(left).key, bt_get_data(right).key);
    
    left = bt_get_left(left);
    right = bt_get_right(right);
    printf("left3: %d, right3: %d\n", bt_get_data(left).key, bt_get_data(right).key);

    left = bt_get_left(left);
    right = bt_get_right(right);
    printf("left4: %d, right4: %d\n", bt_get_data(left).key, bt_get_data(right).key);
    return 0;
}

/*
    ### AVL Tree Test ###
    root : 5
    left1: 4, right1: 6
    left2: 3, right2: 7
    left3: 2, right3: 8
    left4: 1, right4: 9
*/