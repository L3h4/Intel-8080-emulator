#include<iostream>
#include <cstdint>
#include <unistd.h>
#include"../headerFiles/intel8080.h"

using namespace std;

// 1000000 = 1 sec

//
bool use_clock = false;

I8080 proc;
// 


//
void Basicclock(){
	if (use_clock){
		while(1){
			proc.draw_debug();
			usleep(1100000);
			proc.step();
		}
	}
	else{
		while(1){
			proc.draw_debug();
			getchar();
			proc.step();
		}
	}
}


/*
	точка входа в программу и
	обработчик параметров крмандной строки
*/
int main(int argc, char* argv[])
{
	if (argc>=2){
		for (int i = 1; i < argc; i++)
		{
			if (string(argv[i]) == "--help" || string(argv[i]) == "-h")
			{
				cout << "--help/-h \tShows this message\n";
				cout << "--useclock/-uc \tTels emulator wich is exatly clock use standart or steb by step\n";
			}
			else if (string(argv[i]) == "--useclock" || string(argv[i]) == "-uc")
			{
				try{
					if(string(argv[i+1]) == "1"){
						use_clock = true;
					}
					else{
						use_clock = false;
					}
				}
				catch(exception){
					use_clock = false;
				}
			}
		}
	}
	proc.load_code();
	Basicclock();
	return 0;
}
