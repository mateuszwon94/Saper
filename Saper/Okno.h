#ifndef OKNO_H
#define OKNO_H

#include "Window.h"
#define endl "\n"

class Okno {
	public:
		static void Initialize(Window& console, Window& gameWindow, Window& shadow);
		static void SetBorderColoured(Window& window);
};



#endif
