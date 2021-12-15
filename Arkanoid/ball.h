#ifndef BALL_H
#define BALL_H

#include "gameObj.h"

class Ball : public GameObj{

public:
    Ball(int x, int y);
    int xDir = 1;
    int yDir = 1; 

};

#endif