#ifndef __UTIL__TERM_H__
#define __UTIL__TERM_H__

#include <stdio.h>
#include <wchar.h>
#include <termios.h>
#include "../types.h"

#define putchar_at(x, y, c)          { gotoxy(x, y); putchar(c); }
#define putwchar_at(x, y, wc)        { gotoxy(x, y); putwchar(wc); }
#define printf_at(x, y, format, ...) { gotoxy(x, y); printf(format, ##__VA_ARGS__); }
#define clrscr()                     printf("\033[H\033[J")

typedef struct termios termios_t;
typedef struct winsize winsize_t;

// (x, y) starts with (1, 1) on the top-left corner of the window.
// If parameters (1 <= x <= width, 1 <= y <= height) are passed, the cursor will move to (x, y).
// If parameters (x > width, y > height) are passed, the cursor will move to (width, height).
// If parameters (x < 1, y < 1) are passed, the cursor will move to (1, 1).
inline void gotoxy(int x, int y) {
    // NOTE: The following two conditions are added to maintain consistency among terminals. The problem is:
    // If parameters (x = 0, y = 0) are passed, the cursor will move to (1, 1). 
    // If parameters (x < 0, y < 0) are passed, the cursor will move to (1, 1) on Apple Terminal, or not move on iTerm.
    if (x < 1) x = 1;
    if (y < 1) y = 1;
    printf("\033[%d;%df", y, x);
    fflush(stdout);
}

static termios_t stdin_disable_icanon(cc_t vmin, cc_t vtime);
static void stdin_restore(const termios_t* old);

// If getxy returns true, (x, y) will be (1 <= x <= width, 1 <= y <= height).
// If getxy returns false, (x, y) will not be assigned.
bool getxy(int* x, int* y);
void get_winsize(int* width, int* height);
int getch_();
void printf_at_r(int x, int y, const char* format, ...);

#endif // __UTIL__TERM_H__