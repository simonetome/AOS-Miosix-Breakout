

#include <cstdio>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include "miosix.h"
#include <thread>

#include "Arkanoid/game.h"
#include "Arkanoid/terminal.h"
#include "Arkanoid/settings.h"

using namespace std;
using namespace miosix;

void thread_function(){
	int x = 0;
	int y = 0;
	int oldx = 99;
	int oldy = 99;
	int direction = 1;

	for(;;){
		
		Terminal::printAndDelXY(oldx,oldy,x,y,BALL);

		if(y > 40 || y < 0){ direction *= -1;}

		oldx = x;
		oldy = y;
		x++;
		y += direction;

		std::this_thread::sleep_for(std::chrono::milliseconds(40));

	}
}


int main()
{

	Terminal::reset();

	Terminal::print("Press any key to start the game.\n");

	getchar();

	Terminal::reset();

	Terminal::hideCursor();
	
	//std::thread th(&thread_function);

	Game game;
	game.startGame();

	for(;;){}
	//th.join();



	return 0;

}







