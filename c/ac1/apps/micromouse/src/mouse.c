#include <stdlib.h>
#include <ac1/src/log.h>
#include "mouse.h"
#include "path.h"

pos_t mouse_get_pos_ahead(pos_t pos, int direction) {
    switch (direction) {
    case UP:
        --(pos.y);
        break;
    case RIGHT:
        ++(pos.x);
        break;
    case DOWN:
        ++(pos.y);
        break;
    case LEFT:
        --(pos.x); 
        break;
    default:
        error("mouse_get_pos_ahead: invalid direction: %d\n", direction);
        exit(1);
    }
    return pos;
}

void mouse_ready(const mouse_t* mouse) {
    putwchar_at_pos(mouse->pos, U_MOUSE);
    path_add(mouse->pos);
}

void mouse_go_forward(mouse_t* mouse) {
    putchar_at_pos(mouse->pos, ' ');
    mouse->pos = mouse_get_pos_ahead(mouse->pos, mouse->direction);
    putwchar_at_pos(mouse->pos, U_MOUSE);
    path_add(mouse->pos);
}

void mouse_turn_right(mouse_t* mouse) {
    if (mouse->direction == LEFT) {
        mouse->direction = UP;
    } else {
        mouse->direction <<= 1;
    }
}

void mouse_turn_left(mouse_t* mouse) {
    if (mouse->direction == UP) {
        mouse->direction = LEFT;
    } else {
        mouse->direction >>= 1;
    }
}

bool mouse_is_wall_ahead(const mouse_t* mouse, const maze_t* maze) {
    return maze_is_wall(maze, mouse_get_pos_ahead(mouse->pos, mouse->direction));
}

bool mouse_is_in_maze(const mouse_t* mouse, const maze_t* maze) {
    return 0 < mouse->pos.x && mouse->pos.x < maze->columns - 1 && 0 < mouse->pos.y && mouse->pos.y < maze->rows - 1;
}
