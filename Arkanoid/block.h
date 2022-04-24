#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include "shape.h"

class Block: public Shape{

    public:
        Block(int row, int col, int hp,std::string color);
        int getHp() const;
        void hit();
    private:
        int hp;

};


#endif