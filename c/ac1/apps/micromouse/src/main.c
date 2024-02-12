#include <locale.h>
#include "common.h"
#include "maze.h"
#include "mazes.h"

int main(int argc, char* argv[]) {
    setlocale(LC_CTYPE, "");

    clrscr();
    maze_t maze = {(const int*)basic_maze, BASIC_MAZE_ROWS, BASIC_MAZE_COLUMNS};
    maze_draw(&maze);
    return 0;
}
