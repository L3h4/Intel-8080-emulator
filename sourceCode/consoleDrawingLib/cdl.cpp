#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h> 



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
		draw_text(x+1,y,title);
	}
}

void clear(){
    system("clear");
}

winsize get_console_size(){
	struct winsize size;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	return size;
}
