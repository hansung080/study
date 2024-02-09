#ifndef __COMMON_H__
#define __COMMON_H__

#include <ac1/src/util/term.h>

#define UP    1
#define RIGHT 2
#define DOWN  4
#define LEFT  8

#define ORIGIN_X 1
#define ORIGIN_Y 1

#pragma pack(push, 1)

typedef struct __pos {
    int x;
    int y;
} pos_t;

#pragma pack(pop)

inline void gotopos(const pos_t* p) {
    gotoxy(ORIGIN_X + p->x, ORIGIN_Y + p->y);
}

inline void putchar_at_pos(int c, const pos_t* p) {
    gotopos(p);
    putchar(c);
}

inline void putwchar_at_pos(wchar_t wc, const pos_t* p) {
    gotopos(p);
    putwchar(wc);
}

#endif //__COMMON_H__