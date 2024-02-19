#include <stdarg.h>
#include "linked_list.h"

void init_ds__linked_list(test_t t[], int* n) {
    int i = *n;
    t[i++] = new_test("test/ds/gcd/test_ll_list_t", test_ll_list_t);
    *n = i;
}

bool __assert_eq_ll(const char* msg, const ll_list_t* list, int vargc, ...) {
    ll_data_t want[vargc];
    va_list ap;
    va_start(ap, vargc);
    for (int i = 0; i < vargc; ++i) want[i] = va_arg(ap, ll_data_t);
    va_end(ap);

    array_t got = ll_to_array(list);
    if (!assert_eq_arr(got.arr, got.elem_size * got.len, want, sizeof(want), TYPE_INT, msg)) {
        array_destroy(&got);
        return false;
    }
    array_destroy(&got);
    return true;
}

bool test_ll_list_t() {
    ll_list_t list = ll_new();
    ll_node_t* node = list.head;
    node = ll_insert_after(&list, node, 2);
    node = ll_insert_after(&list, node, 1);
    node = ll_insert_after(&list, node, 4);
    node = ll_insert_after(&list, node, 3);

    if (!assert_eq_ll("ll_insert_after(2, 1, 4, 3)", &list, 2, 1, 4, 3)) {
        return false;
    }

    ll_destroy(&list);
    return true;
}
