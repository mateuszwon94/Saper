#include "Wszystko.h"

int main(int argc, char *argv[]) {

	console.SetCursor(false);

	ColorPair tlo = ColorPair(COLOR_WHITE, COLOR_BLUE);
	Window::AssumeDefaultColors(tlo);

	ColorPair okno1 = ColorPair(COLOR_BLACK, COLOR_WHITE);
	ColorPair cien = ColorPair(COLOR_WHITE, COLOR_BLACK);

	Window box = Window(console.lines() - 5, console.columns() - 8, 3, 4);
	Window shadow = Window(console.lines() - 5, console.columns() - 8, 4, 6);

	box.AttrOn(okno1);
	shadow.Background(cien);

	box.SetBorder();

	console << "Saper v0.0.0" << endl;
	console << "__________________________________________________________________________________________________________________________________________________________________________" << endl;


	box.AttrOn(okno1);
	box.Background(okno1);
	box.MoveCursor(5, 20);
	box << "tekst";

	getch();

	return 0;
}

