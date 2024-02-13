#ifndef __MAZE_H__
#define __MAZE_H__

#include <ac1/src/util/array.h>
#include "common.h"

// Reference for ASCII: https://www.asciitable.com/
// Reference for Unicode: https://symbl.cc/en/unicode/blocks/box-drawing/
#define U_SPACE                         32     // space (ASCII 32)
#define U_LIGHT_HORIZONTAL              0x2500 // ─ (Extended ASCII 196)
#define U_LIGHT_VERTICAL                0x2502 // │ (Extended ASCII 179)
#define U_LIGHT_DOWN_AND_RIGHT          0x250C // ┌ (Extended ASCII 218)
#define U_LIGHT_DOWN_AND_LEFT           0x2510 // ┐ (Extended ASCII 191)
#define U_LIGHT_UP_AND_RIGHT            0x2514 // └ (Extended ASCII 192)
#define U_LIGHT_UP_AND_LEFT             0x2518 // ┘ (Extended ASCII 217)
#define U_LIGHT_VERTICAL_AND_RIGHT      0x251C // ├ (Extended ASCII 195)
#define U_LIGHT_VERTICAL_AND_LEFT       0x2524 // ┤ (Extended ASCII 180)
#define U_LIGHT_DOWN_AND_HORIZONTAL     0x252C // ┬ (Extended ASCII 194)
#define U_LIGHT_UP_AND_HORIZONTAL       0x2534 // ┴ (Extended ASCII 193)
#define U_LIGHT_VERTICAL_AND_HORIZONTAL 0x253C // ┼ (Extended ASCII 197)

#define U_HEAVY_HORIZONTAL              0x2501 // ━
#define U_HEAVY_VERTICAL                0x2503 // ┃
#define U_HEAVY_DOWN_AND_RIGHT          0x250F // ┏
#define U_HEAVY_DOWN_AND_LEFT           0x2513 // ┓
#define U_HEAVY_UP_AND_RIGHT            0x2517 // ┗
#define U_HEAVY_UP_AND_LEFT             0x251B // ┛
#define U_HEAVY_VERTICAL_AND_RIGHT      0x2523 // ┣
#define U_HEAVY_VERTICAL_AND_LEFT       0x252B // ┫
#define U_HEAVY_DOWN_AND_HORIZONTAL     0x2533 // ┳
#define U_HEAVY_UP_AND_HORIZONTAL       0x253B // ┻
#define U_HEAVY_VERTICAL_AND_HORIZONTAL 0x254B // ╋

#define MAZE_SPACE 0
#define MAZE_WALL  1

#define maze_deref(i, j) deref2(maze->arr, maze->columns, (i), (j))

#pragma pack(push, 1)

typedef struct __maze {
    const int* arr;
    int rows;
    int columns;
} maze_t;

#pragma pack(pop)

static wchar_t maze_get_shape(const maze_t* maze, pos_t pos);
void maze_draw(const maze_t* maze);
bool maze_is_wall(const maze_t* maze, pos_t pos);

#endif // __MAZE_H__