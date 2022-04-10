#include <cstdio>
#include <string>
#include <iostream>

#include "terminal.h"


namespace Terminal
{

    void print(const std::string & s){
        std::cout<<s<<std::endl;
        fflush(stdout);
    }

    void reset(){
        printf("\e[1;1H\e[2J\n");
	    fflush(stdout);
    }

    void hideCursor(){
        printf("\e[?25l");
        fflush(stdout);
    }

    void delXY(const int & x, const int & y){
        printf("\x1b[%d;%dH ",y,x);
        fflush(stdout);
    }

    
    void printXY(const int & x, const int & y,const char * string){
        
        printf("\x1b[%d;%dH%s",y,x,string);
        fflush(stdout);
    }

    void printAndDelXY(const int & oldX,const int & oldY,const int & x, const int & y,const char * string){
        
        printf("\x1b[%d;%dH \x1b[%d;%dH%s",oldY,oldX,y,x,string);
        fflush(stdout);
    }

    void delObject(const GameObj * obj){

        for(int i = 0; i < obj->width; i++){
            printf("\x1b[%d;%dH ",obj->oldY,obj->oldX+i);
            fflush(stdout);
        }
    }

    void drawObject(const GameObj * obj){
        for(int i = 0; i < obj->width; i++){
            printf("\x1b[%d;%dH%s",obj->y,obj->x+i,obj->shape);
            fflush(stdout);
        }
        
    }
}