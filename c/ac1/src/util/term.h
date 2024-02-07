#ifndef __UTIL__TERM_H__
#define __UTIL__TERM_H__

#include <stdio.h>

// (x, y) starts with (1, 1) on the top-left corner of the screen.
inline void gotoxy(int x, int y) {
    printf("\033[%d;%df", y, x);
    fflush(stdout);
}

inline void putchar_at(int c, int x, int y) {
    gotoxy(x, y);
    putchar(c);
}

inline void clrscr() {
    printf("\033[H\033[J");
}

int getch_();

#endif // __UTIL__TERM_H__