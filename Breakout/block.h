#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include "shape.h"

/**
 * @brief Block represent the bricks that needs to be broken in order to win.
 * 
 */
class Block: public Shape{

    public:
        /**
         * @brief Construct a new Block shape.
         * 
         * @param row row position of the block
         * @param col column position of the block 
         * @param hp hit points for the object: 1 -> the block just need 1 hit to be destroyed, 2 -> 2 hits to be destroyed, etc. 
         * @param color color string (settings.h) for the block. 
         */
        Block(int row, int col, int hp,std::string color);
        /**
         * @brief return the hit points, if 0 the block is destroyed.
         * 
         * @return int 
         */
        int getHp() const;
        /**
         * @brief hit the block in case of collision, reduce the hit points.
         */
        void hit();
    private:
        /**
         * @brief each block has hit points: they represent the amount of hit the block needs to receive in order to be broken. 
         */
        int hp;

};


#endif