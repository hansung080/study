#include <stdio.h>
#include <ac1/src/util/math.h>
#include "math.h"

void init_util__math(test t[], int* n) {
    int i = *n;
    t[i++] = new_test("test/util/math/test_square", test_square);
    t[i++] = new_test("test/util/math/test_pow", test_pow);
    *n = i;
}

bool test_square() {
    struct case_ {
        double x;
        double want;
    };

    struct case_ cases[] = {
        {3, 9},
        {2.5, 6.25},
    };

    int len = sizeof(cases) / sizeof(struct case_);
    for (int i = 0; i < len; ++i) {
        struct case_ c = cases[i];
        double got = square(c.x);
        if (got != c.want) {
            fprintf(stderr, LOG_FAILED": square(%f) => %f, want %f\n", c.x, got, c.want);
            return false;
        }
    }
    return true;
}

bool test_pow() {
    struct case_ {
        double b;
        unsigned int n;
        double want;
    };

    struct case_ cases[] = {
        {2, 0, 1},
        {2, 8, 256},
        {2, 11, 2048},
        {-2, 0, 1},
        {-2, 8, 256},
        {-2, 11, -2048},
        {2.5, 3, 15.625},
    };

    int len = sizeof(cases) / sizeof(struct case_);
    for (int i = 0; i < len; ++i) {
        struct case_ c = cases[i];
        double got = pow_rec(c.b, c.n);
        if (got != c.want) {
            fprintf(stderr, LOG_FAILED": pow_rec(%f, %u) => %f, want %f\n", c.b, c.n, got, c.want);
            return false;
        }

        got = pow_iter(c.b, c.n);
        if (got != c.want) {
            fprintf(stderr, LOG_FAILED": pow_iter(%f, %u) => %f, want %f\n", c.b, c.n, got, c.want);
            return false;
        }
    }
    return true;
}
