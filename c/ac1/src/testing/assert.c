#include <stdlib.h>
#include "assert.h"
#include "test.h"
#include "../util/array.h"

bool assert_eq_arr(const void* got, size_t got_size, const void* want, size_t want_size, int elem_type, const char* msg) {
    if (!arr_equals(got, got_size, want, want_size)) {
        char* got_str;
        char* want_str;
        switch (elem_type) {
        case TYPE_INT:
            got_str = arr_to_str_i(got, got_size / sizeof(int));
            want_str = arr_to_str_i(want, want_size / sizeof(int));
            break;
        case TYPE_UINT:
            got_str = arr_to_str_ui(got, got_size / sizeof(uint));
            want_str = arr_to_str_ui(want, want_size / sizeof(uint));
            break;
        default:
            got_str = (char*)malloc(18 + INT_MAX_DIGIT + 1);
            want_str = (char*)malloc(18 + INT_MAX_DIGIT + 1);
            sprintf(got_str, "unsupported_type(%d)", elem_type);
            sprintf(want_str, "unsupported_type(%d)", elem_type);
            break;
        }

        t_fail("%s: got=%s, want=%s\n", msg, got_str, want_str);
        free(got_str);
        free(want_str);
        return false;
    }
    return true;
}
