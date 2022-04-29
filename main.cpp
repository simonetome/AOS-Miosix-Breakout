

#include <cstdio>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <algorithm>
#include "miosix.h"
#include <thread>
#include "Arkanoid/settings.h"
#include "Arkanoid/game.h"


using namespace std;
using namespace miosix;




int main()
{
	int selected = MEDIUM;
	bool selecting = true;
	bool quit = false;
	
	/*reset*/
	std::printf("\e[1;1H\e[2J\n");
    fflush(stdout);

	struct termios t;
	
	/* Menu */
	do{

		char c;		
		

		printf("\e[1;1H\e[2J\n");
    	fflush(stdout);

		printf(BREAKOUT,BREAKOUTOFFSET,BREAKOUTOFFSET,BREAKOUTOFFSET,BREAKOUTOFFSET);
		printf("\x1b[11;1H Choose the option by pressing A or D, E to select");
		printf("\x1b[13;25H %s %s %s",WHITE,"EASY",RESET_COLOR);
		printf("\x1b[14;25H %s %s %s",GREEN,"MEDIUM",RESET_COLOR);
		printf("\x1b[15;25H %s %s %s",WHITE,"HARD",RESET_COLOR);
		printf("\x1b[16;25H %s %s %s",WHITE,"QUIT",RESET_COLOR);
		printf("\x1b[999;999H");
		fflush(stdout);


		do{
			
			tcgetattr(STDIN_FILENO,&t);
			t.c_lflag &= ~ECHO;
			t.c_lflag &= ~(ICANON);
			tcsetattr(STDIN_FILENO,TCSANOW,&t);
			
			c=getchar();

			tcgetattr(STDIN_FILENO,&t);
			t.c_lflag |= ECHO;
			t.c_lflag |= (ICANON);
			tcsetattr(STDIN_FILENO,TCSANOW,&t);
			fflush(stdout);

			if(c=='d')
			{
				selected = std::min(selected+1,QUIT);

			}else if(c=='a')
			{
				selected = std::max(selected-1,EASY);

			}
			else if(c=='e')
			{
				selecting = false;
				if(selected == QUIT)
				{
					quit = true;
				}
			}

			switch (selected)
			{
			case EASY:
				printf("\x1b[11;1H Choose the option by pressing A or D, E to select");
				printf("\x1b[13;25H %s %s %s",GREEN,"EASY",RESET_COLOR);
				printf("\x1b[14;25H %s %s %s",WHITE,"MEDIUM",RESET_COLOR);
				printf("\x1b[15;25H %s %s %s",WHITE,"HARD",RESET_COLOR);
				printf("\x1b[16;25H %s %s %s",WHITE,"QUIT",RESET_COLOR);
				printf("\x1b[999;999H");
				fflush(stdout);
				break;
			case MEDIUM:
				printf("\x1b[11;1H Choose the option by pressing A or D, E to select");
				printf("\x1b[13;25H %s %s %s",WHITE,"EASY",RESET_COLOR);
				printf("\x1b[14;25H %s %s %s",GREEN,"MEDIUM",RESET_COLOR);
				printf("\x1b[15;25H %s %s %s",WHITE,"HARD",RESET_COLOR);
				printf("\x1b[16;25H %s %s %s",WHITE,"QUIT",RESET_COLOR);
				printf("\x1b[999;999H");
				fflush(stdout);	
				break;
			case HARD:
				printf("\x1b[11;1H Choose the option by pressing A or D, E to select");
				printf("\x1b[13;25H %s %s %s",WHITE,"EASY",RESET_COLOR);
				printf("\x1b[14;25H %s %s %s",WHITE,"MEDIUM",RESET_COLOR);
				printf("\x1b[15;25H %s %s %s",GREEN,"HARD",RESET_COLOR);
				printf("\x1b[16;25H %s %s %s",WHITE,"QUIT",RESET_COLOR);
				printf("\x1b[999;999H");
				fflush(stdout);
				break;
			case QUIT:
				printf("\x1b[11;1H Choose the option by pressing A or D, E to select");
				printf("\x1b[13;25H %s %s %s",WHITE,"EASY",RESET_COLOR);
				printf("\x1b[14;25H %s %s %s",WHITE,"MEDIUM",RESET_COLOR);
				printf("\x1b[15;25H %s %s %s",WHITE,"HARD",RESET_COLOR);
				printf("\x1b[16;25H %s %s %s",GREEN,"QUIT",RESET_COLOR);
				printf("\x1b[999;999H");
				fflush(stdout);
				break;
			default:
				break;
			}


		}while(selecting);

		if(!quit){
			Game game(selected);
			game.startGame();
			/* game has ended */
			selecting = true;
			quit = false;
		}

		selected=MEDIUM;
	}while(!quit);

	std::printf("\e[1;1H\e[2J\n");
    fflush(stdout);

	return 0;

}







