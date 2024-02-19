#include <stdlib.h>
#include "linked_list.h"

ll_list_t ll_new() {
    ll_list_t list;
    list.head = (ll_node_t*)malloc(sizeof(ll_node_t));
    list.tail = (ll_node_t*)malloc(sizeof(ll_node_t));
    list.head->next = list.tail;
    list.tail->next = list.tail;
    return list;
}

ll_node_t* ll_insert_after(const ll_list_t* l, ll_node_t* base, ll_data_t data) {
    if (base == l->tail) return NULL;
    ll_node_t* new = (ll_node_t*)malloc(sizeof(ll_node_t));
    new->data = data;
    new->next = base->next;
    base->next = new;
    return new;
}

ll_node_t* ll_insert_prev(const ll_list_t* l, ll_data_t base, ll_data_t data) {
    ll_node_t* prev = ll_find_prev(l, base);
    if (prev == NULL) return NULL;
    return ll_insert_after(l, prev, data);
}

ll_node_t* ll_insert_next(const ll_list_t* l, ll_data_t base, ll_data_t data) {
    ll_node_t* _base = ll_find(l, base);
    if (_base == NULL) return NULL;
    return ll_insert_after(l, _base, data);
}

ll_node_t* ll_insert_by_asc(const ll_list_t* l, ll_data_t data) {
    ll_node_t* prev = l->head;
    ll_node_t* cur = l->head->next;
    for (; cur->data < data && cur != l->tail; prev = prev->next, cur = cur->next);
    return ll_insert_after(l, prev, data);
}

ll_node_t* ll_insert_by_desc(const ll_list_t* l, ll_data_t data) {
    ll_node_t* prev = l->head;
    ll_node_t* cur = l->head->next;
    for (; cur->data > data && cur != l->tail; prev = prev->next, cur = cur->next);
    return ll_insert_after(l, prev, data);
}

bool ll_delete_after(const ll_list_t* l, ll_node_t* base) {
    if (base == l->tail || base->next == l->tail) return false;
    ll_node_t* del = base->next;
    base->next = del->next;
    free(del);
    return true;
}

bool ll_delete(const ll_list_t* l, ll_data_t data) {
    ll_node_t* prev = ll_find_prev(l, data);
    if (prev == NULL) return false;
    return ll_delete_after(l, prev);
}

void ll_delete_all(const ll_list_t* l) {
    ll_node_t* cur = l->head->next;
    while (cur != l->tail) {
        ll_node_t* del = cur;
        cur = cur->next;
        free(del);
    }
    l->head->next = l->tail;
}

ll_node_t* ll_find(const ll_list_t* l, ll_data_t data) {
    ll_node_t* cur = l->head->next;
    for (; cur != l->tail; cur = cur->next)
        if (cur->data == data) return cur;
    return NULL;
}

ll_node_t* ll_find_prev(const ll_list_t* l, ll_data_t base) {
    ll_node_t* prev = l->head;
    ll_node_t* cur = l->head->next;
    for (; cur != l->tail; prev = prev->next, cur = cur->next)
        if (cur->data == base) return prev;
    return NULL;
}

size_t ll_count(const ll_list_t* l) {
    size_t count = 0;
    ll_node_t* cur = l->head->next;
    for (; cur != l->tail; cur = cur->next)
        ++count;
    return count;
}

array_t ll_to_array(const ll_list_t* l) {
    array_t array = array_new(sizeof(ll_data_t), ll_count(l));
    ll_data_t* arr = (ll_data_t*)array.arr;

    ll_node_t* cur = l->head->next;
    for (; cur != l->tail; cur = cur->next) {
        arr[array.len++] = cur->data;
    }
    return array;
}

char* ll_to_str(const ll_list_t* l) {
    array_t array = ll_to_array(l);
    // NOTE: ll_data_t must be int to use arr_to_str_i.
    char* str = arr_to_str_i(array.arr, array.len);
    array_destroy(&array);
    return str;
}

void ll_destroy(ll_list_t* l) {
    ll_delete_all(l); 
    free(l->head);
    l->head = NULL;
    free(l->tail);
    l->tail = NULL;
}
