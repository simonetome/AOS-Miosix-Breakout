

#include <cstdio>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include "miosix.h"
#include <thread>

#include "Arkanoid/game.h"
#include "Arkanoid/terminal.h"

using namespace std;
using namespace miosix;



int main()
{	
	Terminal::reset();

	Terminal::print("Press any key to start the game.\n");

	getchar();

	Terminal::reset();
	
	Game game();

	return 0;

}







