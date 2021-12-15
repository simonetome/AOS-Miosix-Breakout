#ifndef CANVAS_H
#define CANVAS_H

#include <string>
#include <termios.h>
#include <unistd.h>
#include <list>
#include "settings.h"
#include "terminal.h"
#include "gameObj.h"


class Canvas{
    public:
        Canvas();
        // set the echo and icanon mode to get in input only one characther
        //and not print it on the terminal
        /*
        void setCanvasMode();
        //reset default settings of the terminal
        void changeCanvasMode();
        ~Canvas();
        //clear the screen
        void resetCanvas();
        //print board
        void printTheBoard();
        //update ball position on the board
        void updateBallPosition(Ball ball);
        //update paddle position
        void updatePaddlePosition(Paddle paddle);
        //print Block
        void printBlock(Block block);
        */
        void drawFrame(const std::list<GameObj*> & changed);
        void drawField(const std::list<GameObj> & gameObjects);
};

#endif

