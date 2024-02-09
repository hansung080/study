#include <termios.h>
#include <unistd.h>
#include "term.h"

extern void gotoxy(int x, int y);
extern void putchar_at(int c, int x, int y);
extern void putwchar_at(wchar_t wc, int x, int y);
extern void clrscr();

int getch_() {
    int ch;
    struct termios old, new;
    
    tcgetattr(STDIN_FILENO, &old);
    new = old;
    new.c_lflag &= ~(ICANON | ECHO); // Disable canonical input and echoing.
    new.c_cc[VMIN] = 1;  // Set the minimum input buffer size to 1 character.
    new.c_cc[VTIME] = 0; // Set the buffer flush timeout to 0 second.
    tcsetattr(STDIN_FILENO, TCSANOW, &new);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &old);
    return ch;
}
