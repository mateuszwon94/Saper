#include "Color.h"

#ifndef TEXT_COLOR
#define TEXT_COLOR
ColorPair textColor = ColorPair(COLOR_WHITE, COLOR_BLUE);
ColorPair specialTextColor = ColorPair(COLOR_YELLOW, COLOR_BLUE);
#endif

short ColorPair::count = 0;

ColorPair::ColorPair(short text, short background) {
	++count;
	_background = background;
	_text = text;
	_number = count;
	init_pair(count, text, background);
}

ColorPair::operator chtype() {
	return COLOR_PAIR(_number);
}