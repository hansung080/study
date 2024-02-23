#include <string.h>
#include <stddef.h>
#include "string.h"
#include "math.h"

bool str_to_bool(const char* s) {
    if (strcmp(s, "true") == 0) return true;
    return false;
}

const char* bool_to_str(bool b) {
    if (b == false) return "false";
    return "true";
}

uint int_to_str(int x, char* s) {
    if (x < 0) {
        *s = '-';
        return uint_to_str(-x, s + 1) + 1;
    } else {
        return uint_to_str(x, s);
    }
}

uint uint_to_str(uint x, char* s) {
    uint d = digit_ui(x);
    s += d;
    *s = '\0';
    do {
        --s;
        *s = '0' + (char)(x % 10);
    } while (x /= 10);
    return d;
}

bool str_contains(const char* s, const char* keyword) {
    size_t i, j, k;
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

char* str_to_printable(char* s) {
    for (size_t i = 0; s[i] != '\0'; ++i)
        if (s[i] < 32) s[i] = '?';
    return s;
}
