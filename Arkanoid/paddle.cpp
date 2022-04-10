#include "paddle.h"
#include "settings.h"

Paddle::Paddle(int row, int col){
    this->row = row;
    this->col = col;
    this->width = PADDLEWIDTH;
    this->shapestr = FULLBLOCK;
}

