#include <stdio.h>
#include <ac1/src/etc/prime.h>
#include <ac1/src/util/string.h>
#include "prime.h"

void init_etc__prime(test t[], int* n) {
    int i = *n;
    t[i++] = new_test("test/etc/prime/test_is_prime", test_is_prime);
    *n = i;
}

bool test_is_prime() {
    struct case_ {
        unsigned int n;
        bool want;
    };

    int carmichael_len = 6;

    struct case_ cases[] = {
        /* Carmichael Numbers */
        {561, false},
        {1105, false},
        {1729, false},
        {2465, false},
        {2821, false},
        {6601, false},
        /* Normal Numbers */
        {1, false},
        {2, true},
        {3, true},
        {4, false},
        {5, true},
        {6, false},
        {7, true},
        {8, false},
        {9, false},
        {10, false},
        {11, true},
        {12, false},
        {23, true},
        {149, true},
        {823, true},
        {1483, true},
        {299, false},
        {529, false},
    };

    int len = sizeof(cases) / sizeof(struct case_);
    for (int i = 0; i < len; ++i) {
        struct case_ c = cases[i];
        bool got = is_prime_basic(c.n);
        if (got != c.want) {
            fprintf(stderr, LOG_FAILED": is_prime_basic(%u) => %s, want %s\n", c.n, btos(got), btos(c.want));
            return false;
        }

        got = is_prime_fermat(c.n);
        // NOTE: is_prime_fermat fails with Carmichael numbers, thus, correct the results.
        if (i < carmichael_len) got = !got;
        if (got != c.want) {
            fprintf(stderr, LOG_FAILED": is_prime_fermat(%u) => %s, want %s\n", c.n, btos(got), btos(c.want));
            return false;
        }
    }
    return true;
}