#include <string.h>
#include <ac1/src/util/string.h>
#include "string.h"

void init_util__string(t_test_t tests[], size_t* n) {
    tests[(*n)++] = t_new("test/util/string/test_str_to_bool", test_str_to_bool);
    tests[(*n)++] = t_new("test/util/string/test_bool_to_str", test_bool_to_str);
    tests[(*n)++] = t_new("test/util/string/test_int_to_str", test_int_to_str);
    tests[(*n)++] = t_new("test/util/string/test_str_contains", test_str_contains);
}

bool test_str_to_bool() {
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
        bool got = str_to_bool(c.s);
        if (got != c.want) {
            t_fail("str_to_bool(%s) => %d, want %d\n", c.s, got, c.want);
            return false;
        }
    }
    return true;
}

bool test_bool_to_str() {
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
        const char* got = bool_to_str(c.b);
        if (strcmp(got, c.want) != 0) {
            t_fail("bool_to_str(%d) => %s, want %s\n", c.b, got, c.want);
            return false;
        }
    }
    return true;
}

bool test_int_to_str() {
    struct case_ {
        int x;
        const char* want;
        uint digit;
    };

    struct case_ cases[] = {
        {0, "0", 1},
        {1, "1", 1},
        {12, "12", 2},
        {123, "123", 3},
        {-1, "-1", 2},
        {-12, "-12", 3},
        {-123, "-123", 4},
    };

    int len = sizeof(cases) / sizeof(struct case_);
    char got[INT_MAX_DIGIT + 1];
    for (int i = 0; i < len; ++i) {
        struct case_ c = cases[i];
        uint digit = int_to_str(c.x, got);
        if (strcmp(got, c.want) != 0 || digit != c.digit) {
            t_fail("int_to_str(%d) => (%s, %u), want (%s, %u)\n", c.x, got, digit, c.want, c.digit);
            return false;
        }

        if (c.x >= 0) {
            digit = uint_to_str((uint)c.x, got);
            if (strcmp(got, c.want) != 0 || digit != c.digit) {
                t_fail("uint_to_str(%d) => (%s, %u), want (%s, %u)\n", c.x, got, digit, c.want, c.digit);
                return false;
            }
        }
    }
    return true;
}

bool test_str_contains() {
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
        bool got = str_contains(c.s, c.keyword);
        if (got != c.want) {
            t_fail("str_contains('%s', '%s') => %s, want %s\n", c.s, c.keyword, bool_to_str(got), bool_to_str(c.want));
            return false;
        }

    }
    return true;
}
