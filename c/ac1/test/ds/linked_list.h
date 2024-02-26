#ifndef __TEST__DS__LINKED_LIST_H__
#define __TEST__DS__LINKED_LIST_H__

#include <ac1/src/testing/test.h>
#include <ac1/src/ds/linked_list.h>
#include <ac1/src/util/util.h>

#define assert_eq_ll(msg, list, ...) __assert_eq_ll((msg), (list), args_len(ll_data_t, ##__VA_ARGS__), ##__VA_ARGS__)

void init_ds__linked_list(t_test_t tests[], size_t* n);
static bool __assert_eq_ll(const char* msg, const ll_list_t* list, int vargc, ...);
static bool test_ll_list_t();
static bool test_ll_insert_by_asc();
static bool test_ll_insert_by_desc();

#endif // __TEST__DS__LINKED_LIST_H__