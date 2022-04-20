#include "canvas.h"
#include "settings.h"
#include <iostream>
#include <string>

std::vector<std::string> color={RED,YELLOW,BLUE,GREEN,MAGENTA,CYAN,WHITE};

void Canvas::reset(){
    std::printf("\e[1;1H\e[2J\n");
    fflush(stdout);
}

void Canvas::drawWalls(){
    // blocks starts from rowoffset and coloffset, thus walls must start from it -1 


    //LEFTWALLCOL = COLOFFSET-2
    //RIGHTWALLCOL = COLOFFSET+COLS+1
    //TOPWALLROW = ROWOFFSET-1


    //vertical walls
    for(int i = TOPWALLROW; i <= TOPWALLROW+VERTWALLLENGTH; ++i){
        std::printf("\x1b[%d;%dH%s",i,LEFTWALLCOL,FULLBLOCK);
        fflush(stdout);
        std::printf("\x1b[%d;%dH%s",i,RIGHTWALLCOL,FULLBLOCK);
        fflush(stdout);
    }

    //horizontal wall
    for(int i = LEFTWALLCOL; i<= RIGHTWALLCOL; ++i){
        std::printf("\x1b[%d;%dH%s",TOPWALLROW,i,FULLBLOCK);
        fflush(stdout);
    }


}


void Canvas::drawObject(const Shape& object){
    int width = object.getWidth();
    int row = object.getRow();
    int col = object.getCol();
    std::string shape = object.getShape();

    for(int i = 0; i < width; ++i){
        std::printf("\x1b[%d;%dH%s",row,i+col,shape.c_str());
        fflush(stdout);
    }
}

void Canvas::deleteObject(const Shape& object){
    int width = object.getWidth();
    int row = object.getRow();
    int col = object.getCol();

    for(int i = 0; i < width; ++i){
        std::printf("\x1b[%d;%dH%s",row,i+col," ");
        fflush(stdout);
    }
}

void Canvas::movePaddle(const Shape& object,const int& rowDirection){
    int row = object.getRow();
    int col = object.getCol();
    
    if(rowDirection == 1){ // move right
        std::printf("\x1b[%d;%dH%s",row,col," ");
        fflush(stdout);
        std::printf("\x1b[%d;%dH%s",row,col+PADDLEWIDTH,FULLBLOCK);
        fflush(stdout);
        printf("\x1b[999;999H");
        fflush(stdout); 
    }
    else{ // move left
        printf("\x1b[%d;%dH%s",row,col-1,FULLBLOCK);
        fflush(stdout);
        printf("\x1b[%d;%dH%s",row,col+PADDLEWIDTH-1," ");
        fflush(stdout);
        printf("\x1b[999;999H");
        fflush(stdout); 
    }
}
void Canvas::moveSphere(const Shape& object,const int& rowDirection,const int& colDirection){
    int row = object.getRow();
    int col = object.getCol();
    std::printf("\x1b[%d;%dH%s",row,col," ");
    fflush(stdout);
    std::printf("\x1b[%d;%dH%s",row+rowDirection,col+colDirection,SPHERE);
    fflush(stdout);
    printf("\x1b[999;999H");
    fflush(stdout);

}


void Canvas::firstRender(const std::vector<std::unique_ptr<Block>>& blocks,const std::unique_ptr<Paddle>& paddle,const std::unique_ptr<Sphere>& sphere){

    
    this->drawWalls();
    
    int temp=0;
    int row=0;
    this->changeColor(color.at(row));
    for (auto const& b : blocks) {
                
        this->drawObject(*b);
        temp+=BRICKWIDTH;

        if (temp==COLS)
        {
            row++;
            this->changeColor(color.at(row));
            temp=0;
        }

    }

    this->changeColor(RESET_COLOR);
    this->drawObject(*paddle);
    this->drawObject(*sphere);

    printf("\x1b[999;999H");
    fflush(stdout); 
    
}


void Canvas::write(const std::string& towrite){
    this->reset();
    
    printf("\x1b[1;1H");
    printf("%s",towrite.c_str());
    fflush(stdout);
}


void Canvas::changeColor(const std::string& color){

    std::cout<<color;
    fflush(stdout);
}