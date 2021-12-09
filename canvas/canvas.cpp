
#include "canvas.h"


    Canvas::Canvas(){
        setCanvasMode();
    }

    // set the echo and icanon mode to get in input only one characther
    //and not print it on the terminal
    void Canvas::setCanvasMode()
    {
        struct termios t;

        tcgetattr(STDIN_FILENO,&t);
            t.c_lflag &= ~ECHO;
            t.c_lflag &= ~(ICANON);
        tcsetattr(STDIN_FILENO,TCSANOW,&t);
            
    }

    //reset default settings of the terminal
    Canvas::~Canvas()
    {
        struct termios t;
        tcgetattr(STDIN_FILENO,&t);
        t.c_lflag |= ECHO;
        t.c_lflag |= (ICANON);
        tcsetattr(STDIN_FILENO,TCSANOW,&t);

    }

    //clear the screen
    void Canvas::resetCanvas()
    {
        printf("\e[1;1H\e[2J\n");
        fflush(stdout);         
    }

    //print board
    void Canvas::printTheBoard()
    {

    }

    //update ball position on the board
    void Canvas::updateBallPosition(Ball ball)
    {

    }

    //update paddle position
    void Canvas::updatePaddlePosition(Paddle Paddle)
    {

    }

    //print Block
    void Canvas::printBlock(Block block)
    {

    }
