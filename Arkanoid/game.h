#ifndef GAME_H
#define GAME_H

#include <list>
#include <string.h>
#include "canvas.h"
#include "gameObj.h"
#include "block.h"

class Game{

public:
    Game();
    ~Game();
    void startGame();
    
private:

    Canvas canvas;
    int score;
    std::list<GameObj> gameObjects;
    std::list<GameObj*> changed;
    
};

#endif