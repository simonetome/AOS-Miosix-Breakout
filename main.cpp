#include <cstdio>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <algorithm>
#include "miosix.h"
#include <thread>
#include "Breakout/settings.h"
#include "Breakout/game.h"

#include "interfaces/gpio.h"

using namespace std;
using namespace miosix;


int main()
{
	int selected = MEDIUM;
	bool selecting = true;
	bool quit = false;
	bool is_changed = true;

	struct termios t;

	std::unique_ptr<miosix::GpioPin> move_down = std::make_unique<miosix::GpioPin>(GPIOD_BASE,6);
	std::unique_ptr<miosix::GpioPin> move_up = std::make_unique<miosix::GpioPin>(GPIOD_BASE,7);
	std::unique_ptr<miosix::GpioPin> select = std::make_unique<miosix::GpioPin>(GPIOD_BASE,4);

	/*reset*/
	printf("\e[1;1H\e[2J\n");
    fflush(stdout);

	tcgetattr(STDIN_FILENO,&t);
	t.c_lflag &= ~ECHO;
	t.c_lflag &= ~(ICANON);
	tcsetattr(STDIN_FILENO,TCSANOW,&t);

	/* Menu */
	do{

		char c;		
		int lastD=0,lastU=0,lastS=0;

		select ->mode(miosix::Mode::INPUT);
		move_down ->mode(miosix::Mode::INPUT);
		move_up ->mode(miosix::Mode::INPUT);

		printf("\e[1;1H\e[2J\n");
    	fflush(stdout);
		
		printf(BREAKOUT,BREAKOUTOFFSET,BREAKOUTOFFSET,BREAKOUTOFFSET,BREAKOUTOFFSET);
		printf("\x1b[21;%dH Choose the option by pressing LEFT or RIGHT, ENTER to select",(VERTICAL_SIZE-60)/2);
		printf("\x1b[23;%dH %s %s %s",VERTICAL_SIZE/2-3, WHITE,"EASY",RESET_COLOR);
		printf("\x1b[24;%dH %s %s %s",VERTICAL_SIZE/2-3,GREEN,"MEDIUM",RESET_COLOR);
		printf("\x1b[25;%dH %s %s %s",VERTICAL_SIZE/2-3,WHITE,"HARD",RESET_COLOR);
		printf("\x1b[26;%dH %s %s %s",VERTICAL_SIZE/2-3,WHITE,"QUIT",RESET_COLOR);
		printf("\x1b[999;999H");
		fflush(stdout);


		do{
							
			if(BUTTON)
			{
				//button input
				is_changed=false;
				int valU=move_up->value();
				int valD=move_down->value();
				int valS=select->value();

				if(lastD==1 && valD==0)
				{
					selected = min(selected+1,QUIT);
					is_changed=true;

				}else if(lastU==1 && valU==0)
				{
					selected = max(selected-1,EASY);
					is_changed=true;

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
			}
			else
			{
				//keyboard input
				is_changed = true;
				c=getchar();
		
				fflush(stdout);

				if(c=='d')
				{
					selected = min(selected+1,QUIT);
					is_changed = true;

				}else if(c=='a')
				{
					selected = max(selected-1,EASY);
					is_changed = true;

				}
				else if(c=='e')
				{
					selecting = false;
					if(selected == QUIT)
					{
						quit = true;
						is_changed = true;
					}
				}

			}


			if(is_changed)
				switch (selected)
				{
				case EASY:
					printf("\x1b[23;%dH %s %s %s",VERTICAL_SIZE/2-3, GREEN,"EASY",RESET_COLOR);
					printf("\x1b[24;%dH %s %s %s",VERTICAL_SIZE/2-3,WHITE,"MEDIUM",RESET_COLOR);
					printf("\x1b[25;%dH %s %s %s",VERTICAL_SIZE/2-3,WHITE,"HARD",RESET_COLOR);
					printf("\x1b[26;%dH %s %s %s",VERTICAL_SIZE/2-3,WHITE,"QUIT",RESET_COLOR);
					printf("\x1b[999;999H");
					fflush(stdout);
					break;
				case MEDIUM:
					printf("\x1b[23;%dH %s %s %s",VERTICAL_SIZE/2-3, WHITE,"EASY",RESET_COLOR);
					printf("\x1b[24;%dH %s %s %s",VERTICAL_SIZE/2-3,GREEN,"MEDIUM",RESET_COLOR);
					printf("\x1b[25;%dH %s %s %s",VERTICAL_SIZE/2-3,WHITE,"HARD",RESET_COLOR);
					printf("\x1b[26;%dH %s %s %s",VERTICAL_SIZE/2-3,WHITE,"QUIT",RESET_COLOR);
					printf("\x1b[999;999H");
					fflush(stdout);	
					break;
				case HARD:
					printf("\x1b[23;%dH %s %s %s",VERTICAL_SIZE/2-3, WHITE,"EASY",RESET_COLOR);
					printf("\x1b[24;%dH %s %s %s",VERTICAL_SIZE/2-3,WHITE,"MEDIUM",RESET_COLOR);
					printf("\x1b[25;%dH %s %s %s",VERTICAL_SIZE/2-3,GREEN,"HARD",RESET_COLOR);
					printf("\x1b[26;%dH %s %s %s",VERTICAL_SIZE/2-3,WHITE,"QUIT",RESET_COLOR);
					printf("\x1b[999;999H");
					fflush(stdout);
					break;
				case QUIT:
					printf("\x1b[23;%dH %s %s %s",VERTICAL_SIZE/2-3, WHITE,"EASY",RESET_COLOR);
					printf("\x1b[24;%dH %s %s %s",VERTICAL_SIZE/2-3,WHITE,"MEDIUM",RESET_COLOR);
					printf("\x1b[25;%dH %s %s %s",VERTICAL_SIZE/2-3,WHITE,"HARD",RESET_COLOR);
					printf("\x1b[26;%dH %s %s %s",VERTICAL_SIZE/2-3,GREEN,"QUIT",RESET_COLOR);
					printf("\x1b[999;999H");
					fflush(stdout);
					break;
				default:
					break;
				}
			is_changed = false;

		}while(selecting);

		if(!quit){
			Game game(selected);
			game.startGame();
			/* game has ended */
			selecting = true;
			quit = false;
			if(BUTTON)
				std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}

		selected=MEDIUM;
	}while(!quit);

	printf("\e[1;1H\e[2J\n");
    fflush(stdout);

	tcgetattr(STDIN_FILENO,&t);
	t.c_lflag |= ECHO;
	t.c_lflag |= (ICANON);
	tcsetattr(STDIN_FILENO,TCSANOW,&t);
	
	return 0;

} // end main







