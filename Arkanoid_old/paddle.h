#ifndef PADDLE_H 
#define PADDLE_H

#include "gameObj.h"

class Paddle: public GameObj{

public:
    Paddle(int x, int y);
    int xDir = 0;
    int yDir = 1; 

};

#endif