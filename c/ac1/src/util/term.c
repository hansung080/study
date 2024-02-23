#include <unistd.h>
#include <stdarg.h>
#include "term.h"
#include "../log.h"
#include "string.h"

extern void gotoxy(int x, int y);

termios_t stdin_disable_icanon(cc_t vmin, cc_t vtime) {
    termios_t old, new;    
    tcgetattr(STDIN_FILENO, &old);
    new = old;
    new.c_lflag &= ~(ICANON | ECHO); // Disable canonical-input and echoing.
    new.c_cc[VMIN] = vmin;   // Set the minimum input buffer size to `vmin` characters.
    new.c_cc[VTIME] = vtime; // Set the buffer flush timeout to `vtime` seconds.
    tcsetattr(STDIN_FILENO, TCSANOW, &new);
    return old;
}

void stdin_restore(const termios_t* old) {
    tcsetattr(STDIN_FILENO, TCSANOW, old);
}

bool getxy(int* x, int* y) {
    // Request the cursor position.
    if (write(STDOUT_FILENO, "\033[6n", 4) != 4) {
        error("getxy: failed on write\n");
        return false;
    }

    // The response will be ^[[y;xR for (x, y) which must be (x >= 1, y >= 1). e.g. ^[[2;1R for (1, 2).
    // The prefix ^[ represents ESC character whose ASCII code is 27, \x1B, \033 each for decimal, hexadecimal, octal number.
    char buf[30] = {0, };
    termios_t old = stdin_disable_icanon(6, 0);
    int i = (int)read(STDIN_FILENO, buf, 30);
    stdin_restore(&old);

    for (--i; i >= 5 && buf[i] != 'R'; --i);
    if (i < 5) {
        error("getxy: invalid response: %s\n", str_to_printable(buf));
        return false;
    }

    int pow, a = 0, b = 0;
    for (--i, pow = 1; i >= 3 && '0' <= buf[i] && buf[i] <= '9'; --i, pow *= 10)
        a += (buf[i] - '0') * pow;
    if (i < 3 || buf[i] != ';') {
        error("getxy: invalid response: %s\n", str_to_printable(buf));
        return false;
    }

    for (--i, pow = 1; i >= 1 && '0' <= buf[i] && buf[i] <= '9'; --i, pow *= 10)
        b += (buf[i] - '0') * pow;
    if (i < 1 || buf[i] != '[') {
        error("getxy: invalid response: %s\n", str_to_printable(buf));
        return false;
    }
    
    if (buf[--i] != A_ESC) {
        error("getxy: invalid response: %s ([%d]=%d is not esc)\n", str_to_printable(buf), i, buf[i]);
        return false;
    }
    
    *x = a, *y = b;
    return true;
}

int getch_() {
    termios_t old = stdin_disable_icanon(1, 0);
    int ch = getchar();
    stdin_restore(&old);
    return ch;
}

void printf_at_r(int x, int y, const char* format, ...) {
    int old_x, old_y;
    if (!getxy(&old_x, &old_y)) return;

    va_list ap;
    va_start(ap, format);
    gotoxy(x, y);
    vprintf(format, ap);
    va_end(ap);

    gotoxy(old_x, old_y);
}
