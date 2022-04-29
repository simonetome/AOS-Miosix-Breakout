

#include <cstdio>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <algorithm>
#include "miosix.h"
#include <thread>
#include "Arkanoid/settings.h"
#include "Arkanoid/game.h"

#include "interfaces/gpio.h"

using namespace std;
using namespace miosix;




int main()
{
	int selected = MEDIUM;
	bool selecting = true;
	bool quit = false;
	
	/*reset*/
	std::printf("\e[1;1H\e[2J\n");
    std::fflush(stdout);

	struct termios t;

	/* Menu */
	do{

		char c;		
		int lastD=0,lastU=0,lastS=0;

		miosix::GpioPin *move_down = new miosix::GpioPin(GPIOD_BASE,6);
		miosix::GpioPin *move_up = new miosix::GpioPin(GPIOD_BASE,7);
		miosix::GpioPin *select = new miosix::GpioPin(GPIOD_BASE,4);

		select ->mode(miosix::Mode::INPUT);
		move_down ->mode(miosix::Mode::INPUT);
		move_up ->mode(miosix::Mode::INPUT);

		printf("\e[1;1H\e[2J\n");
    	std::fflush(stdout);
		
		printf(BREAKOUT,BREAKOUTOFFSET,BREAKOUTOFFSET,BREAKOUTOFFSET,BREAKOUTOFFSET);
		//printf("\x1b[21;1H Choose the option by pressing A or D, E to select");
		printf("\x1b[21;%dH Choose the option by pressing LEFT or RIGHT, ENTER to select",(VERTICAL_SIZE-60)/2);
		printf("\x1b[23;%dH %s %s %s",VERTICAL_SIZE/2-3, WHITE,"EASY",RESET_COLOR);
		printf("\x1b[24;%dH %s %s %s",VERTICAL_SIZE/2-3,GREEN,"MEDIUM",RESET_COLOR);
		printf("\x1b[25;%dH %s %s %s",VERTICAL_SIZE/2-3,WHITE,"HARD",RESET_COLOR);
		printf("\x1b[26;%dH %s %s %s",VERTICAL_SIZE/2-3,WHITE,"QUIT",RESET_COLOR);
		printf("\x1b[999;999H");
		std::fflush(stdout);


		do{
			/*
			//keyboard input
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
			}*/

			//button input
			bool is_change=false;
			//std::this_thread::sleep_for(std::chrono::milliseconds(50));
			int valU=move_up->value();
			int valD=move_down->value();
			int valS=select->value();

			if(lastD==1 && valD==0)
			{
				selected = std::min(selected+1,QUIT);
				is_change=true;

			}else if(lastU==1 && valU==0)
			{
				selected = std::max(selected-1,EASY);
				is_change=true;

			}
			else if(lastS==1 && valS==0)
			{
				selecting = false;
				if(selected == QUIT)
				{
					quit = true;
				}
			}
			lastD=valD;
			lastU=valU;
			lastS=valS;

			if(is_change)
				switch (selected)
				{
				case EASY:
					printf("\x1b[23;%dH %s %s %s",VERTICAL_SIZE/2-3, GREEN,"EASY",RESET_COLOR);
					printf("\x1b[24;%dH %s %s %s",VERTICAL_SIZE/2-3,WHITE,"MEDIUM",RESET_COLOR);
					printf("\x1b[25;%dH %s %s %s",VERTICAL_SIZE/2-3,WHITE,"HARD",RESET_COLOR);
					printf("\x1b[26;%dH %s %s %s",VERTICAL_SIZE/2-3,WHITE,"QUIT",RESET_COLOR);
					printf("\x1b[999;999H");
					std::fflush(stdout);
					break;
				case MEDIUM:
					printf("\x1b[23;%dH %s %s %s",VERTICAL_SIZE/2-3, WHITE,"EASY",RESET_COLOR);
					printf("\x1b[24;%dH %s %s %s",VERTICAL_SIZE/2-3,GREEN,"MEDIUM",RESET_COLOR);
					printf("\x1b[25;%dH %s %s %s",VERTICAL_SIZE/2-3,WHITE,"HARD",RESET_COLOR);
					printf("\x1b[26;%dH %s %s %s",VERTICAL_SIZE/2-3,WHITE,"QUIT",RESET_COLOR);
					printf("\x1b[999;999H");
					std::fflush(stdout);	
					break;
				case HARD:
					printf("\x1b[23;%dH %s %s %s",VERTICAL_SIZE/2-3, WHITE,"EASY",RESET_COLOR);
					printf("\x1b[24;%dH %s %s %s",VERTICAL_SIZE/2-3,WHITE,"MEDIUM",RESET_COLOR);
					printf("\x1b[25;%dH %s %s %s",VERTICAL_SIZE/2-3,GREEN,"HARD",RESET_COLOR);
					printf("\x1b[26;%dH %s %s %s",VERTICAL_SIZE/2-3,WHITE,"QUIT",RESET_COLOR);
					std::fflush(stdout);
					break;
				case QUIT:
					printf("\x1b[23;%dH %s %s %s",VERTICAL_SIZE/2-3, WHITE,"EASY",RESET_COLOR);
					printf("\x1b[24;%dH %s %s %s",VERTICAL_SIZE/2-3,WHITE,"MEDIUM",RESET_COLOR);
					printf("\x1b[25;%dH %s %s %s",VERTICAL_SIZE/2-3,WHITE,"HARD",RESET_COLOR);
					printf("\x1b[26;%dH %s %s %s",VERTICAL_SIZE/2-3,GREEN,"QUIT",RESET_COLOR);
					printf("\x1b[999;999H");
					std::fflush(stdout);
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
    std::fflush(stdout);

	return 0;

}







