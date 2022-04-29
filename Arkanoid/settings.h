#ifndef SETTINGS_H
#define SETTINGS_H

#define COLS 36
#define ROWS 40


//terminal size: 70 columns, 45 rows 
#define ORIZONTAL_SIZE 45
#define VERTICAL_SIZE 70

//game space
#define VERTWALLLENGTH 40
#define HORWALLLENGTH 32

//offset
#define COLOFFSET ((VERTICAL_SIZE-COLS+2)/2)    
#define ROWOFFSET ((ORIZONTAL_SIZE-HORWALLLENGTH-2)/2)

//gameOver length:50
#define GAMEOVEROFFSET ((VERTICAL_SIZE-50)/2)
//Breakout length:48
#define BREAKOUTOFFSET ((VERTICAL_SIZE-48)/2)
//Win length:35
#define WINOFFSET ((VERTICAL_SIZE-35)/2)

#define BRICKWIDTH 9
#define BRICKROWS 3


#define LEFTWALLCOL COLOFFSET - 2
#define RIGHTWALLCOL COLOFFSET + COLS + 1
#define TOPWALLROW ROWOFFSET - 1


//define paddle feature
#define PADDLEWIDTH 12
#define PADDLELIMITUP 20
#define PADDLELIMITBOTTOM 36
#define PADDLEROW 35

#define UPBLOCK "\u2580"
#define VERTBLOCK "\u2589"
#define LOWERBLOCK "\u2584"
#define BLOCK "\u25a3"
#define BRICK "\u25A9"
#define FULLBLOCK "\u2588"

#define OBSTACLE "\u2593"
#define OBSTACLEWIDTH 9
#define NUM_OBSTACLES_MEDIUM 1
#define NUM_OBSTACLES_HARD 2
#define OBSTACLES_BOTTOM_LIMIT TOPWALLROW + BRICKROWS + 2
#define OBSTACLES_TOP_LIMIT PADDLEROW - 6
#define OBSTACLES_SX_LIMIT LEFTWALLCOL + 1
#define OBSTACLES_DX_LIMIT RIGHTWALLCOL - OBSTACLEWIDTH 


//color
#define RED "\u001b[31m"
#define GREEN "\u001b[32m"
#define YELLOW "\u001b[33m"
#define BLUE "\u001b[34m"
#define MAGENTA "\u001b[35m"
#define CYAN "\u001b[36m"
#define WHITE "\u001b[37m"

#define BRIGHTRED "\u001b[91m"
#define BRIGHTGREEN "\u001b[92m"
#define BRIGHTYELLOW "\u001b[93m"
#define BRIGHTBLUE "\u001b[94m"
#define BRIGHTMAGENTA "\u001b[95m"
#define BRIGHTCYAN "\u001b[96m"





#define RESET_COLOR "\033[0m"


#define GAMEOVER   "\x1b[12;%dH _____ _____ _____ _____    _____ _____ _____ _____ \x1b[13;%dH|   __|  _  |     |   __|  |     |  |  |   __| __  |\x1b[14;%dH|  |  |     | | | |   __|  |  |  |  |  |   __|    -|\x1b[15;%dH|_____|__|__|_|_|_|_____|  |_____|____/|_____|__|__|"
        
#define WIN "\x1b[12;%dH __ __ _____ _____    _ _ _ _ _____ \x1b[13;%dH|  |  |     |  |  |  | | | |_|   | | \x1b[14;%dH|_   _|  |  |  |  |  | | | | | | | | \x1b[15;%dH|_| |_____|_____|  |_____|_|_|___| "

#define BREAKOUT  "\x1b[12;%dH _____ _____ _____ _____ _____ _____ _____ _____ \x1b[13;%dH| __  | __  |   __|  _  |  |  |     |  |  |_   _|\x1b[14;%dH| __ -|    -|   __|     |    -|  |  |  |  | | |\x1b[15;%dH|_____|__|__|_____|__|__|__|__|_____|_____| |_|"  


#define SPHERE "\u001b[92m\u25c9\033[0m"
//#define SPHERE "\033[0;31m\u2588\033[0m"

#define BALL "\u2b24"



#define EASY 0
#define MEDIUM 1
#define HARD 2
#define QUIT 3

#define EASY_SPEED 80
#define MEDIUM_SPEED 65
#define HARD_SPEED 55





#endif
