#include <iostream>
#include <stdio.h>
#include <iomanip>

using namespace std;


void draw_text(int x, int y, string text){
    printf("\033[%d;%dH",y,x);
    cout<<text;
}

void draw_rect(int x, int y, int width, int height, string title = ""){
	for (int i = x; i < x+width; i++){
		if (i == x){
			draw_text(i,y,"╔");
		}
		else if(i == x+width-1){
			draw_text(i,y,"╗");
		}
		else{
			draw_text(i,y,"═");
		}
	}
	for (int i = x; i < x+width; i++){
		if (i == x){
			draw_text(i,y+height-1,"╚");
		}
		else if(i == x+width-1){
			draw_text(i,y+height-1,"╝");
		}
		else{
			draw_text(i,y+height-1,"═");
		}
	}
	for(int i = y+1; i < y+height-1; i++){
		draw_text(x, i, "║");
	}
	for(int i = y+1; i < y+height-1; i++){
		draw_text(x+width-1, i, "║");
	}

	if(title != ""){
		draw_text(x,y,title);
	}
}

void clear(){
    system("clear");
}

template< typename T >
std::string to_hex( T i ){
  std::stringstream stream;
  stream << "0x" << std::setfill ('0') << std::setw(sizeof(T)*2) << std::hex << i;
  return stream.str();
}