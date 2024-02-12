#include <wchar.h>
#include "maze.h"
#include "common.h"

wchar_t maze_get_shape(const maze_t* maze, pos_t pos) {
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
    if (maze_deref(pos.y, pos.x) == MAZE_WALL) {
        if (pos.y > 0 && maze_deref(pos.y - 1, pos.x) == MAZE_WALL) 
            index |= UP;
        if (pos.y < maze->rows - 1 && maze_deref(pos.y + 1, pos.x) == MAZE_WALL) 
            index |= DOWN;
        if (pos.x > 0 && maze_deref(pos.y, pos.x - 1) == MAZE_WALL) 
            index |= LEFT;
        if (pos.x < maze->columns - 1 && maze_deref(pos.y, pos.x + 1) == MAZE_WALL) 
            index |= RIGHT;
    }
    return shapes[index];
}

void maze_draw(const maze_t* maze) {
    for (int y = 0; y < maze->rows; ++y) {
        for (int x = 0; x < maze->columns; ++x) {
            pos_t pos = {x, y};
            putwchar_at_pos(maze_get_shape(maze, pos), pos);
        }
    }
}
