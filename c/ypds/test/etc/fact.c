#include <ypds/src/etc/fact.h>
#include "fact.h"

void init_etc__fact(t_test_t tests[], size_t* n) {
    tests[(*n)++] = t_new("test/etc/fact/test_fact", test_fact);
}

bool test_fact() {
    struct case_ {
        uint n;
        uint want;
    };

    struct case_ cases[] = {
        {0, 1},
        {1, 1},
        {2, 2},
        {3, 6},
        {4, 24},
        {5, 120},
    };

    int len = sizeof(cases) / sizeof(struct case_);
    for (int i = 0; i < len; ++i) {
        struct case_ c = cases[i];
        uint got = fact_rec(c.n);
        if (got != c.want) {
            t_fail("fact_rec(%u) => %u, want %u\n", c.n, got, c.want);
            return false;
        }

        got = fact_iter(c.n);
        if (got != c.want) {
            t_fail("fact_iter(%u) => %u, want %u\n", c.n, got, c.want);
            return false;
        }
    }
    return true;
}
