#include <ac1/src/etc/mul.h>
#include "mul.h"

void init_etc__mul(test_t t[], int* n) {
    int i = *n;
    t[i++] = new_test("test/etc/mul/test_mul", test_mul);
    *n = i;
}

bool test_mul() {
    struct case_ {
        int x;
        int y;
        int want;
    };

    struct case_ cases[] = {
        {45, 37, 1665},
        {-45, 37, -1665},
        {45, -37, -1665},
        {-45, -37, 1665},
        {0, 37, 0},
        {45, 0, 0},
        {0, 0, 0},
        {1, 37, 37},
        {45, 1, 45},
        {1, 1, 1},
    };

    int len = sizeof(cases) / sizeof(struct case_);
    for (int i = 0; i < len; ++i) {
        struct case_ c = cases[i];
        int got = mul_rec(c.x, c.y);
        if (got != c.want) {
            fail("mul_rec(%d, %d) => %d, want %d\n", c.x, c.y, got, c.want);
            return false;
        }

        got = mul_iter(c.x, c.y);
        if (got != c.want) {
            fail("mul_iter(%d, %d) => %d, want %d\n", c.x, c.y, got, c.want);
            return false;
        }
    }
    return true;
}