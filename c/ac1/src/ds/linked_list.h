#ifndef __DS__LINKED_LIST_H__
#define __DS__LINKED_LIST_H__

#include <stddef.h>
#include "../types.h"
#include "../util/array.h"

typedef int ll_data_t;

#pragma pack(push, 1)

typedef struct __ll_node {
    ll_data_t data;
    struct __ll_node* next;
} ll_node_t;

typedef struct __ll_list {
    ll_node_t* head;
    ll_node_t* tail;
} ll_list_t;

#pragma pack(pop)

ll_list_t ll_new();
ll_node_t* ll_insert_after(const ll_list_t* l, ll_node_t* base, ll_data_t data);
ll_node_t* ll_insert_prev(const ll_list_t* l, ll_data_t base, ll_data_t data);
ll_node_t* ll_insert_next(const ll_list_t* l, ll_data_t base, ll_data_t data);
ll_node_t* ll_insert_by_asc(const ll_list_t* l, ll_data_t data);
ll_node_t* ll_insert_by_desc(const ll_list_t* l, ll_data_t data);
bool ll_delete_after(const ll_list_t* l, ll_node_t* base);
bool ll_delete(const ll_list_t* l, ll_data_t data);
void ll_delete_all(const ll_list_t* l);
ll_node_t* ll_find(const ll_list_t* l, ll_data_t data);
ll_node_t* ll_find_prev(const ll_list_t* l, ll_data_t base);
size_t ll_count(const ll_list_t* l);
array_t ll_to_array(const ll_list_t* l); // Destroy the returned array_t.
char* ll_to_str(const ll_list_t* l); // Free the returned memory.
void ll_destroy(ll_list_t* l);

#endif // __DS__LINKED_LIST_H__