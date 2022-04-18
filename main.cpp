

#include <cstdio>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include "miosix.h"
#include <thread>

#include "Arkanoid/game.h"


using namespace std;
using namespace miosix;




int main()
{

	/*reset*/
	std::printf("\e[1;1H\e[2J\n");
    fflush(stdout);

	struct termios t;
	
	/* Menu */
	do{

		char c;		
		bool startGame =true;

		printf("\e[1;1H\e[2J\n");
    	fflush(stdout);

		printf("\x1b[11;1H Choose the option by pressing A or D, any other key to select");
		printf("\x1b[13;25H\u001b[32m START	\033[0mQUIT");
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
				startGame=false;
				printf("\x1b[13;25H\033[0m START	\u001b[32mQUIT \033[0m");
				printf("\x1b[999;999H");
				fflush(stdout);	

			}else if(c=='a')
			{
				startGame=true;
				printf("\x1b[13;25H\u001b[32m START	\033[0mQUIT");
				printf("\x1b[999;999H");
				fflush(stdout);	

			}else break;
		}while(true);

		if(!startGame)break;

		Game game;
		game.startGame();

	}while(true);

	std::printf("\e[1;1H\e[2J\n");
    fflush(stdout);

	return 0;

}







