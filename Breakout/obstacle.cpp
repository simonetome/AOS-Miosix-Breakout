#include "obstacle.h"
#include "settings.h"


Obstacle::Obstacle(int row, int col){
    this -> row = row;
    this -> col = col;
    this->width = OBSTACLEWIDTH;
    this->shapestr = OBSTACLE;
    this->color = MAGENTA;
}