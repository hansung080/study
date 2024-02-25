#include <stdio.h>
#include <ac1/src/util/string.h>
#include <ac1/src/util/term.h>
#include "util/util.h"
#include "util/math.h"
#include "util/string.h"
#include "util/array.h"
#include "util/term.h"
#include "etc/mul.h"
#include "etc/gcd.h"
#include "etc/lcm.h"
#include "etc/prime.h"
#include "ds/linked_list.h"

int main(int argc, char* argv[]) {
    if (argc > 2) {
        error("too many arguments\n");
        error_n("usage: %s [<test name>]\n", argv[0]);
        return 1;
    }

    int len = 21;
    test_t tests[len];
    int n = 0;

    init_util__util(tests, &n);
    init_util__math(tests, &n);
    init_util__string(tests, &n);
    init_util__array(tests, &n);
    init_util__term(tests, &n);
    init_etc__mul(tests, &n);
    init_etc__gcd(tests, &n);
    init_etc__lcm(tests, &n);
    init_etc__prime(tests, &n);
    init_ds__linked_list(tests, &n);

    if (n != len) {
        error("mismatched tests length: want %d, got %d\n", len, n);
        return 1;
    }

    int n_tests = 0, passed = 0;
    int x, y;
    for (int i = 0; i < len; ++i) {
        test_t t = tests[i];
        if (argc < 2 || str_contains(t.name, argv[1])) {
            ++n_tests;
            printf("# %d. %s ... ", i + 1, t.name);
            fflush(stdout);
            if (!getxy(&x, &y)) { error("failed on getxy\n"); return 1; }
            printf("\n");
            bool ok = t.func();
            printf_at_r(x, y, "%s", ok ? T_OK_LOW : T_FAILED);
            if (ok) ++passed;
        }        
    }

    if (n_tests == 0) {
        error("no tests found: %s\n", argv[1]);
        return 1;
    }

    printf("> "blue("test result")": %s - %d passed, %d failed\n",
        (passed == n_tests) ? T_OK_UP : T_FAILED, passed, n_tests - passed);
    return 0;
}