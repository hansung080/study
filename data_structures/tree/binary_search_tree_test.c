#include <stdio.h>
#include "binary_search_tree.h"

int main(int argc, const char** argv) {
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

    bst_insert_data(&root, data9);
    bst_insert_data(&root, data1);
    bst_insert_data(&root, data6);
    bst_insert_data(&root, data2);
    bst_insert_data(&root, data8);
    bst_insert_data(&root, data3);
    bst_insert_data(&root, data5);

    /* Find node from Binary Search Tree */
    bt_data data4 = {4, 104};
    bt_data data7 = {7, 107};

    found = bst_find_node(root, data1);
    if (found != NULL) printf("search success: %d -> %d\n", bst_get_data(found).key, bst_get_data(found).value);
    else printf("search failure: %d\n", data1.key);

    found = bst_find_node(root, data4);
    if (found != NULL) printf("search success: %d -> %d\n", bst_get_data(found).key, bst_get_data(found).value);
    else printf("search failure: %d\n", data4.key);

    found = bst_find_node(root, data6);
    if (found != NULL) printf("search success: %d -> %d\n", bst_get_data(found).key, bst_get_data(found).value);
    else printf("search failure: %d\n", data6.key);

    found = bst_find_node(root, data7);
    if (found != NULL) printf("search success: %d -> %d\n", bst_get_data(found).key, bst_get_data(found).value);
    else printf("search failure: %d\n", data7.key);
    return 0;
}
