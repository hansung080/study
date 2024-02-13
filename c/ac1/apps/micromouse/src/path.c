#include <unistd.h>
#include "path.h"

void add_path(pos_t pos) {
}

void navigate_by_right_hand(const maze_t* maze, mouse_t* mouse) {
    mouse_ready(mouse);
    sleep(2); // sleep for 2 seconds
    mouse_go_forward(mouse);
    while (mouse_is_in_maze(mouse, maze)) {
        usleep(200000); // sleep for 200 milliseconds
        mouse_turn_right(mouse);
        while (mouse_is_wall_ahead(mouse, maze)) {
            mouse_turn_left(mouse);
        }
        mouse_go_forward(mouse);
    }
    // add_path({-1, -1})
    sleep(2); // sleep for 2 seconds
}

void navigate_by_shortest_path();
