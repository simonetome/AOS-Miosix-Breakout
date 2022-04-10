#include "game.h"
#include "settings.h"
#include <thread>
#include <chrono>
#include <stdio.h>
#include <string.h>
#include "paddle.h"
#include "canvas.h"
#include <termios.h>

Game::Game(){
    for (int i = 0; i <= BRICKROWS; ++i){
        for (int j = 0; j < COLS; j += BRICKWIDTH+1){
            this->blocks.push_front(std::make_unique<Block>(i+ROWOFFSET,j+COLOFFSET));
        }
    }
    sphere = std::make_unique<Sphere>(ROWS-ROWOFFSET*2,(int)COLS/2 + COLOFFSET);
    paddle = std::make_unique<Paddle>(ROWS-ROWOFFSET,(int)COLS/2 + COLOFFSET);
}


void Game::inputController(){
    
    char c,lastC;
    struct termios t;
    
	printf("\x1b[999;999H");     //cursor to the last cell of the terminal
    fflush(stdout);
    for(;;)
    {
	//set option to take in input only one character
    	tcgetattr(STDIN_FILENO,&t);
        t.c_lflag &= ~ECHO;
        t.c_lflag &= ~(ICANON);
        tcsetattr(STDIN_FILENO,TCSANOW,&t);
        
        c=getchar();

        tcgetattr(STDIN_FILENO,&t);
        t.c_lflag |= ECHO;
        t.c_lflag |= (ICANON);
        tcsetattr(STDIN_FILENO,TCSANOW,&t);
        //move right
        if(c=='d')
    	{
    		if(lastC=='d')
    		{
                canvas.movePaddle(*paddle,1);
                paddle->setCol(paddle->getCol()+1);
    		}
		    fflush(stdout);
		    printf("\x1b[999;999H");
	    	fflush(stdout);
	    	lastC=c;
    		
    	}else if(c=='a') //move left
    	{
    		if(lastC=='a')
    		{
                canvas.movePaddle(*paddle,-1);
                paddle->setCol(paddle->getCol()-1);
    		}
		    fflush(stdout);
		    printf("\x1b[999;999H");
	    	fflush(stdout);
	    	lastC=c;
    		
    	}

    	c=' ';
    }
    
}


void Game::startGame(){
    
    this->canvas.reset();
    this->canvas.firstRender(blocks,paddle,sphere);

    std::thread inputThread(&Game::inputController,this);    

    /*
    while(1){
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        canvas.moveSphere(*sphere,sphere->getRowDir(),sphere->getColDir());
        sphere->updatePosition(sphere->getRowDir(),sphere->getColDir());

    }
    */
    inputThread.join();

}

int Game::getScore(){
    return this->score;
}
