#include "game.h"
#include "block.h"
#include "ball.h"
#include "paddle.h"
#include <thread>

Game::Game():canvas(),score(0)
{

}

void Game::startGame()
{
    score=0;
    
    Block b(5,5);
    Paddle paddle(20,20);
    
    gameObjects.push_front(b);
    gameObjects.push_front(paddle);
    

    Ball * ball = new Ball(10,10);

    canvas.drawField(gameObjects);

    changed.push_front(ball); // ball is always moving 

    for(;;){

        ball -> oldX = ball -> x;
        ball -> oldY = ball -> y;
        ball -> x += ball -> xDir;
        ball -> y += ball -> yDir;

        canvas.drawFrame(changed);

        std::this_thread::sleep_for(std::chrono::milliseconds(80));
    }

}

Game::~Game()
{

}