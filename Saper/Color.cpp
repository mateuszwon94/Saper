#include "Color.h"

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