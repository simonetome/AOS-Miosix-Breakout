#include "canvas.h"
#include "settings.h"
#include <iostream>
#include <string>
#include <mutex>
#include <termios.h>
#include <cstdio>
#include <string.h>
#include <unistd.h>

#include "../miosix/interfaces/gpio.h"

//std::mutex stdout_mutex; --> not needed as printf is POSIX standard

struct termios t;

using namespace std;



void Canvas::reset(){
    printf("\e[1;1H\e[2J\n");
    fflush(stdout);
}

void Canvas::drawWalls(){

    //vertical walls
    for(int i = TOPWALLROW; i <= TOPWALLROW+VERTWALLLENGTH; ++i){
        printf("\x1b[%d;%dH%s",i,LEFTWALLCOL-1,FULLBLOCK);
        printf("\x1b[%d;%dH%s",i,LEFTWALLCOL,FULLBLOCK);
        printf("\x1b[%d;%dH%s",i,RIGHTWALLCOL,FULLBLOCK);
        printf("\x1b[%d;%dH%s",i,RIGHTWALLCOL+1,FULLBLOCK);
        fflush(stdout);
    }

    //horizontal wall
    for(int i = LEFTWALLCOL; i<= RIGHTWALLCOL; ++i){
        printf("\x1b[%d;%dH%s",TOPWALLROW,i,FULLBLOCK);
        fflush(stdout);
    }
}


void Canvas::drawObject(const Shape& object){
    int width = object.getWidth();
    int row = object.getRow();
    int col = object.getCol();
    string shape = object.getShape();
    this->changeColor(object.getColor());
    for(int i = 0; i < width; ++i){
        printf("\x1b[%d;%dH%s",row,i+col,shape.c_str());
        fflush(stdout);
    }
    this->changeColor(RESET_COLOR);
}

void Canvas::deleteObject(const Shape& object){
    int width = object.getWidth();
    int row = object.getRow();
    int col = object.getCol();
    //std::lock_guard<mutex> lck(stdout_mutex);

    for(int i = 0; i < width; ++i){
        printf("\x1b[%d;%dH%s",row,i+col," ");
        fflush(stdout);
    }
}

void Canvas::movePaddle(const Shape& object,const int& rowDirection){
    
    int row = object.getRow();
    int col = object.getCol();
    
    //std::lock_guard<mutex> lck(stdout_mutex);
    
    if(rowDirection == 1){ // move right
        printf("\x1b[%d;%dH%s",row,col," ");
        printf("\x1b[%d;%dH%s",row,col+PADDLEWIDTH,FULLBLOCK);
        printf("\x1b[999;999H");
        fflush(stdout); 
    }
    else{ // move left
        printf("\x1b[%d;%dH%s",row,col-1,FULLBLOCK);
        printf("\x1b[%d;%dH%s",row,col+PADDLEWIDTH-1," ");
        printf("\x1b[999;999H");
        fflush(stdout); 
    }
}
void Canvas::moveSphere(const Shape& object,const int& rowDirection,const int& colDirection){
    
    int row = object.getRow();
    int col = object.getCol();
    
    //std::lock_guard<mutex> lck(stdout_mutex);

    printf("\x1b[%d;%dH%s",row,col," ");
    printf("\x1b[%d;%dH%s",row+rowDirection,col+colDirection,SPHERE);
    printf("\x1b[999;999H");
    fflush(stdout);

}


void Canvas::firstRender(const std::vector<std::unique_ptr<Block>>& blocks,const std::unique_ptr<Paddle>& paddle,const std::unique_ptr<Sphere>& sphere,const std::vector<std::unique_ptr<Obstacle>>& obstacles){

    this->drawWalls();
    
    for (auto const& b : blocks) {
        this->drawObject(*b);
    }
    

    for (auto const& o : obstacles) {       
        this->drawObject(*o);
    }

    this->drawObject(*paddle);
    this->drawObject(*sphere);

    printf("\x1b[999;999H");
    fflush(stdout); 
    
}


void Canvas::write(bool won){
    this->reset();
    printf("\x1b[1;1H");
    if(won)
        printf(WIN,WINOFFSET,WINOFFSET,WINOFFSET,WINOFFSET);
    else
        printf(GAMEOVER,GAMEOVEROFFSET,GAMEOVEROFFSET,GAMEOVEROFFSET,GAMEOVEROFFSET);
    printf("\x1b[25;%dH Press ENTER to continue",(VERTICAL_SIZE-24)/2);
    printf("\x1b[999;999H");
    fflush(stdout);

    
    std::unique_ptr<miosix::GpioPin> select = std::make_unique<miosix::GpioPin>(GPIOD_BASE,4);
	select->mode(miosix::Mode::INPUT);

    if(BUTTON) // Button input (settings.h)
    {
        
        int lastS=0;
        while(true){
            int selection=select->value();
            if(selection==0 && lastS==1)
                break;
            lastS=selection;
        }
    }
    else
    {
        // Keyboard input (settings.h)
        char c = ' ';
        do{
 
            //keyboard input
            c=getchar();
        }while(c != 'e');
    }

}


void Canvas::changeColor(const std::string& color){
    cout<<color;
    fflush(stdout);
}