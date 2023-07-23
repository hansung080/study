#include <stdio.h>
#include <make-sample/src/people/alice.h>
#include "alice.h"

void init_people__alice(test t[], int* n) {
    int i = *n;
    t[i++] = new_test("test/people/alice/test_alice", test_alice);
    *n = i;
}

bool test_alice() {
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
        bool got = alice(c.arg);
        if (got != c.want) {
            fprintf(stderr, C_RED"FAILED"C_RESET": alice(%d) => %d, want %d\n", c.arg, got, c.want);
            return false;
        }
    }

    return true;
}