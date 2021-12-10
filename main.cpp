

#include <cstdio>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include "miosix.h"
#include <thread>

#include "canvas/canvas.h"
#include "game/game.h"

using namespace std;
using namespace miosix;



int main()
{	
	Canvas canvas;
	canvas.resetCanvas();

	printf("press any key to start the game\n");
	fflush(stdout);
	getchar();
	canvas.resetCanvas();
	Game game;
	game.newGame(canvas);
	return 0;

}







