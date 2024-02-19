#include <stdlib.h>
#include <string.h>
#include <ac1/src/util/array.h>
#include <ac1/src/util/string.h>
#include "array.h"

void init_util__array(test_t t[], int* n) {
    int i = *n;
    t[i++] = new_test("test/util/array/test_arr_to_str", test_arr_to_str);
    t[i++] = new_test("test/util/array/test_arr_equals", test_arr_equals);
    *n = i;
}

bool has_negative(const int* arr, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        if (arr[i] < 0) return true;
    }
    return false;
}

bool test_arr_to_str() {
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
        char* got = arr_to_str_i(c.arr, c.len);
        if (got == NULL || strcmp(got, c.want) != 0) {
            fail("arr_to_str_i(arr%d, %lu) => %s, want %s\n", i, c.len, got, c.want);
            if (got != NULL) free(got);
            return false;
        }
        free(got);

        if (!c.has_negative) {
            got = arr_to_str_ui((const uint*)c.arr, c.len);
            if (got == NULL || strcmp(got, c.want) != 0) {
                fail("arr_to_str_ui(arr%d, %lu) => %s, want %s\n", i, c.len, got, c.want);
                if (got != NULL) free(got);
                return false;
            }
            free(got);
        }
    }
    return true;
}

bool test_arr_equals() {
    struct case_ {
        const int* arr1;
        size_t size1;
        const int* arr2;
        size_t size2;
        bool want;
    };

    int arr1[] = {};
    int arr2[] = {};
    int arr3[] = {1, -2, 3};
    int arr4[] = {1, -2, 3};
    int arr5[] = {1, -2, -3};
    int arr6[] = {1, -2, 3, 4};

    struct case_ cases[] = {
        {NULL, 0, NULL, 0, true},
        {NULL, 0, arr1, sizeof(arr1), false},
        {arr1, sizeof(arr1), NULL, 0, false},
        {arr1, sizeof(arr1), arr2, sizeof(arr2), true},
        {arr3, sizeof(arr3), arr4, sizeof(arr4), true},
        {arr3, sizeof(arr3), arr5, sizeof(arr5), false},
        {arr3, sizeof(arr3), arr6, sizeof(arr6), false},
    };

    int len = sizeof(cases) / sizeof(struct case_);
    for (int i = 0; i < len; ++i) {
        struct case_ c = cases[i];
        bool got = arr_equals(c.arr1, c.size1, c.arr2, c.size2);
        if (got != c.want) {
            char* s_arr1 = arr_to_str_i(c.arr1, c.size1 / sizeof(int));
            char* s_arr2 = arr_to_str_i(c.arr2, c.size2 / sizeof(int));
            fail("arr_equals(%s, %lu, %s, %lu) => %s, want %s\n", s_arr1, c.size1, s_arr2, c.size2, bool_to_str(got), bool_to_str(c.want));
            free(s_arr1);
            free(s_arr2);
            return false;
        }
    }
    return true;
}
