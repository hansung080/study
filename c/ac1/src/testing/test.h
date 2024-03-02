#ifndef __TESTING__TEST_H__
#define __TESTING__TEST_H__

#include <stdio.h>
#include <stddef.h>
#include "../types.h"
#include "../log.h"
#include "assert.h"

#define T_OK_LOW green("ok")
#define T_OK_UP  green("OK")
#define T_FAILED red("FAILED")

#define t_debug(format, ...)   t_fprintf(stdout, T_DEBUG": "format, ##__VA_ARGS__)
#define t_debug_n(format, ...) t_fprintf(stdout, format, ##__VA_ARGS__)
#define t_info(format, ...)    t_fprintf(stdout, T_INFO": "format, ##__VA_ARGS__)
#define t_info_n(format, ...)  t_fprintf(stdout, format, ##__VA_ARGS__)
#define t_warn_(format, ...)   t_fprintf(stderr, T_WARNING": "format, ##__VA_ARGS__)
#define t_warn_n(format, ...)  t_fprintf(stderr, format, ##__VA_ARGS__)
#define t_error(format, ...)   t_fprintf(stderr, T_ERROR": "format, ##__VA_ARGS__)
#define t_error_n(format, ...) t_fprintf(stderr, format, ##__VA_ARGS__)
#define t_fail(format, ...)    t_fprintf(stderr, T_FAILED": "format, ##__VA_ARGS__)
#define t_fail_n(format, ...)  t_fprintf(stderr, format, ##__VA_ARGS__)
#define t_printf(format, ...)  t_fprintf(stdout, format, ##__VA_ARGS__)

typedef bool (*t_test_func)();

#pragma pack(push, 1)

typedef struct __t_test {
    const char* name;
    t_test_func func;
} t_test_t;

typedef struct __t_winsize {
    int width;
    int height;
} t_winsize_t;

typedef struct __t_result_pos {
    int x;
    int y;
    bool x_reached_width;
    bool y_reached_height;
} t_result_pos_t;

#pragma pack(pop)

typedef void (*t_init_func)(t_test_t tests[], size_t* n);

t_test_t t_new(const char* name, t_test_func func);
bool t_start(t_init_func inits[], size_t n_inits, size_t n_tests, int argc, char* argv[]);
int t_fprintf(FILE* stream, const char* format, ...);

#endif // __TESTING__TEST_H__