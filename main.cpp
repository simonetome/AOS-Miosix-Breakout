

#include <cstdio>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include "miosix.h"

using namespace std;
using namespace miosix;


int main()
{	
	int lastX=1;
	char grid[15][31];
	bool avanti=true;

	for(int i=0;i<15;i++){
		for(int j=0;j<30;j++)
		{
			
			if(j==0 || j==29)
				grid[i][j]='#';
				else
			grid[i][j]=' ';
			if(i==14)
				grid[i][j]='#';
		}

		grid[i][30]='\n';

	}
	for(;;){
	printf("\e[1;1H\e[2J\n");
	
	if(lastX==29)
	{
		avanti=false;
	}
	if(lastX==1)
		avanti=true;
	if(avanti)
	{	
		grid[0][lastX-1]=' ';
		grid[0][lastX]='.';
		grid[0][0]='#';
		lastX++;
	}else
	{
		grid[0][lastX+1]=' ';
		grid[0][lastX]='.';
		grid[0][29]='#';
		grid[0][30]='\n';
		lastX--;
	}
	
		printf("%s\n",grid);
		
		//fflush(stdout);
		Thread::sleep(50);
		
	}
}







