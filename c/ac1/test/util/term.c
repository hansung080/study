#include <ac1/src/util/term.h>
#include "term.h"

void init_util__term(test_t t[], int* n) {
    int i = *n;
    t[i++] = new_test("test/util/term/test_gotoxy_getxy", test_gotoxy_getxy);
    *n = i;
}

bool test_gotoxy_getxy() {
    int old_x, old_y;
    if (!getxy(&old_x, &old_y)) return false;

    struct case_ {
        int x;
        int y;
        int want_x;
        int want_y;
    };

    struct case_ cases[] = {
        {1, 1, 1, 1},
        {12, 13, 12, 13},
        {-1, -1, 12, 13},
        {-1, 5, 12, 13},
        {5, -1, 12, 13},
        {0, 0, 1, 1},
        {0, 7, 1, 7},
        {7, 0, 7, 1},
    };

    int len = sizeof(cases) / sizeof(struct case_);
    int got_x = -99, got_y = -99;
    for (int i = 0; i < len; ++i) {
        struct case_ c = cases[i];
        gotoxy(c.x, c.y);
        if (!getxy(&got_x, &got_y)) return false;
        if (got_x != c.want_x || got_y != c.want_y) {
            gotoxy(old_x, old_y);        
            fail("gotoxy(%d, %d) => getxy(%d, %d), want (%d, %d)\n", c.x, c.y, got_x, got_y, c.want_x, c.want_y);
            return false;
        }
    }
    gotoxy(old_x, old_y);
    return true;
}