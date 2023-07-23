#include <stdio.h>
#include <make-sample/src/fruits/apple.h>
#include "apple.h"

void init_fruits__apple(test t[], int* n) {
    int i = *n;
    t[i++] = new_test("test/fruits/apple/test_apple", test_apple);
    *n = i;
}

bool test_apple() {
    struct case_ {
        bool arg;
        bool want;
    };

    struct case_ cases[] = {
        {false, false},
        {true, true},
    };

    int len = sizeof(cases) / sizeof(struct case_);
    for (int i = 0; i < len; ++i) {
        struct case_ c = cases[i];
        bool got = apple(c.arg);
        if (got != c.want) {
            fprintf(stderr, C_RED"FAILED"C_RESET": apple(%d) => %d, want %d\n", c.arg, got, c.want);
            return false;
        }
    }
    return true;
}