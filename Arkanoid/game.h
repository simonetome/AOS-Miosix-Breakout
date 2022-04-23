#ifndef GAME_H
#define GAME_H

#include "canvas.h"
#include "block.h"
#include "paddle.h"
#include "sphere.h"
#include <list>
#include <vector>
#include <memory>

class Game{

public:
    Game(int dif);
    void startGame();
    int getScore();
    void inputController();  

private:

    std::vector<std::unique_ptr<Block>> blocks;
    std::unique_ptr<Paddle> paddle;
    std::unique_ptr<Sphere> sphere;

    int difficulty;
    
    Canvas canvas;
    int score;
    
};

#endif