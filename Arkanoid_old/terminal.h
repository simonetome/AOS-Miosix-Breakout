#ifndef TERMINAL_H
#define TERMINAL_H

#include "gameObj.h"

namespace Terminal
{   
    void print(const std::string & s);
    void hideCursor();
    void delXY(const int & x, const int & y);
    void printXY(const int & x, const int & y,const char * string);
    void printAndDelXY(const int & oldX,const int & oldY,const int & x, const int & y,const char * string);
    void delObject(const GameObj * obj);
    void drawObject(const GameObj * obj);
    void reset();
    
}

#endif