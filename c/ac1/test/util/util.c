#include <ac1/src/util/util.h>
#include "util.h"

void init_util__util(t_test_t tests[], size_t* n) {
    tests[(*n)++] = t_new("test/util/util/test_rand_between", test_rand_between);
}

bool test_rand_between() {
    int min = 5;
    int max = 10;
    for (int i = 0; i < 20; ++i) {
        int got = rand_between(min, max);
        if (got < min || got > max) {
            t_fail("rand_between(%d, %d) => %d, want (%d ~ %d)\n", min, max, got, min, max);
            return false;
        }
    }
    return true;
}
