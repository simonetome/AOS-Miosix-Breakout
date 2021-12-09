
#include <string>
#include <termios.h>
#include <unistd.h>
#include "../game/gameObj/block.h"
#include "../game/gameObj/ball.h"
#include "../game/gameObj/paddle.h"


class Canvas{
    public:
        Canvas();
        // set the echo and icanon mode to get in input only one characther
        //and not print it on the terminal
        void setCanvasMode();
        //reset default settings of the terminal
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


};