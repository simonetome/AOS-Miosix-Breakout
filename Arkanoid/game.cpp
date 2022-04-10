#include "game.h"
#include "settings.h"
#include <thread>
#include <chrono>



Game::Game(){
    for (int i = 0; i <= BRICKROWS; ++i){
        for (int j = 0; j < COLS; j += BRICKWIDTH+1){
            this->blocks.push_front(std::make_unique<Block>(i+ROWOFFSET,j+COLOFFSET));
        }
    }
    sphere = std::make_unique<Sphere>(ROWS-ROWOFFSET*2,(int)COLS/2 + COLOFFSET);
    paddle = std::make_unique<Paddle>(ROWS-ROWOFFSET,(int)COLS/2 + COLOFFSET);
}


void Game::startGame(){
    
    this->canvas.reset();
    this->canvas.firstRender(blocks,paddle,sphere);

    

    std::this_thread::sleep_for(std::chrono::seconds(1));
    canvas.movePaddle(*paddle,-1);
    paddle->setCol(paddle->getCol()-1);

    std::this_thread::sleep_for(std::chrono::seconds(1));
    canvas.movePaddle(*paddle,-1);
    paddle->setCol(paddle->getCol()-1);

    std::this_thread::sleep_for(std::chrono::seconds(1));
    canvas.moveSphere(*sphere,1,1);
    sphere->updatePosition(1,1);

    std::this_thread::sleep_for(std::chrono::seconds(1));
    canvas.moveSphere(*sphere,1,-1);
    sphere->updatePosition(1,-1);

    std::this_thread::sleep_for(std::chrono::seconds(1));
    canvas.moveSphere(*sphere,-1,1);
    sphere->updatePosition(-1,1);

    std::this_thread::sleep_for(std::chrono::seconds(1));
    canvas.moveSphere(*sphere,-1,-1);
    sphere->updatePosition(-1,-1);

    std::this_thread::sleep_for(std::chrono::seconds(1));
    canvas.moveSphere(*sphere,1,0);
    sphere->updatePosition(1,0);

    std::this_thread::sleep_for(std::chrono::seconds(1));
    canvas.moveSphere(*sphere,0,1);
    sphere->updatePosition(0,1);


    /*
    while(1){
        
    }
    */

}

int Game::getScore(){
    return this->score;
}
