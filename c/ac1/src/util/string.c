#include <string.h>
#include "string.h"

bool stob(const char* s) {
    if (strcmp(s, "true") == 0) return true;
    return false;
}

const char* btos(bool b) {
    if (b == false) return "false";
    return "true";
}

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