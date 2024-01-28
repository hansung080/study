#include <stdio.h>
#include <ac1/src/util/array.h>
#include "array.h"

void init_util__array(test_t t[], int* n) {
    int i = *n;
    t[i++] = new_test("test/util/array/test_a_equals", test_a_equals);
    *n = i;
}

bool test_a_equals() {
    struct case_ {
        const int* arr1;
        size_t len1;
        const int* arr2;
        size_t len2;
        bool want;
    };

    int arr[] = {1, 2, 3};

    struct case_ cases[] = {
        {arr, 3, arr, 3, true},
    };

    int len = sizeof(cases) / sizeof(struct case_);
    //printf("len: %d\n", len);
    for (int i = 0; i < len; ++i) {
        struct case_ c = cases[i];
        bool got = a_equals(c.arr1, c.len1, c.arr2, c.len2);
        if (got != c.want) {
            //fprintf(stderr, LOG_FAILED": s_contains('%s', '%s') => %s, want %s\n", c.s, c.keyword, bool2str(got), bool2str(c.want));
            fprintf(stderr, LOG_FAILED": a_equals\n");
            return false;
        }

    }
    return true;
}
