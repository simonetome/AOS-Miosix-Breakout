

#include <cstdio>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include "miosix.h"
#include <thread>

using namespace std;
using namespace miosix;

//thread for input
void thread_function()
{
    char c,lastC;
    struct termios t;
    int x=15;
    	printf("\x1b[%d;%dH###",15,x-1);
	fflush(stdout);
	printf("\x1b[999;999H");     //cursor to the last cell of the terminal
    	fflush(stdout);
    for(;;)
    {
	//set option to take in input only one character
    	tcgetattr(STDIN_FILENO,&t);
        t.c_lflag &= ~ECHO;
        t.c_lflag &= ~(ICANON);
        tcsetattr(STDIN_FILENO,TCSANOW,&t);
        
        c=getchar();

        tcgetattr(STDIN_FILENO,&t);
        t.c_lflag |= ECHO;
        t.c_lflag |= (ICANON);
        tcsetattr(STDIN_FILENO,TCSANOW,&t);
        //move right
        if(c=='d')
    	{
    		if(lastC=='d')
    		{
    			x++;
    			printf("\x1b[%d;%dH ###",15,x-1);}
    		else{
    			printf("\x1b[%d;%dH ###",15,x-2);
    			x--;
    		}
		fflush(stdout);
		printf("\x1b[999;999H");
	    	fflush(stdout);
	    	lastC=c;
    		
    	}else if(c=='a') //move left
    	{
    		if(lastC=='a')
    		{
    			x--;
    			printf("\x1b[%d;%dH### ",15,x-2);}
		else{	

    			printf("\x1b[%d;%dH### ",15,x-1);
    			x++;
    		}
		fflush(stdout);
		printf("\x1b[999;999H");
	    	fflush(stdout);
	    	lastC=c;
    		
    	}

    	c=' ';
    }
}


int main()
{	
	int lastX=3;
	char grid[15][31];
	bool avanti=true;

	printf("\e[1;1H\e[2J\n");//clear screen
	for(int i=0;i<15;i++){
		for(int j=0;j<30;j++)
		{
			
			if(j==0 || j==29)
				grid[i][j]='|';
				else
			if(i<3)
				grid[i][j]='#';
			else
				grid[i][j]=' ';
			if(i==14)
				grid[i][j]='_';
		}

		grid[i][30]='\n';

	}
	grid[14][0]='.';
	grid[14][29]='.';
	
	
	//wait to start the game
		struct termios t;
		printf("press any key to start the game");
		tcgetattr(STDIN_FILENO,&t);
		t.c_lflag &= ~(ICANON);
		tcsetattr(STDIN_FILENO,TCSANOW,&t);
		
		getchar();

		tcgetattr(STDIN_FILENO,&t);
		t.c_lflag |= (ICANON);
		tcsetattr(STDIN_FILENO,TCSANOW,&t);      
        
        printf("\e[1;1H\e[2J\n");
	printf("%s\n",grid);
	std::thread th(&thread_function);
	
	for(;;){
	
	if(lastX==20)
	{
		avanti=false;
	}
	if(lastX==3)
		avanti=true;
	if(avanti)
	{	
		printf("\x1b[%d;%dH",5,lastX);//print alle coordinate (5,lastX)
		printf(" ○");
    		fflush(stdout);
		lastX++;
	}else
	{
		printf("\x1b[%d;%dH",5,lastX);
		printf("○ ");
    		fflush(stdout);
		lastX--;
	}
		printf("\x1b[999;999H");
    		fflush(stdout);

		Thread::sleep(100);
		
	}

}







