#ifndef __PATH_H__
#define __PATH_H__

#include "common.h"
#include "maze.h"
#include "mouse.h"

#pragma pack(push, 1)

typedef struct __path {
    pos_t* arr;
    int len;
    int cap;
} path_t;

#pragma pack(pop)

void path_init(const maze_t* maze);
void path_add(pos_t pos);
static void path_remove(int i, int j);
void path_delete();

void navigate_by_right_hand(const maze_t* maze, mouse_t* mouse);
void navigate_by_shortest_path();

#endif // __PATH_H__