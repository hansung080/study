#include <stdlib.h>
#include <stdarg.h>
#include "test.h"
#include "../util/string.h"
#include "../util/term.h"

static t_winsize_t ws = {-1, -1};
static t_result_pos_t result_pos = {-1, -1, false, false};

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

    get_winsize(&ws.width, &ws.height);

    size_t tested = 0, passed = 0;
    for (size_t i = 0; i < n_tests; ++i) {
        t_test_t t = tests[i];
        if (argc < 2 || str_contains(t.name, argv[1])) {
            ++tested;
            printf("# %lu. %s ... ", i + 1, t.name);
            fflush(stdout);
            if (!getxy(&result_pos.x, &result_pos.y)) return false;
            result_pos.x_reached_width = false, result_pos.y_reached_height = false;
            t_printf("\n");
            bool ok = t.func();
            // NOTE: If t.func() prints logs more than window's height, the result will not be printed.
            if (result_pos.y >= 1) printf_at_r(result_pos.x, result_pos.y, "%s", ok ? T_OK_LOW : T_FAILED);
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

int t_fprintf(FILE* stream, const char* format, ...) {
    char str[1024];

    va_list ap;
    va_start(ap, format);
    if (vsprintf(str, format, ap) >= 1024) { t_error("t_fprintf: string exceeded size(1023)\n"); return -1; }
    va_end(ap);

    int x, y, newlines = 0;
    if (!getxy(&x, &y)) return -1;

    // NOTE: If x precisely reached width in the previous invocation, x must be 1 in the current invocation.
    //       However, `getxy` returns width for x, which is wrong position of the current x.
    //       Thus, the following code sets x to 1 directly to currect this problem.
    if (result_pos.x_reached_width) x = 1;

    for (int i = 0; str[i] != '\0'; ++i, ++x) {
        if (str[i] == '\n' || x > ws.width) {
            ++newlines;
            x = 1;
        }
    }

    if (result_pos.x_reached_width) {
        result_pos.x_reached_width = false;
        if (str[0] != '\0' && str[0] != '\n') ++newlines; 
    }

    if (x > ws.width) {
        result_pos.x_reached_width = true;
    }

    if (result_pos.y_reached_height) {
        result_pos.y -= newlines;
    } else {
        if (y + newlines > ws.height) {
            result_pos.y_reached_height = true;
            result_pos.y -= y + newlines - ws.height;
        }
    }
     
    int n = fprintf(stream, "%s", str);
    fflush(stream);
    return n;
}