#ifndef __PATH_H__
#define __PATH_H__

#include "common.h"
#include "maze.h"
#include "mouse.h"

void add_path(pos_t pos);
void navigate_by_right_hand(const maze_t* maze, mouse_t* mouse);
void navigate_by_shortest_path();

#endif // __PATH_H__