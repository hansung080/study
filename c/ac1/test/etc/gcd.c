#include <ac1/src/etc/gcd.h>
#include "gcd.h"

void init_etc__gcd(test_t t[], int* n) {
    int i = *n;
    t[i++] = new_test("test/etc/gcd/test_gcd", test_gcd);
    *n = i;
}

bool test_gcd() {
    struct case_ {
        uint a;
        uint b;
        uint want;
    };

    struct case_ cases[] = {
        {10, 10, 10},
        {24, 10, 2},
        {10, 24, 2},
        {206, 40, 2},
        {280, 30, 10},
    };

    int len = sizeof(cases) / sizeof(struct case_);
    for (int i = 0; i < len; ++i) {
        struct case_ c = cases[i];
        uint got = gcd_sub_rec(c.a, c.b);
        if (got != c.want) {
            fail("gcd_sub_rec(%u, %u) => %u, want %u\n", c.a, c.b, got, c.want);
            return false;
        } 

        got = gcd_sub_iter(c.a, c.b);
        if (got != c.want) {
            fail("gcd_sub_iter(%u, %u) => %u, want %u\n", c.a, c.b, got, c.want);
            return false;
        }

        got = gcd_mod_rec(c.a, c.b);
        if (got != c.want) {
            fail("gcd_mod_rec(%u, %u) => %u, want %u\n", c.a, c.b, got, c.want);
            return false;
        }

        got = gcd_mod_iter(c.a, c.b);
        if (got != c.want) {
            fail("gcd_mod_iter(%u, %u) => %u, want %u\n", c.a, c.b, got, c.want);
            return false;
        }
    }
    return true;
}
