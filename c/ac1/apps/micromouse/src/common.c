#include "common.h"

bool pos_equals(pos_t p1, pos_t p2) {
    return p1.x == p2.x && p1.y == p2.y;
}

extern void gotopos(pos_t p);
extern void putchar_at_pos(int c, pos_t p);
extern void putwchar_at_pos(wchar_t wc, pos_t p);
