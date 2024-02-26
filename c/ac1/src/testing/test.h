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

#define t_fail(format, ...)   fprintf(stderr, T_FAILED": "format, ##__VA_ARGS__)
#define t_fail_n(format, ...) fprintf(stderr, format, ##__VA_ARGS__)

typedef bool (*t_test_func)();

#pragma pack(push, 1)

typedef struct __t_test {
    const char* name;
    t_test_func func;
} t_test_t;

#pragma pack(pop)

typedef void (*t_init_func)(t_test_t tests[], size_t* n);

t_test_t t_new(const char* name, t_test_func func);
bool t_start(t_init_func inits[], size_t n_inits, size_t n_tests, int argc, char* argv[]);

#endif // __TESTING__TEST_H__