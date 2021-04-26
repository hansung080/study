#include <stdio.h>
#include <stdlib.h>
#include "binary_search_tree.h"

static void find_test(void) {
    bt_node* root;
    bt_node* found;

    /* Initialize Binary Search Tree */
    bst_init(&root);

    /* Insert data into Binary Search Tree */
    bt_data data9 = {9, 109};
    bt_data data1 = {1, 101};
    bt_data data6 = {6, 106};
    bt_data data2 = {2, 102};
    bt_data data8 = {8, 108};
    bt_data data3 = {3, 103};
    bt_data data5 = {5, 105};

    bst_insert_node(&root, data9);
    bst_insert_node(&root, data1);
    bst_insert_node(&root, data6);
    bst_insert_node(&root, data2);
    bst_insert_node(&root, data8);
    bst_insert_node(&root, data3);
    bst_insert_node(&root, data5);

    /* Find node from Binary Search Tree */
    bt_data data4 = {4, 104};
    bt_data data7 = {7, 107};

    printf("### Binary Search Tree Find Test ###\n");

    found = bst_find_node(root, data1);
    if (found != NULL) printf("find success: %d -> %d\n", bst_get_data(found).key, bst_get_data(found).value);
    else printf("find failure: %d\n", data1.key);

    found = bst_find_node(root, data4);
    if (found != NULL) printf("find success: %d -> %d\n", bst_get_data(found).key, bst_get_data(found).value);
    else printf("find failure: %d\n", data4.key);

    found = bst_find_node(root, data6);
    if (found != NULL) printf("find success: %d -> %d\n", bst_get_data(found).key, bst_get_data(found).value);
    else printf("find failure: %d\n", data6.key);

    found = bst_find_node(root, data7);
    if (found != NULL) printf("find success: %d -> %d\n", bst_get_data(found).key, bst_get_data(found).value);
    else printf("find failure: %d\n", data7.key);
}

/*
    ### Binary Search Tree Find Test ###
    find success: 1 -> 101
    find failure: 4
    find success: 6 -> 106
    find failure: 7
*/

static void remove_test(void) {
    bt_node* root;
    bt_node* removed;

    /* Initialize Binary Search Tree */
    bst_init(&root);

    /* Insert data into Binary Search Tree */
    bt_data data5 = {5, 105};
    bt_data data8 = {8, 108};
    bt_data data1 = {1, 101};
    bt_data data6 = {6, 106};
    bt_data data4 = {4, 104};
    bt_data data9 = {9, 109};
    bt_data data3 = {3, 103};
    bt_data data2 = {2, 102};
    bt_data data7 = {7, 107};

    bst_insert_node(&root, data5);
    bst_insert_node(&root, data8);
    bst_insert_node(&root, data1);
    bst_insert_node(&root, data6);
    bst_insert_node(&root, data4);
    bst_insert_node(&root, data9);
    bst_insert_node(&root, data3);
    bst_insert_node(&root, data2);
    bst_insert_node(&root, data7);

    /* Remove node from Binary Search Tree */
    printf("### Binary Search Tree Remove Test ###\n");
    bst_print_key(root);

    removed = bst_remove_node(&root, data3);
    free(removed);
    bst_print_key(root);

    removed = bst_remove_node(&root, data8);
    free(removed);
    bst_print_key(root);

    removed = bst_remove_node(&root, data1);
    free(removed);
    bst_print_key(root);

    removed = bst_remove_node(&root, data6);
    free(removed);
    bst_print_key(root);
}

/*
    ### Binary Search Tree Remove Test ###
    1 2 3 4 5 6 7 8 9
    1 2 4 5 6 7 8 9
    1 2 4 5 6 7 9
    2 4 5 6 7 9
    2 4 5 7 9
*/

int main(int argc, const char** argv) {
    find_test();
    printf("\n");
    remove_test();
    return 0;
}
