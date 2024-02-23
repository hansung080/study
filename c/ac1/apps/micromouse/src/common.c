#include <string.h>
#include "common.h"

extern void gotopos(pos_t p);

bool pos_equals(pos_t p1, pos_t p2) {
    return p1.x == p2.x && p1.y == p2.y;
}

void wait_(const char* msg) {
    gotoxy(TITLE_X, TITLE_Y);
    printf("%s", msg);
    getch_();
    clear_title((int)strlen(msg));
}

void print_title(const char* title) {
    gotoxy(TITLE_X, TITLE_Y);
    printf("%s", title);
}

void clear_title(int len) {
    char buf[len + 1];
    for (int i = 0; i < len; ++i) buf[i] = ' ';
    buf[len] = '\0';
    gotoxy(TITLE_X, TITLE_Y);
    printf("%s", buf);
}
