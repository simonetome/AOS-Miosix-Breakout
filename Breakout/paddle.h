#ifndef PADDLE_H
#define PADDLE_H

#include "shape.h"
#include <string>

/**
 * @brief represents the moving paddle in the game, what the player con
 * 
 */
class Paddle: public Shape{

    public:
        /**
         * @brief Construct a new Paddle object
         * 
         * @param row row position of the paddle 
         * @param col column position of the paddle 
         */
        Paddle(int row, int col);
    private:
        

};


#endif