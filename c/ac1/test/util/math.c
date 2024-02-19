#include <ac1/src/util/math.h>
#include "math.h"

void init_util__math(test_t t[], int* n) {
    int i = *n;
    t[i++] = new_test("test/util/math/test_square", test_square);
    t[i++] = new_test("test/util/math/test_pow", test_pow);
    t[i++] = new_test("test/util/math/test_powmod", test_powmod);
    t[i++] = new_test("test/util/math/test_powmod_checked", test_powmod_checked);
    t[i++] = new_test("test/util/math/test_digit", test_digit);
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
            fail("square_i(%d) => %d, want %d\n", c.x, got, c.want);
            return false;
        }

        got = (int)square_ui((uint)c.x);
        if (got != c.want) {
            fail("square_ui(%d) => %d, want %d\n", c.x, got, c.want);
            return false;
        }

        got = (int)square_d((double)c.x);
        if (got != c.want) {
            fail("square_d(%d) => %d, want %d\n", c.x, got, c.want);
            return false;
        }
    }
    return true;
}

bool test_pow() {
    struct case_ {
        double b;
        uint n;
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
            fail("pow_rec(%f, %u) => %f, want %f\n", c.b, c.n, got, c.want);
            return false;
        }

        got = pow_iter(c.b, c.n);
        if (got != c.want) {
            fail("pow_iter(%f, %u) => %f, want %f\n", c.b, c.n, got, c.want);
            return false;
        }
    }
    return true;
}

bool test_powmod() {
    struct case_ {
        uint b;
        uint n;
        uint m;
        uint want;
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
        uint got = powmod_basic(c.b, c.n, c.m);
        if (got != c.want) {
            fail("powmod_basic(%u, %u, %u) => %u, want %u\n", c.b, c.n, c.m, got, c.want);
            return false;
        }

        got = powmod_rec(c.b, c.n, c.m);
        if (got != c.want) {
            fail("powmod_rec(%u, %u, %u) => %u, want %u\n", c.b, c.n, c.m, got, c.want);
            return false;
        }

        got = powmod_iter(c.b, c.n, c.m);
        if (got != c.want) {
            fail("powmod_iter(%u, %u, %u) => %u, want %u\n", c.b, c.n, c.m, got, c.want);
            return false;
        }
    }
    return true;
}

bool test_powmod_checked() {
    struct case_ {
        uint b;
        uint n;
        uint m;
        uint want_powmod;
        int want_powmod_checked_rec;
        int want_powmod_checked_iter;
    };

    int nc = -1; // No-Corrected: powmod_checked doesn't correct powmod. i.e. both are the same.

    struct case_ cases[] = {
        /* 149 is prime number */
        {1, 148, 149, 1, nc, nc},
        {2, 148, 149, 1, nc, nc},
        {11, 148, 149, 1, nc, nc},
        {12, 148, 149, 1, nc, nc},
        {50, 148, 149, 1, nc, nc},
        {100, 148, 149, 1, nc, nc},
        {123, 148, 149, 1, nc, nc},
        {124, 148, 149, 1, nc, nc},
        {147, 148, 149, 1, nc, nc},
        {148, 148, 149, 1, nc, nc},
        /* 299 is not prime number */
        {1, 298, 299, 1, nc, nc},
        {2, 298, 299, 140, nc, nc},
        {11, 298, 299, 127, nc, nc},
        {12, 298, 299, 196, nc, nc},
        {50, 298, 299, 257, nc, nc},
        {100, 298, 299, 100, nc, nc},
        {123, 298, 299, 238, nc, nc},
        {124, 298, 299, 147, nc, nc},
        {297, 298, 299, 140, nc, nc},
        {298, 298, 299, 1, nc, nc},
        /* 561 is not prime number (Carmichael number) */
        {1, 560, 561, 1, nc, nc},
        {2, 560, 561, 1, nc, nc},
        {11, 560, 561, 154, nc, nc},
        {12, 560, 561, 375, nc, nc},
        {50, 560, 561, 1, nc, nc},
        {100, 560, 561, 1, nc, 0},
        {123, 560, 561, 375, nc, nc},
        {124, 560, 561, 1, 0, nc},
        {559, 560, 561, 1, nc, nc},
        {560, 560, 561, 1, nc, nc},
    };

    int len = sizeof(cases) / sizeof(struct case_);
    uint want;
    for (int i = 0; i < len; ++i) {
        struct case_ c = cases[i];
        uint got = powmod_checked_rec(c.b, c.n, c.m);
        if (c.want_powmod_checked_rec != nc) want = c.want_powmod_checked_rec;
        else want = c.want_powmod;
        if (got != want) {
            fail("powmod_checked_rec(%u, %u, %u) => %u, want %u\n", c.b, c.n, c.m, got, want);
            return false;
        }

        got = powmod_checked_iter(c.b, c.n, c.m);
        if (c.want_powmod_checked_iter != nc) want = c.want_powmod_checked_iter;
        else want = c.want_powmod;
        if (got != want) {
            fail("powmod_checked_iter(%u, %u, %u) => %u, want %u\n", c.b, c.n, c.m, got, want);
            return false;
        }
    }
    return true;
}

bool test_digit() {
    struct case_ {
        int x;
        uint want;
    };

    struct case_ cases[] = {
        {0, 1},
        {1, 1},
        {12, 2},
        {123, 3},
        {-1, 2},
        {-12, 3},
        {-123, 4},
    };

    int len = sizeof(cases) / sizeof(struct case_);
    for (int i = 0; i < len; ++i) {
        struct case_ c = cases[i];
        uint got = digit_i(c.x);
        if (got != c.want) {
            fail("digit_i(%d) => %u, want %u\n", c.x, got, c.want);
            return false;
        }

        if (c.x >= 0) {
            got = digit_ui((uint)c.x);
            if (got != c.want) {
                fail("digit_ui(%d) => %u, want %u\n", c.x, got, c.want);
                return false;
            }
        }
    }
    return true;
}
