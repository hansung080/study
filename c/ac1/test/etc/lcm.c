#include <ac1/src/etc/lcm.h>
#include "lcm.h"

void init_etc__lcm(t_test_t tests[], size_t* n) {
    tests[(*n)++] = t_new("test/etc/lcm/test_lcm", test_lcm);
}

bool test_lcm() {
    struct case_ {
        uint a;
        uint b;
        uint want;
    };

    struct case_ cases[] = {
        {10, 10, 10},
        {24, 10, 120},
        {10, 24, 120},
        {206, 40, 4120},
        {280, 30, 840},
    };

    int len = sizeof(cases) / sizeof(struct case_);
    for (int i = 0; i < len; ++i) {
        struct case_ c = cases[i];
        uint got = lcm(c.a, c.b);
        if (got != c.want) {
            t_fail("lcm(%u, %u) => %u, want %u\n", c.a, c.b, got, c.want);
            return false;
        } 
    }
    return true;
}
