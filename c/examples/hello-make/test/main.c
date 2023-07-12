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
    int len = 4;
    test tests[len];
    int n = 0;

    init_fruits__apple(tests, &n);
    init_fruits__banana(tests, &n);
    init_people__alice(tests, &n);
    init_people__bob(tests, &n);

    if (n != len) {
        fprintf(stderr, C_RED"ERROR"C_RESET": mismatched tests length: want %d, got %d\n", len, n);
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