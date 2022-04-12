#include "block.h"
#include "settings.h"

Block::Block(int row, int col){
    this->row = row;
    this->col = col;
    this->width = BRICKWIDTH;
    this->shapestr = FULLBLOCK;
}
