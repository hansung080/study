#ifndef __COMMON_H__
#define __COMMON_H__

#include <ac1/src/types.h>
#include <ac1/src/util/term.h>

#define UP    1
#define RIGHT 2
#define DOWN  4
#define LEFT  8

#define TITLE_X  1
#define TITLE_Y  1
#define ORIGIN_X 1
#define ORIGIN_Y 2

#define putchar_at_pos(p, c)   { gotopos(p); putchar(c); }
#define putwchar_at_pos(p, wc) { gotopos(p); putwchar(wc); }

#pragma pack(push, 1)

typedef struct __pos {
    int x;
    int y;
} pos_t;

#pragma pack(pop)

bool pos_equals(pos_t p1, pos_t p2);

inline void gotopos(pos_t p) {
    gotoxy(ORIGIN_X + p.x, ORIGIN_Y + p.y);
}

void wait_(const char* msg);
void print_title(const char* title);
void clear_title(int len);

#endif //__COMMON_H__