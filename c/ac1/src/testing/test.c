#include <stdio.h>
#include <stdlib.h>
#include "test.h"
#include "../util/string.h"
#include "../util/term.h"

t_test_t t_new(const char* name, t_test_func func) {
    return (t_test_t){name, func};
}

bool t_start(t_init_func inits[], size_t n_inits, size_t n_tests, int argc, char* argv[]) {
    if (argc > 2) {
        error("too many arguments\n");
        error_n("usage: %s [<test name>]\n", argv[0]);
        return false;
    }

    t_test_t* tests = (t_test_t*)malloc(sizeof(t_test_t) * n_tests);
    size_t n = 0;
    for (size_t i = 0; i < n_inits; ++i) {
        inits[i](tests, &n);
    }

    if (n != n_tests) {
        error("mismatched tests length: want %lu, got %lu\n", n_tests, n);
        free(tests);
        return false;
    }

    size_t tested = 0, passed = 0;
    int x, y;
    for (size_t i = 0; i < n_tests; ++i) {
        t_test_t t = tests[i];
        if (argc < 2 || str_contains(t.name, argv[1])) {
            ++tested;
            printf("# %lu. %s ... ", i + 1, t.name);
            fflush(stdout);
            if (!getxy(&x, &y)) { error("failed on getxy\n"); return 1; }
            printf("\n");
            bool ok = t.func();
            printf_at_r(x, y, "%s", ok ? T_OK_LOW : T_FAILED);
            if (ok) ++passed;
        }
    }

    if (tested == 0) {
        error("no tests found: %s\n", argv[1]);
        free(tests);
        return false;
    }

    printf("> "blue("test result")": %s - %lu passed, %lu failed\n",
        (passed == tested) ? T_OK_UP : T_FAILED, passed, tested - passed);
    free(tests);
    return true;
}