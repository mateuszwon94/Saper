#include "Wszystko.h"

int main(int argc, char *argv[]) {

	Okno::Initialize();
	
	gameWindow.MoveCursor(5, 20);
	gameWindow << "tekst";

	getch();

	return 0;
}

