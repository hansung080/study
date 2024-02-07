#ifndef __COMMON_H__
#define __COMMON_H__

#define UP    1
#define RIGHT 2
#define DOWN  4
#define LEFT  8

#pragma pack(push, 1)

typedef struct __pos {
    int x;
    int y;
} pos_t;

#pragma pack(pop)

#endif //__COMMON_H__