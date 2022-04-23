#ifndef GAME_H
#define GAME_H

#include "canvas.h"
#include "block.h"
#include "paddle.h"
#include "sphere.h"
#include "obstacle.h"
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
    std::vector<std::unique_ptr<Obstacle>> obstacles;
    std::unique_ptr<Paddle> paddle;
    std::unique_ptr<Sphere> sphere;

    int difficulty;

    bool obstacles_present;
    
    Canvas canvas;
    int score;
    
};

#endif