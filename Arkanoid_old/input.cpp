#include "input.h"
#include <thread>
#include <termios.h>
#include <iostream>
#include <unistd.h>

namespace Input
{
    void inputController(Paddle * paddle)
    {
        struct termios t;
        
        tcgetattr(STDIN_FILENO,&t);
        t.c_lflag &= ~ECHO;             // ECHO is a flag to print input characters 
        t.c_lflag &= ~(ICANON);         // ICANON -> canonical mode ()
        t.c_cc[VTIME] = 0;
        t.c_cc[VMIN] = 1;
        tcsetattr(STDIN_FILENO,TCSANOW,&t);
        
        char input;

        for(;;){
            
           // std::cin >> input;
            input=getchar();
            if(input == 'd'){

                paddle -> oldX = paddle -> x;
                (paddle -> x)++;
                
            }
            if(input == 'a'){

                paddle -> oldX = paddle -> x;
                (paddle -> x)--;

            }

            input = ' ';
            
        }
    }

}