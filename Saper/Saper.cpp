#pragma comment(lib , "pdcurses.lib")
#include <curses.h>

int main(int argc, char *argv[]) {
	initscr();			/* Start curses mode 		*/
	if (has_colors() == FALSE) {
		endwin();
		printf("Your terminal does not support color\n");
		return 1;
	}
	start_color();			/* Start color 			*/
	assume_default_colors(COLOR_WHITE, COLOR_BLUE);
	printw("Jakis napis");
	refresh();
	getch();
	endwin();

	return 0;
}