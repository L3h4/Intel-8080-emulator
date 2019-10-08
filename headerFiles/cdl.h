#include <iostream>
#include <sys/ioctl.h>

void draw_text(int x, int y, std::string text);

void draw_rect(int x, int y, int width, int height, std::string title = "");

void clear();

winsize get_console_size();