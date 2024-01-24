#include <stdio.h>
#include <ac1/src/util/math.h>
#include "math.h"

void init_util__math(test t[], int* n) {
    int i = *n;
    t[i++] = new_test("test/util/math/test_square", test_square);
    t[i++] = new_test("test/util/math/test_pow", test_pow);
    t[i++] = new_test("test/util/math/test_powmod", test_powmod);
    *n = i;
}

bool test_square() {
    struct case_ {
        int x;
        int want;
    };

    struct case_ cases[] = {
        {3, 9},
        {4, 16},
    };

    int len = sizeof(cases) / sizeof(struct case_);
    for (int i = 0; i < len; ++i) {
        struct case_ c = cases[i];
        int got = square_i(c.x);
        if (got != c.want) {
            fprintf(stderr, LOG_FAILED": square_i(%d) => %d, want %d\n", c.x, got, c.want);
            return false;
        }

        got = (int)square_u((unsigned int)c.x);
        if (got != c.want) {
            fprintf(stderr, LOG_FAILED": square_u(%d) => %d, want %d\n", c.x, got, c.want);
            return false;
        }

        got = (int)square_d((double)c.x);
        if (got != c.want) {
            fprintf(stderr, LOG_FAILED": square_d(%d) => %d, want %d\n", c.x, got, c.want);
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

bool test_powmod() {
    struct case_ {
        unsigned int b;
        unsigned int n;
        unsigned int m;
        unsigned int want;
    };

    struct case_ cases[] = {
        {2, 0, 5, 1},
        {2, 1, 5, 2},
        {2, 2, 5, 4},
        {2, 3, 5, 3},
        {2, 4, 5, 1},
        {2, 5, 5, 2},
        {2, 6, 5, 4},
        {2, 7, 5, 3},
        {2, 8, 5, 1},
        {2, 9, 5, 2},
        {2, 10, 5, 4},
        {2, 11, 5, 3},
        {2, 11, 1, 0},
        {7, 11, 5, 3},
    };

    int len = sizeof(cases) / sizeof(struct case_);
    for (int i = 0; i < len; ++i) {
        struct case_ c = cases[i];
        unsigned int got = powmod_basic(c.b, c.n, c.m);
        if (got != c.want) {
            fprintf(stderr, LOG_FAILED": powmod_basic(%u, %u, %u) => %u, want %u\n", c.b, c.n, c.m, got, c.want);
            return false;
        }

        got = powmod_rec(c.b, c.n, c.m);
        if (got != c.want) {
            fprintf(stderr, LOG_FAILED": powmod_rec(%u, %u, %u) => %u, want %u\n", c.b, c.n, c.m, got, c.want);
            return false;
        }

        got = powmod_iter(c.b, c.n, c.m);
        if (got != c.want) {
            fprintf(stderr, LOG_FAILED": powmod_iter(%u, %u, %u) => %u, want %u\n", c.b, c.n, c.m, got, c.want);
            return false;
        }
    }
    return true;
}
