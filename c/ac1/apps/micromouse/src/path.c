#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ac1/src/log.h>
#include "path.h"

static path_t path;

void path_init(const maze_t* maze) {
    int cap = maze->rows * maze->columns;
    path.arr = (pos_t*)malloc(sizeof(pos_t) * cap);
    if (path.arr == NULL) {
        error("path_init: failed on malloc\n");
        exit(1);
    }
    path.len = 0;
    path.cap = cap;
}

void path_add(pos_t pos) {
    if (path.len >= path.cap) {
        error("path_add: not enough capacity\n");
        exit(1);
    }
    path.arr[path.len++] = pos;
}

void path_remove(int i, int j) {
    for (++i, ++j; j < path.len; ++i, ++j) {
        path.arr[i] = path.arr[j];
    }
    path.len = i;
}

void path_delete() {
    if (path.arr != NULL) {
        free(path.arr);
        path.arr = NULL;
    }
    path.len = 0;
    path.cap = 0;
}

void navigate_by_right_hand(const maze_t* maze, mouse_t* mouse) {
    const char* title = "Navigation by Right Hand";
    mouse_ready(mouse);
    wait_("Press any key to start for right hand...");
    print_title(title);

    mouse_go_forward(mouse);
    while (mouse_is_in_maze(mouse, maze)) {
        usleep(200000); // sleep for 200 milliseconds
        mouse_turn_right(mouse);
        while (mouse_is_wall_ahead(mouse, maze)) {
            mouse_turn_left(mouse);
        }
        mouse_go_forward(mouse);
    }
    
    sleep(2); // sleep for 2 seconds
    putchar_at_pos(' ', mouse->pos);
    clear_title((int)strlen(title));
}

void navigate_by_shortest_path() {
    const char* title = "Navigation by Shortest Path";

    for (int i = 0; i < path.len; ++i) {
        for (int j = i + 1; j < path.len; ++j) {
            if (pos_equals(path.arr[i], path.arr[j])) {
                path_remove(i, j);
                j = i;
            }
        }
    }

    for (int i = 0; i < path.len; ++i) {
        putwchar_at_pos(U_MOUSE, path.arr[i]);
        if (i == 0) {
            wait_("Press any key to start for shortest path...");
            print_title(title);
        } else if (i == path.len - 1) {
            sleep(2);
        } else {
            usleep(200000);
        }
        putchar_at_pos(' ', path.arr[i]);
    }

    clear_title((int)strlen(title));
}
