#include <locale.h>
#include "common.h"
#include "maze.h"
#include "mazes.h"
#include "mouse.h"
#include "path.h"

int main(int argc, char* argv[]) {
    setlocale(LC_CTYPE, "");

    clrscr();
    maze_t maze = {(const int*)basic_maze, BASIC_MAZE_ROWS, BASIC_MAZE_COLUMNS};
    maze_draw(&maze);

    mouse_t mouse = {{maze.columns - 1, maze.rows - 2}, LEFT};
    path_init(&maze);
    navigate_by_right_hand(&maze, &mouse);

    navigate_by_shortest_path();
    path_delete();
    clrscr();
    return 0;
}
