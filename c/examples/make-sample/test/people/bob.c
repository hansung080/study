#include <stdio.h>
#include <make-sample/src/people/bob.h>
#include "bob.h"

void init_people__bob(test t[], int* n) {
    int i = *n;
    t[i++] = new_test("test/people/bob/test_bob", test_bob);
    *n = i;
}

bool test_bob() {
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
        int got = bob(c.arg);
        if (got != c.want) {
            fprintf(stderr, C_RED"FAILED"C_RESET": bob(%d) => %d, want %d\n", c.arg, got, c.want);
            return false;
        }
    }
    return true;
}