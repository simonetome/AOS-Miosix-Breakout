#include "block.h"
#include "settings.h"

Block::Block(int row, int col, int hp, std::string color){
    this->row = row;
    this->col = col;
    this->width = BRICKWIDTH;
    this->shapestr = FULLBLOCK;
    this->hp = hp;
    this->color = color;
}


int Block::getHp() const { return this -> hp;}

void Block::hit() { this -> hp--; }