#include <ac1/src/util/term.h>
#include "term.h"

void init_util__term(t_test_t tests[], size_t* n) {
    tests[(*n)++] = t_new("test/util/term/test_gotoxy_getxy", test_gotoxy_getxy);
}

bool test_gotoxy_getxy() {
    int old_x, old_y;
    if (!getxy(&old_x, &old_y)) return false;

    int ws_x, ws_y;
    get_winsize(&ws_x, &ws_y);

    struct case_ {
        int x;
        int y;
        int want_x;
        int want_y;
    };

    struct case_ cases[] = {
        {-1, -1, old_x, old_y},
        {-1, 2, old_x, old_y},
        {2, -1, old_x, old_y},
        {0, 0, 1, 1},
        {0, 2, 1, 2},
        {2, 0, 2, 1},
        {ws_x + 1, ws_y + 1, ws_x, ws_y},
        {ws_x + 1, 2, ws_x, 2},
        {2, ws_y + 1, 2, ws_y},
        {1, 1, 1, 1},
        {ws_x / 2, ws_y / 2, ws_x / 2, ws_y / 2},
        {ws_x, ws_y, ws_x, ws_y},
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