#include "game.h"
#include "block.h"
#include "ball.h"
#include "paddle.h"
#include <thread>
#include "input.h"

Game::Game():canvas(),score(0)
{

}

void Game::startGame()
{
    score=0;

    Paddle * paddle = new Paddle(10,10);
    Ball * ball = new Ball(10,10);

    std::thread inputTh(Input::inputController,paddle);    

    gameObjects.push_front(paddle);
    gameObjects.push_front(ball);
    

    //canvas.drawField(gameObjects);


    //changed.push_front(ball); 
    changed.push_front(paddle);

    for(;;){

        /*
        ball -> oldX = ball -> x;
        ball -> oldY = ball -> y;
        ball -> x += ball -> xDir;
        ball -> y += ball -> yDir;
        */

        canvas.drawFrame(changed);

        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }

    inputTh.join();

}

Game::~Game()
{

}