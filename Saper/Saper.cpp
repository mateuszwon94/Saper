#pragma comment(lib , "pdcurses.lib")
#include <curses.h>

int main(int argc, char *argv[]) {
	initscr();			/* Start curses mode 		*/
	if (has_colors() == FALSE) {
		endwin();
		printf("Your terminal does not support color\n");
		return 1;
	}

	curs_set(FALSE);

	start_color();			/* Start color 			*/
	assume_default_colors(COLOR_WHITE, COLOR_BLUE);

	init_pair(1, COLOR_BLACK, COLOR_WHITE);
	init_pair(2, COLOR_WHITE, COLOR_BLACK);

	WINDOW* box = newwin(LINES - 5, COLS - 8, 3, 4);
	WINDOW* shadow = newwin(1, 1, 0, 0);

	wattron(box, COLOR_PAIR(1));
	//wattron(shadow, COLOR_PAIR(2));
	wbkgd(shadow, COLOR_PAIR(2));
	wrefresh(shadow);
	
	printw("Saper v0.0.0\n__________________________________________________________________________________________________________________________________________________________________________");
	refresh();

	wattron(box, COLOR_PAIR(1));
	wbkgd(box, COLOR_PAIR(1));
	mvwprintw(box, 5, 20, "tekst");
	wrefresh(box);
	
	wattroff(box, COLOR_PAIR(1));
	//wattroff(shadow, COLOR_PAIR(2));

	delwin(box);
	delwin(shadow);

	getch();
	endwin();

	//proba dodania jakiejs linijkii :P

	return 0;
}