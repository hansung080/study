#include <ac1/src/util/util.h>
#include "util.h"

void init_util__util(test_t t[], int* n) {
    int i = *n;
    t[i++] = new_test("test/util/util/test_rand_between", test_rand_between);
    *n = i;
}

bool test_rand_between() {
    int min = 5;
    int max = 10;
    for (int i = 0; i < 20; ++i) {
        int got = rand_between(min, max);
        if (got < min || got > max) {
            fail("rand_between(%d, %d) => %d, want (%d ~ %d)\n", min, max, got, min, max);
            return false;
        }
    }
    return true;
}
