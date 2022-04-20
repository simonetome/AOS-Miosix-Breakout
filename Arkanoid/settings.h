#ifndef SETTINGS_H
#define SETTINGS_H

#define COLS 36
#define ROWS 40

#define COLOFFSET 5
#define ROWOFFSET 5

#define BRICKWIDTH 6
#define BRICKROWS 4


#define LEFTWALLCOL 3//= COLOFFSET-2
#define RIGHTWALLCOL 42//= COLOFFSET+COLS+1
#define TOPWALLROW 4//= ROWOFFSET-1
#define VERTWALLLENGTH 40
#define HORWALLLENGTH 32

//define paddle feature
#define PADDLEWIDTH 12
#define PADDLELIMITUP 20
#define PADDLELIMITBOTTOM 36

#define UPBLOCK "\u2580"
#define VERTBLOCK "\u2589"
#define LOWERBLOCK "\u2584"
#define BLOCK "\u25a3"
#define BRICK "\u25A9"
#define FULLBLOCK "\u2588"

//color
#define RED "\u001b[31m"
#define GREEN "\u001b[32m"
#define YELLOW "\u001b[33m"
#define BLUE "\u001b[34m"
#define MAGENTA "\u001b[35m"
#define CYAN "\u001b[36m"
#define WHITE "\u001b[37m"
#define RESET_COLOR "\033[0m"


#define GAMEOVER    " _____ _____ _____ _____    _____ _____ _____ _____ \x1b[2;1H|   __|  _  |     |   __|  |     |  |  |   __| __  |\x1b[3;1H|  |  |     | | | |   __|  |  |  |  |  |   __|    -|\x1b[4;1H|_____|__|__|_|_|_|_____|  |_____|____/|_____|__|__|\x1b[5;1H"
        
#define WIN " __ __ _____ _____    _ _ _ _ _____ \x1b[2;1H|  |  |     |  |  |  | | | |_|   | | \x1b[3;1H|_   _|  |  |  |  |  | | | | | | | | \x1b[2;1H|_| |_____|_____|  |_____|_|_|___| \x1b[2;1H"




#define SPHERE "\033[0;31m\u25c9\033[0m"
//#define SPHERE "\033[0;31m\u2588\033[0m"

#define BALL "\u2b24"

#endif
