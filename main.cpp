

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

	Game game;

	/* Menu */
	printf("Press any key to begin the game");
	getchar();
	game.startGame();


	return 0;

}







