#include<iostream>
#include <cstdint>
#include <unistd.h>
#include <stdio.h> 
#include"../headerFiles/intel8080.h"

using namespace std;

// 1000000 = 1 sec

//
bool use_clock = false;

I8080 proc(true);
// 
string GetCurrentWorkingDir() {
  char buff[FILENAME_MAX];
  getcwd( buff, FILENAME_MAX );
  string current_working_dir(buff);
  return current_working_dir;
}

//
void Basicclock(){
	if (use_clock){
		while(1){
			usleep(1100000);
			proc.step();
		}
	}
	else{
		while(1){
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
	//cout<<GetCurrentWorkingDir()<<endl;
	//return 0;

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
			else if (string(argv[i]) == "--loadRom" || string(argv[i]) == "-l"){
				if(string(argv[i+1]) != ""){
					proc.load_code(GetCurrentWorkingDir()+"/"+string(argv[i+1]));
				}
			}
		}
	}

	Basicclock();
	return 0;
}
