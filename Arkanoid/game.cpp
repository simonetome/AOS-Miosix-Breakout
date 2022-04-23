#include "game.h"
#include "settings.h"
#include <thread>
#include <chrono>
#include <stdio.h>
#include <string.h>
#include "paddle.h"
#include "canvas.h"
#include <termios.h>
#include <mutex>
#include <atomic>
#include <random> 

//variabile condivisa dai due thread 


// boolean var for ending the game 
std::atomic<bool> gameNotEnd;

// sync mutexes
std::mutex paddle_mutex;

std::random_device rd; 
std::mt19937 gen(rd());
std::uniform_int_distribution<> distr_row(OBSTACLES_BOTTOM_LIMIT,OBSTACLES_TOP_LIMIT); 
std::uniform_int_distribution<> distr_col(OBSTACLES_SX_LIMIT,OBSTACLES_DX_LIMIT); 

Game::Game(int dif){

    this->difficulty = dif;

    int row,col;

    switch (this -> difficulty)
    {
    case EASY:
        this -> obstacles_present = false;
        break;
    case MEDIUM:
        for(int i = 0; i < NUM_OBSTACLES_MEDIUM; ++i){
            row = distr_row(gen);
            col = distr_col(gen);
            obstacles.push_back(std::make_unique<Obstacle>(row,col));
        }
        this -> obstacles_present = true;
        break;
    case HARD:
        for(int i = 0; i < NUM_OBSTACLES_HARD; ++i){
            row = distr_row(gen);
            col = distr_col(gen);
            obstacles.push_back(std::make_unique<Obstacle>(row,col));
        }
        this -> obstacles_present = true;
        break;
    default:
        break;
    }

    gameNotEnd.store(true);
    for (int i = 0; i <= BRICKROWS; ++i){
        for (int j = 0; j < COLS; j += BRICKWIDTH){
            //blocks.push_front(std::make_unique<Block>(i+ROWOFFSET,j+COLOFFSET));
            //Block *b = new Block(i+ROWOFFSET,j+COLOFFSET);
            //blocks.push_back(b);
            blocks.push_back(std::make_unique<Block>(i+ROWOFFSET,j+COLOFFSET));
        }
    }
    
    sphere = std::make_unique<Sphere>(ROWS-ROWOFFSET*2,(int)COLS/2 + COLOFFSET);
    paddle = std::make_unique<Paddle>(PADDLEROW,(int)COLS/2 + COLOFFSET);
}


void Game::inputController(){
    
    char c,lastC;
    struct termios t;
    
	printf("\x1b[999;999H");     //cursor to the last cell of the terminal
    fflush(stdout);
    
    while(gameNotEnd.load() == true)
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
    		if(lastC=='d' && paddle->getCol() + PADDLEWIDTH  < RIGHTWALLCOL)
    		{
                paddle_mutex.lock();
                canvas.movePaddle(*paddle,1);
                paddle->setCol(paddle->getCol()+1);
                paddle_mutex.unlock();
    		}
		    
		    printf("\x1b[999;999H");
	    	fflush(stdout);
	    	lastC=c;
    		
    	}else if(c=='a') //move left
    	{
    		if(lastC=='a' && paddle->getCol() > LEFTWALLCOL +1)
    		{
                paddle_mutex.lock();
                canvas.movePaddle(*paddle,-1);
                paddle->setCol(paddle->getCol()-1);
                paddle_mutex.unlock();
    		}
		
		    printf("\x1b[999;999H");
	    	fflush(stdout);
	    	lastC=c;
    		
    	}

    	c=' ';
    }
    
}


void Game::startGame(){
    
    this->canvas.reset();
    this->canvas.firstRender(blocks,paddle,sphere,obstacles);

    std::thread inputThread(&Game::inputController,this);    
    
    int sphereRow;
    int sphereCol;
    int paddlesx;
    int paddledx;
    int blocksx;
    int blockdx;
    int blockrow;
    int obstaclesx;
    int obstacledx;
    int obstaclerow;

    bool won = false;

    while(1){
        switch (this->difficulty)
        {
        case EASY:
            std::this_thread::sleep_for(std::chrono::milliseconds(EASY_SPEED));
            break;
        case MEDIUM:
            std::this_thread::sleep_for(std::chrono::milliseconds(MEDIUM_SPEED));
            break;
        case HARD:
            std::this_thread::sleep_for(std::chrono::milliseconds(HARD_SPEED));
            break;
        
        default:
            break;
        }
        
        
        // check for collision 

        // if rowDir == 1 it has only sense in checking paddle collisions 
        // otherwise we must check for block collisions 

        sphereRow = sphere -> getRow();
        sphereCol = sphere -> getCol();
        paddle_mutex.lock();
        paddlesx = paddle -> getCol();
        paddle_mutex.unlock();
        paddledx = paddlesx + PADDLEWIDTH -1;
        
        // check win 
        // check loss 

        if(sphereRow == paddle->getRow()+1 ){
            won = false;
            gameNotEnd.store(false);
            break;
        }

        if(blocks.size() == 0){
            won = true;
            gameNotEnd.store(false);
            break;
        }
        
            
        if(sphereRow == paddle->getRow() - 1 && sphere ->getRowDir() == 1 && sphereCol <= paddledx+1 && sphereCol >= paddlesx-1){
            if(sphereCol <= paddledx - (int)PADDLEWIDTH/2){
                sphere -> setColDir(-1);
            }
            else{
                sphere -> setColDir(1);
            }
            sphere->setRowDir(-1);
            
        }
    

        for (int i = 0; i < blocks.size(); ++i) {
            
            blocksx = blocks[i] -> getCol();
            blockdx = blocksx + BRICKWIDTH - 1;
            blockrow = blocks[i] -> getRow();
            
        
            // hitting from top or bottom 
            if(((sphere->getRowDir()==-1 && sphereRow == blockrow+1 ) || (sphere->getRowDir()==1 && sphereRow==blockrow-1)) 

            && (sphereCol >= blocksx-1 && sphereCol <= blockdx+1))
            {
                sphere->setRowDir(sphere->getRowDir()*(-1));
                canvas.deleteObject(*blocks[i]);
                blocks.erase(blocks.begin()+i);
            }
            else
            {
                // hitting from sides 
                if(sphereRow == blockrow && ( (sphereCol == blocksx-1 && sphere->getColDir()==1)
                                            ||   (sphereCol == blockdx+1 && sphere->getColDir()==-1) ))
                {
                    sphere->setColDir(sphere->getColDir()*(-1));
                    canvas.deleteObject(*blocks[i]);
                    blocks.erase(blocks.begin()+i);
                }
            }
        }

        if(obstacles_present){
            for (int i = 0; i < obstacles.size(); ++i) {
            
                obstaclesx = obstacles[i] -> getCol();
                obstacledx = obstaclesx + OBSTACLEWIDTH - 1;
                obstaclerow = obstacles[i] -> getRow();
                
            
                // hitting from top or bottom 
                if(((sphere->getRowDir()==-1 && sphereRow == obstaclerow+1 ) || (sphere->getRowDir()==1 && sphereRow==obstaclerow-1)) 

                && (sphereCol >= obstaclesx-1 && sphereCol <= obstacledx+1))
                {
                    sphere->setRowDir(sphere->getRowDir()*(-1));
                }
                else
                {
                    // hitting from sides 
                    if(sphereRow == obstaclerow && ( (sphereCol == obstaclesx-1 && sphere->getColDir()==1)
                                                ||   (sphereCol == obstacledx+1 && sphere->getColDir()==-1) ))
                    {
                        sphere->setColDir(sphere->getColDir()*(-1));
                    }
                }
            }
        }
        

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
    
    gameNotEnd.store(false);
    inputThread.join();

    if(won){
        canvas.write(WIN);
    }else{
        canvas.write(GAMEOVER);
    }

}

int Game::getScore(){
    return this->score;
}
