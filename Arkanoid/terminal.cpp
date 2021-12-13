#include <cstdio>
#include <string>
#include <iostream>

namespace Terminal
{

    void print(const std::string & s){
        std::cout<<s<<std::endl;
        fflush(stdout);
    }

    void reset(){
        printf("\e[1;1H\e[2J\n");
	    fflush(stdout);
    }
}