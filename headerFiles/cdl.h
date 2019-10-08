#include <iostream>

void draw_text(int x, int y, std::string text);

void draw_rect(int x, int y, int width, int height, std::string title = "");

void clear();

template< typename T >
std::string to_hex( T i );