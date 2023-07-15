#include <stdio.h>
#include <string.h>
#include "string.h"
#include "../../src/util/string.h"

void init_util__string(test t[], int* n) {
    int i = *n;
    t[i++] = new_test("test/util/string/test_stob", test_stob);
    t[i++] = new_test("test/util/string/test_btos", test_btos);
    t[i++] = new_test("test/util/string/test_contains", test_contains);
    *n = i;
}

bool test_stob() {
    struct case_ {
        const char* s;
        bool want;
    };

    struct case_ cases[] = {
        {"false", false},
        {"true", true},
        {"invalid", false},
    };

    int len = sizeof(cases) / sizeof(struct case_);
    for (int i = 0; i < len; ++i) {
        struct case_ c = cases[i];
        bool got = stob(c.s);
        if (got != c.want) {
            fprintf(stderr, C_RED"FAILED"C_RESET": stob(%s) => %d, want %d\n", c.s, got, c.want);
            return false;
        }
    }    

    return true;
}

bool test_btos() {
    struct case_ {
        bool b;
        const char* want;
    };

    struct case_ cases[] = {
        {false, "false"},
        {true, "true"},
        {2, "true"},
    };

    int len = sizeof(cases) / sizeof(struct case_);
    for (int i = 0; i < len; ++i) {
        struct case_ c = cases[i];
        const char* got = btos(c.b);
        if (strcmp(got, c.want) != 0) {
            fprintf(stderr, C_RED"FAILED"C_RESET": btos(%d) => %s, want %s\n", c.b, got, c.want);
            return false;
        }
    }
    return true;
}

bool test_contains() {
    struct case_ {
        const char* s;
        const char* keyword;
        bool want;
    };

    struct case_ cases[] = {
        {"", "", false},
        {"", "apple", false},
        {"apple", "", false},
        {"apple", "apple", true},
        {"apple, apply, application", "apple", true},
        {"apply, apple, application", "apple", true},
        {"apply, application, apple", "apple", true},
        {"appl, apply, application", "apple", false},
    };

    int len = sizeof(cases) / sizeof(struct case_);
    for (int i = 0; i < len; ++i) {
        struct case_ c = cases[i];
        bool got = contains(c.s, c.keyword);
        if (got != c.want) {
            fprintf(stderr, C_RED"FAILED"C_RESET": contains('%s', '%s') => %s, want %s\n", c.s, c.keyword, btos(got), btos(c.want));
            return false;
        }

    }

    return true;
}
