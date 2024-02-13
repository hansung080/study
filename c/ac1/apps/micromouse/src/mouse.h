#ifndef __MOUSE_H__
#define __MOUSE_H__

#include "common.h"
#include "maze.h"

#define U_MOUSE 0x2605 // ★ (black star)

#pragma pack(push, 1)

typedef struct __mouse {
    pos_t pos;
    int direction;
} mouse_t;

#pragma pack(pop)

static pos_t mouse_get_pos_ahead(pos_t pos, int direction);
void mouse_ready(const mouse_t* mouse);
void mouse_go_forward(mouse_t* mouse);
void mouse_turn_right(mouse_t* mouse);
void mouse_turn_left(mouse_t* mouse);
bool mouse_is_wall_ahead(const mouse_t* mouse, const maze_t* maze);
bool mouse_is_in_maze(const mouse_t* mouse, const maze_t* maze);

#endif // __MOUSE_H__