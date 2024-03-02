#include <ac1/src/util/term.h>
#include "term.h"

void init_util__term(t_test_t tests[], size_t* n) {
    tests[(*n)++] = t_new("test/util/term/test_gotoxy_getxy", test_gotoxy_getxy);
}

bool test_gotoxy_getxy() {
    int old_x, old_y;
    if (!getxy(&old_x, &old_y)) return false;

    int width, height;
    get_winsize(&width, &height);

    struct case_ {
        int x;
        int y;
        int want_x;
        int want_y;
    };

    struct case_ cases[] = {
        {-1, -1, 1, 1},
        {-1, 2, 1, 2},
        {2, -1, 2, 1},
        {0, 0, 1, 1},
        {0, 2, 1, 2},
        {2, 0, 2, 1},
        {width + 1, height + 1, width, height},
        {width + 1, 2, width, 2},
        {2, height + 1, 2, height},
        {1, 1, 1, 1},
        {width / 2, height / 2, width / 2, height / 2},
        {width, height, width, height},
    };

    int len = sizeof(cases) / sizeof(struct case_);
    int got_x = -99, got_y = -99;
    for (int i = 0; i < len; ++i) {
        struct case_ c = cases[i];
        gotoxy(c.x, c.y);
        if (!getxy(&got_x, &got_y)) return false;
        if (got_x != c.want_x || got_y != c.want_y) {
            gotoxy(old_x, old_y);        
            t_fail("gotoxy(%d, %d) => getxy(%d, %d), want (%d, %d)\n", c.x, c.y, got_x, got_y, c.want_x, c.want_y);
            return false;
        }
    }
    gotoxy(old_x, old_y);
    return true;
}