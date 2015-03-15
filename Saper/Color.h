#ifndef COLOR_H
#define COLOR_H

#include "ncurses.h"

class ColorPair {
	public:
		ColorPair(short text, short background);

		operator chtype();

		short text() { return _text; }
		short background() { return _background; }
	private:
		static short count;
		short _text;
		short _background;
		short _number;
};

#endif
