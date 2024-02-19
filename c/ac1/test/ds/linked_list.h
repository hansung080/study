#ifndef __TEST__DS__LINKED_LIST_H__
#define __TEST__DS__LINKED_LIST_H__

#include <ac1/src/ds/linked_list.h>
#include "../test.h"

#define args_len(type, ...)          (sizeof((type[]){__VA_ARGS__}) / sizeof(type))
#define assert_eq_ll(msg, list, ...) __assert_eq_ll((msg), (list), args_len(ll_data_t, ##__VA_ARGS__), ##__VA_ARGS__)

void init_ds__linked_list(test_t t[], int* n);
static bool __assert_eq_ll(const char* msg, const ll_list_t* list, int vargc, ...);
static bool test_ll_list_t();

#endif // __TEST__DS__LINKED_LIST_H__