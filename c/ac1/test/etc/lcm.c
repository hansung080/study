#include <stdio.h>
#include <ac1/src/etc/lcm.h>
#include "lcm.h"

void init_etc__lcm(test t[], int* n) {
    int i = *n;
    t[i++] = new_test("test/etc/lcm/test_lcm", test_lcm);
    *n = i;
}

bool test_lcm() {
    struct case_ {
        unsigned int a;
        unsigned int b;
        unsigned int want;
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
        unsigned int got = lcm(c.a, c.b);
        if (got != c.want) {
            fprintf(stderr, LOG_FAILED": lcm(%u, %u) => %u, want %d\n", c.a, c.b, got, c.want);
            return false;
        } 
    }
    return true;
}
