#include <stdio.h>
#include "util/string.h"
#include "etc/mul.h"
#include "../src/util/string.h"

int main(int argc, char* argv[]) {
    int len = 4;
    test tests[len];
    int n = 0;

    init_util__string(tests, &n);
    init_etc__mul(tests, &n);

    if (n != len) {
        fprintf(stderr, C_RED"ERROR"C_RESET": mismatched tests length: got %d, want %d\n", n, len);
        return 1;
    }

    int n_tests = 0;
    int passed = 0; 
    for (int i = 0; i < len; ++i) {
        test t = tests[i];
        if (argc < 2 || contains(t.name, argv[1])) {
            ++n_tests;
            bool ok = t.func();
            printf("==>> %s - %s\n", t.name, ok ? C_GREEN"ok"C_RESET : C_RED"FAILED"C_RESET);
            if (ok) ++passed;
            else return 2;
        }        
    }

    printf("> "C_BLUE"TEST RESULT"C_RESET": %s - %d passed, %d failed\n",
        (passed == n_tests) ? C_GREEN"OK"C_RESET : C_RED"FAILED"C_RESET, passed, n_tests - passed);
    return 0;
}