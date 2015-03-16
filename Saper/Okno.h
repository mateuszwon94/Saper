#ifndef OKNO_H
#define OKNO_H

#include "Window.h"
#define endl "\n"

class Okno {
	public:
		static void Initialize();
		static void SetBorderColoured(Window& window);
};

//standard output:
extern Window console;

//used Windows:
extern Window gameWindow;
extern Window shadow;

#endif
