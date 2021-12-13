#ifndef GAME_H
#define GAME_H

#include <list>
#include <string.h>
#include "canvas.h"

class Game{

public:
    Game();
    ~Game();
    
    void newGame();
    
private:

    Canvas canvas;
    int score;
    char grid [20][40];

};

#endif