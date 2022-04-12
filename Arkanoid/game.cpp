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
        for (int j = 0; j < COLS; j += BRICKWIDTH){
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
    
    int sphereRow;
    int sphereCol;
    int paddlesx;
    int paddledx;
    int blocksx;
    int blockdx;
    
    while(1){
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        
        // check for collision 

        // if rowDir == 1 it has only sense in checking paddle collisions 
        // otherwise we must check for block collisions 

        sphereRow = sphere -> getRow();
        sphereCol = sphere -> getCol();
        paddlesx = paddle -> getCol();
        paddledx = paddlesx + PADDLEWIDTH -1;

        if(sphere->getRowDir() == 1){
            
            if(sphereRow == paddle->getRow() - 1 ){
                if(sphereCol <= paddledx && sphereCol >= paddlesx && sphereCol <= paddledx - (int)PADDLEWIDTH/2){
                    sphere -> setColDir(-1);
                }
                else{
                    sphere -> setColDir(1);
                }
                sphere->setRowDir(-1);
                
            }
        }
        else{
            for (auto const& b : blocks) {
                blocksx = b -> getCol();
                blockdx = blocksx + BRICKWIDTH - 1;
                
                //sphere hitting block from the bottom
                if(sphereRow == b->getRow() + 1 && (sphereCol <= blockdx && sphereCol >= blocksx)){
                    sphere->setRowDir(+1);
                    canvas.deleteObject(*b);
                    blocks.remove(b);
                }
                else{
                    if(sphereRow == b->getRow() && sphere -> getColDir() == -1 && sphereCol <= blockdx + 1 && sphereCol >= blockdx - 1){ // sphere hitting dx of block
                        sphere -> setColDir(+1);
                        canvas.deleteObject(*b);
                        blocks.remove(b);
                    }
                    else{
                        if(sphereRow == b->getRow() && sphere -> getColDir() == 1 && sphereCol >= blocksx - 1 && sphereCol <= blocksx +1){ // sphere hitting sx of block
                            sphere -> setColDir(-1);
                            canvas.deleteObject(*b);
                            blocks.remove(b);
                        }
                        else{
                            if(sphereRow == b->getRow() -1 && (sphereCol <= blockdx && sphereCol >= blocksx)){ // sphere hitting block from the top
                                sphere->setRowDir(-1);
                                canvas.deleteObject(*b);
                                blocks.remove(b);
                            }

                        }
                    }

                }

            }
        }

        /*
        #define LEFTWALLCOL 3//= COLOFFSET-2
        #define RIGHTWALLCOL 26//= COLOFFSET+COLS+1
        #define TOPWALLROW 4//= ROWOFFSET-1
        #define VERTWALLLENGTH 30
        #define HORWALLLENGTH 20
        */
        // check collision with walls 

        if(sphere -> getColDir() == 1){ //right wall 
            if(sphereCol == RIGHTWALLCOL - 1 && (sphereRow >= TOPWALLROW + 1 && sphereRow <= TOPWALLROW + 1 +VERTWALLLENGTH)){
                sphere -> setColDir(-1);
            }
        }
        else{   // left wall
            if(sphereCol == LEFTWALLCOL + 1 && (sphereRow >= TOPWALLROW + 1 && sphereRow <= TOPWALLROW + 1 +VERTWALLLENGTH)){
                sphere -> setColDir(+1);
            }
        }

        if(sphere -> getRowDir() == -1 && (sphereCol >= LEFTWALLCOL && sphereCol <= RIGHTWALLCOL && sphereRow <= TOPWALLROW + 1)){ //top wall 

            sphere -> setRowDir(+1);
        }




        canvas.moveSphere(*sphere,sphere->getRowDir(),sphere->getColDir());
        sphere->updatePosition(sphere->getRowDir(),sphere->getColDir());

    }
    
    inputThread.join();

}

int Game::getScore(){
    return this->score;
}
