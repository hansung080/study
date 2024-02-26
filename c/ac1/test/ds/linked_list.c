#include <stdarg.h>
#include <ac1/src/util/string.h>
#include "linked_list.h"

void init_ds__linked_list(t_test_t tests[], size_t* n) {
    tests[(*n)++] = t_new("test/ds/linked_list/test_ll_list_t", test_ll_list_t);
    tests[(*n)++] = t_new("test/ds/linked_list/test_ll_insert_by_asc", test_ll_insert_by_asc);
    tests[(*n)++] = t_new("test/ds/linked_list/test_ll_insert_by_desc", test_ll_insert_by_desc);
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

    if ((node = ll_insert_prev(&list, 2, 5)) == NULL || node->data != 5) {
        t_fail("ll_insert_prev(2, 5) => %d, want 5\n", (node != NULL) ? node->data : 0);
        return false;           
    }
    ll_insert_prev(&list, 4, 6);
    ll_insert_prev(&list, 3, 7);
    if (!assert_eq_ll("ll_insert_prev(5, 6, 7)", &list, 5, 2, 1, 6, 4, 7, 3)) {
        return false;
    }

    if ((node = ll_insert_next(&list, 5, 8)) == NULL || node->data != 8) {
        t_fail("ll_insert_next(5, 8) => %d, want 8\n", (node != NULL) ? node->data : 0);
        return false;
    }
    ll_insert_next(&list, 6, 9);
    ll_insert_next(&list, 3, 10);
    if (!assert_eq_ll("ll_insert_next(8, 9, 10)", &list, 5, 8, 2, 1, 6, 9, 4, 7, 3, 10)) {
        return false;
    }

    bool ok;
    node = ll_find(&list, 5);
    if ((ok = ll_delete_after(&list, node)) != true) {
        t_fail("ll_delete_after(5) => %s, want true\n", bool_to_str(ok));
        return false;
    }
    node = ll_find(&list, 6);
    if ((ok = ll_delete_after(&list, node)) != true) {
        t_fail("ll_delete_after(6) => %s, want true\n", bool_to_str(ok));
        return false;
    }
    node = ll_find(&list, 10);
    if ((ok = ll_delete_after(&list, node)) != false) {
        t_fail("ll_delete_after(10) => %s, want false\n", bool_to_str(ok));
        return false;
    }
    if (!assert_eq_ll("ll_delete_after(5, 6, 10)", &list, 5, 2, 1, 6, 4, 7, 3, 10)) {
        return false;
    }

    if ((ok = ll_delete(&list, 5)) != true) {
        t_fail("ll_delete(5) => %s, want true\n", bool_to_str(ok));
        return false;
    }
    if ((ok = ll_delete(&list, 6)) != true) {
        t_fail("ll_delete(6) => %s, want true\n", bool_to_str(ok));
        return false;
    }
    if ((ok = ll_delete(&list, 10)) != true) {
        t_fail("ll_delete(5) => %s, want true\n", bool_to_str(ok));
        return false;
    }
    if (!assert_eq_ll("ll_delete(5, 6, 10)", &list, 2, 1, 4, 7, 3)) {
        return false;
    }

    size_t count;
    if ((count = ll_count(&list)) != 5) {
        t_fail("ll_count() => %lu, want 5\n", count);
        return false;
    }

    ll_delete_all(&list);
    if ((count = ll_count(&list)) != 0) {
        t_fail("ll_count() => %lu, want 0\n", count);
        return false;
    }

    ll_destroy(&list);
    return true;
}

bool test_ll_insert_by_asc() {
    ll_list_t list = ll_new();
    ll_insert_by_asc(&list, 2);
    ll_insert_by_asc(&list, 1);
    ll_insert_by_asc(&list, 4);
    ll_insert_by_asc(&list, 3);
    if (!assert_eq_ll("ll_insert_by_asc(2, 1, 4, 3)", &list, 1, 2, 3, 4)) {
        return false;
    }
    ll_destroy(&list);
    return true;
}

bool test_ll_insert_by_desc() {
    ll_list_t list = ll_new();
    ll_insert_by_desc(&list, 2);
    ll_insert_by_desc(&list, 1);
    ll_insert_by_desc(&list, 4);
    ll_insert_by_desc(&list, 3);
    if (!assert_eq_ll("ll_insert_by_desc(2, 1, 4, 3)", &list, 4, 3, 2, 1)) {
        return false;
    }
    ll_destroy(&list);
    return true;
}
