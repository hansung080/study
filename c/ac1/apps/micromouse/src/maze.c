#include <wchar.h>
#include "maze.h"

static int g_maze_basic[MAZE_ROWS][MAZE_COLUMNS] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

wchar_t maze_get_shape(const maze_t* m, const pos_t* p) {
    static wchar_t shapes[] = {
        U_SPACE,                         // 0000 - SPACE
        U_LIGHT_VERTICAL,                // 0001 - UP
        U_LIGHT_HORIZONTAL,              // 0010 - RIGHT
        U_LIGHT_UP_AND_RIGHT,            // 0011 - UP | RIGHT 
        U_LIGHT_VERTICAL,                // 0100 - DOWN
        U_LIGHT_VERTICAL,                // 0101 - UP | DOWN
        U_LIGHT_DOWN_AND_RIGHT,          // 0110 - RIGHT | DOWN
        U_LIGHT_VERTICAL_AND_RIGHT,      // 0111 - UP | RIGHT | DOWN
        U_LIGHT_HORIZONTAL,              // 1000 - LEFT
        U_LIGHT_UP_AND_LEFT,             // 1001 - UP | LEFT
        U_LIGHT_HORIZONTAL,              // 1010 - RIGHT | LEFT
        U_LIGHT_UP_AND_HORIZONTAL,       // 1011 - UP | RIGHT | LEFT
        U_LIGHT_DOWN_AND_LEFT,           // 1100 - DOWN | LEFT
        U_LIGHT_VERTICAL_AND_LEFT,       // 1101 - UP | DOWN | LEFT
        U_LIGHT_DOWN_AND_HORIZONTAL,     // 1110 - RIGHT | DOWN | LEFT
        U_LIGHT_VERTICAL_AND_HORIZONTAL, // 1111 - UP | RIGHT | DOWN | LEFT
    };

    int index = 0;
    if (p->y > 0 && m->arr[p->y - 1][p->x] == MAZE_WALL) index |= UP;
    if (p->y < m->rows - 1 && m->arr[p->y + 1][p->x] == MAZE_WALL) index |= DOWN;
    if (p->x > 0 && m->arr[p->y][p->x - 1] == MAZE_WALL) index |= LEFT;
    if (p->x < m->columns - 1 && m->arr[p->y][p->x + 1] == MAZE_WALL) index |= RIGHT;
    return shapes[index];
}
