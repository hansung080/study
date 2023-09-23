#include <stdio.h>
#include "fruits/apple.h"
#include "fruits/banana.h"
#include "people/alice.h"
#include "people/bob.h"

bool contains(const char* s, const char* keyword) {
    int i, j, k;
    bool matched;
    for (i = 0; s[i] != '\0'; ++i) {
        if (s[i] == keyword[0]) {
            matched = true;
            for (j = i, k = 0; keyword[k] != '\0'; ++j, ++k) {
                if (s[j] != keyword[k]) {
                    matched = false;
                    break;
                }
            }
            if (matched) return true;
        }
    }
    return false;
}

int main(int argc, char* argv[]) {
    if (argc > 2) {
        fprintf(stderr, LOG_ERROR": too many arguments\n");
        fprintf(stderr, "usage: %s [<test name>]\n", argv[0]);
        return 1;
    }

    int len = 4;
    test tests[len];
    int n = 0;

    init_fruits__apple(tests, &n);
    init_fruits__banana(tests, &n);
    init_people__alice(tests, &n);
    init_people__bob(tests, &n);

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