#include "maze.h"

int maze_get_shape(const maze_t* maze, const pos_t* pos) {
    static int shapes[] = {
        32,  // 0000 - SPACE
        179, // 0001 - UP
        196, // 0010 - RIGHT
        192, // 0011 - UP | RIGHT 
        179, // 0100 - DOWN
        179, // 0101 - UP | DOWN
        218, // 0110 - RIGHT | DOWN
        195, // 0111 - UP | RIGHT | DOWN
        196, // 1000 - LEFT
        217, // 1001 - UP | LEFT
        196, // 1010 - RIGHT | LEFT
        193, // 1011 - UP | RIGHT | LEFT
        191, // 1100 - DOWN | LEFT
        180, // 1101 - UP | DOWN | LEFT
        194, // 1110 - RIGHT | DOWN | LEFT
        197, // 1111 - UP | RIGHT | DOWN | LEFT
    };

    return 0;
}
