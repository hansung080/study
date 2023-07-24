#include <stdio.h>
#include <make-sample/src/fruits/banana.h>
#include "banana.h"

void init_fruits__banana(test t[], int* n) {
    int i = *n;
    t[i++] = new_test("test/fruits/banana/test_banana", test_banana);
    *n = i;
}

bool test_banana() {
    struct case_ {
        int arg;
        int want;
    };

    struct case_ cases[] = {
        {-1, -1},
        {0, 0},
        {1, 1},
    };

    int len = sizeof(cases) / sizeof(struct case_);
    for (int i = 0; i < len; ++i) {
        struct case_ c = cases[i];
        int got = banana(c.arg);
        if (got != c.want) {
            fprintf(stderr, LOG_FAILED": banana(%d) => %d, want %d\n", c.arg, got, c.want);
            return false;
        }
    }
    return true;
}
