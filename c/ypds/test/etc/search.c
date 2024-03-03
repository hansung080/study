#include <stdlib.h>
#include <ac1/src/util/array.h>
#include <ypds/src/etc/search.h>
#include "search.h"

void init_etc__search(t_test_t tests[], size_t* n) {
    tests[(*n)++] = t_new("test/etc/search/test_search", test_search);
}

bool test_search() {
    struct case_ {
        const int* arr;
        long len;
        int elem;
        long want;
    };

    int arr[] = {1, 2, 3, 4, 5, 6};

    struct case_ cases[] = {
        {arr, sizeof(arr) / sizeof(int), 1, 0},
        {arr, sizeof(arr) / sizeof(int), 4, 3},
        {arr, sizeof(arr) / sizeof(int), 6, 5},
        {arr, sizeof(arr) / sizeof(int), 7, -1},
    };

    int len = sizeof(cases) / sizeof(struct case_);
    for (int i = 0; i < len; ++i) {
        struct case_ c = cases[i];
        long got = lsearch_i(c.arr, c.len, c.elem);
        if (got != c.want) {
            char* str = arr_to_str_i(c.arr, c.len);
            t_fail("lsearch_i(%s, %d) => %ld, want %ld\n", str, c.elem, got, c.want);
            free(str);
            return false;
        }

        got = bsearch_i(c.arr, c.len, c.elem);
        if (got != c.want) {
            char* str = arr_to_str_i(c.arr, c.len);
            t_fail("bsearch_i(%s, %d) => %ld, want %ld\n", str, c.elem, got, c.want);
            free(str);
            return false;
        }
    }
    return true;
}
