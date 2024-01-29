#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ac1/src/util/array.h>
#include "array.h"

void init_util__array(test_t t[], int* n) {
    int i = *n;
    t[i++] = new_test("test/util/array/test_arr2str", test_arr2str);
    t[i++] = new_test("test/util/array/test_a_equals", test_a_equals);
    *n = i;
}

bool has_negative(const int* arr, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        if (arr[i] < 0) return true;
    }
    return false;
}

bool test_arr2str() {
    struct case_ {
        const int* arr;
        size_t len;
        const char* want;
        bool has_negative;
    };

    int arr1[] = {};
    int arr2[] = {98765};
    int arr3[] = {0, 1, 12, 123};
    int arr4[] = {-98765};
    int arr5[] = {0, -1, 12, -123};

    size_t len1 = sizeof(arr1) / sizeof(int);
    size_t len2 = sizeof(arr2) / sizeof(int);
    size_t len3 = sizeof(arr3) / sizeof(int);
    size_t len4 = sizeof(arr4) / sizeof(int);
    size_t len5 = sizeof(arr5) / sizeof(int);

    struct case_ cases[] = {
        {NULL, 0, "[]"},
        {arr1, len1, "[]", has_negative(arr1, len1)},
        {arr2, len2, "[98765]", has_negative(arr2, len2)},
        {arr3, len3, "[0, 1, 12, 123]", has_negative(arr3, len3)},
        {arr4, len4, "[-98765]", has_negative(arr4, len4)},
        {arr5, len5, "[0, -1, 12, -123]", has_negative(arr5, len5)},
    };

    int len = sizeof(cases) / sizeof(struct case_);
    for (int i = 0; i < len; ++i) {
        struct case_ c = cases[i];
        char* got = int_arr2str(c.arr, c.len);
        if (got == NULL || strcmp(got, c.want) != 0) {
            fprintf(stderr, LOG_FAILED": int_arr2str(arr%d, %lu) => %s, want %s\n", i, c.len, got, c.want);
            if (got != NULL) free(got);
            return false;
        }
        free(got);

        if (!c.has_negative) {
            got = uint_arr2str((const uint*)c.arr, c.len);
            if (got == NULL || strcmp(got, c.want) != 0) {
                fprintf(stderr, LOG_FAILED": uint_arr2str(arr%d, %lu) => %s, want %s\n", i, c.len, got, c.want);
                if (got != NULL) free(got);
                return false;
            }
            free(got);
        }
    }
    return true;
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
