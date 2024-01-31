#include <stdio.h>
#include <stdlib.h>
#include <ac1/src/etc/prime.h>
#include <ac1/src/util/string.h>
#include "prime.h"

void init_etc__prime(test_t t[], int* n) {
    int i = *n;
    t[i++] = new_test("test/etc/prime/test_is_prime", test_is_prime);
    t[i++] = new_test("test/etc/prime/test_primes_new", test_primes_new);
    *n = i;
}

bool test_is_prime() {
    struct case_ {
        uint n;
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
            fprintf(stderr, LOG_FAILED": is_prime_basic(%u) => %s, want %s\n", c.n, bool_to_str(got), bool_to_str(c.want));
            return false;
        }

        got = is_prime_fermat(c.n);
        // NOTE: is_prime_fermat fails with Carmichael numbers, thus, correct the results.
        if (i < carmichael_len) got = !got;
        if (got != c.want) {
            fprintf(stderr, LOG_FAILED": is_prime_fermat(%u) => %s, want %s\n", c.n, bool_to_str(got), bool_to_str(c.want));
            return false;
        }

        got = is_prime_mr(c.n);
        if (got != c.want) {
            fprintf(stderr, LOG_FAILED": is_prime_mr(%u) => %s, want %s\n", c.n, bool_to_str(got), bool_to_str(c.want));
            return false;
        }
    }
    return true;
}

bool test_primes_new() {
    struct case_ {
        uint max;
        primes_t want;
    };

    uint arr1[] = {};
    uint arr2[] = {2};
    uint arr3[] = {2, 3};
    uint arr4[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

    primes_t want1 = {arr1, sizeof(arr1) / sizeof(uint), NULL};
    primes_t want2 = {arr2, sizeof(arr2) / sizeof(uint), NULL};
    primes_t want3 = {arr3, sizeof(arr3) / sizeof(uint), NULL};
    primes_t want4 = {arr4, sizeof(arr4) / sizeof(uint), NULL};

    struct case_ cases[] = {
        {1, want1},
        {2, want2},
        {3, want3},
        {30, want4},
    };

    int len = sizeof(cases) / sizeof(struct case_);
    for (int i = 0; i < len; ++i) {
        struct case_ c = cases[i];
        primes_t got = primes_new(c.max);
        if (!primes_equals(&got, &c.want)) {
            char* s_want = primes_to_str(&c.want);
            fprintf(stderr, LOG_FAILED": primes_new(%u) => %s, want %s\n", c.max, primes_to_str(&got), s_want);
            primes_delete(&got);
            if (s_want != NULL) free(s_want);
            return false;
        }
        primes_delete(&got);
    }
    return true;
}
