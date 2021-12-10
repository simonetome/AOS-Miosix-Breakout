#ifndef GAME_H
#define GAME_H

#include <list>
#include <string.h>
#include "../canvas/canvas.h"

class Game{

public:
    Game();
    ~Game();
    void newGame(Canvas canvas);

    int score=0;
private:

    char grid [20] [40];

};

#endif