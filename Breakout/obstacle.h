#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <string>
#include "shape.h"

/**
 * @brief represent an obstacle in the game. It has collisions with the sphere and can spawn between the paddle and the blocks.
 * The number of blocks is proportional to the chosen difficulty.
 * 
 */
class Obstacle: public Shape{

    public:
        /**
         * @brief Construct a new Obstacle object
         * 
         * @param row row position of the obstacle
         * @param col column position of the obstacle 
         */
        Obstacle(int row, int col);
    private:

};


#endif