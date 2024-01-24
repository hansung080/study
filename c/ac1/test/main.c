#include <stdio.h>
#include <ac1/src/util/string.h>
#include "util/string.h"
#include "util/math.h"
#include "etc/mul.h"
#include "etc/gcd.h"
#include "etc/lcm.h"
#include "etc/prime.h"

int main(int argc, char* argv[]) {
    if (argc > 2) {
        fprintf(stderr, LOG_ERROR": too many arguments\n");
        fprintf(stderr, "usage: %s [<test name>]\n", argv[0]);
        return 1;
    }

    int len = 10;
    test tests[len];
    int n = 0;

    init_util__string(tests, &n);
    init_util__math(tests, &n);
    init_etc__mul(tests, &n);
    init_etc__gcd(tests, &n);
    init_etc__lcm(tests, &n);
    init_etc__prime(tests, &n);

    if (n != len) {
        fprintf(stderr, LOG_ERROR": mismatched tests length: want %d, got %d\n", len, n);
        return 1;
    }

    int n_tests = 0;
    int passed = 0; 
    for (int i = 0; i < len; ++i) {
        test t = tests[i];
        if (argc < 2 || contains(t.name, argv[1])) {
            ++n_tests;
            bool ok = t.func();
            printf("# %d. %s ... %s\n", i + 1, t.name, ok ? LOG_OK_LOW : LOG_FAILED);
            if (ok) ++passed;
        }        
    }

    printf("> "blue("test result")": %s - %d passed, %d failed\n",
        (passed == n_tests) ? LOG_OK_UP : LOG_FAILED, passed, n_tests - passed);
    return 0;
}