#include "Window.h"

Window console = Window();

Window::Window(int lines, int columns, int x, int y, WINDOW* window) {
	if (_window == stdscr) {
		initscr();

		_x = 0;
		_y = 0;
		_lines = LINES;
		_columns = COLS;
		_window = stdscr;

	//	Resize(170,50);

		if (has_colors() == FALSE) {
			printf("Your terminal does not support color\n");

			std::exit(1);
		}
		start_color();
		keypad(stdscr, TRUE);
		raw();
	} else {
		_x = x;
		_y = y;
		_lines = lines;
		_columns = columns;
		if (window == NULL)
			_window = newwin(lines, columns, x, y);
		else _window = window;
	}
}

Window::~Window() {
	while (!_attrybutes.empty())
		AttrOff(_attrybutes.front());
	if (_window == stdscr) endwin();
	else delwin(_window);
}

void Window::AttrOn(chtype attrybute) {
	_attrybutes.push_back(attrybute);
	wattron(_window, attrybute);
	Refresh();
}

void Window::AttrOff(chtype attrybute) {
	_attrybutes.remove(attrybute);
	wattroff(_window, attrybute);
	Refresh();
}

void Window::Refresh() {
	wrefresh(_window);
	refresh();
}

Window::operator WINDOW*() {
	return _window;
}

void Window::Background(chtype attrybute) {
	wbkgd(_window, attrybute);
	Refresh();
}

Window& Window::operator<<(char* text) {
	wprintw(_window, text);
	Refresh();
	return *(this);
}

Window& Window::operator<<(char sign) {
	wprintw(_window, "%c", sign);
	Refresh();
	return *(this);
}

Window& Window::operator<<(int number) {
	wprintw(_window, "%d", number);
	Refresh();
	return *(this);
}

Window& Window::operator<<(double number) {
	wprintw(_window,"%f", number);
	Refresh();
	return *(this);
}

void Window::operator>>(char* text) {
	wgetstr(_window,text);
}

void Window::operator>>(char& sign) {
	sign = wgetch(_window);
}


void Window::MoveCursor(int x, int y) {
	wmove(_window, x, y);
	Refresh();
}

void Window::MoveWindow(int x, int y) {
	mvwin(_window, x, y);
	Refresh();
}

void Window::SetBorder(char ls, char rs, char ts, char bs, char tl, char tr, char bl, char br) {
	wborder(_window, (chtype)ls, (chtype)rs, (chtype)ts, (chtype)bs, (chtype)tl, (chtype)tr, (chtype)bl, (chtype)br);
	Refresh();
}

void Window::SetBorder(chtype ls, chtype rs, chtype ts, chtype bs, chtype tl, chtype tr, chtype bl, chtype br) {
	wborder(_window, ls, rs, ts, bs, tl, tr, bl, br);
	Refresh();
}

void Window::SetBorder(chtype* ls, chtype* rs, chtype* ts, chtype* bs, chtype* tl, chtype* tr, chtype* bl, chtype* br) {
	wborder(_window, *ls, *rs, *ts, *bs, *tl, *tr, *bl, *br);
	Refresh();
}

void Window::SetCursor(bool var) {
	curs_set(var);
}

void Window::AssumeDefaultColors(int text, int background) {
	assume_default_colors(text, background);
	refresh();
}

void Window::AssumeDefaultColors(ColorPair colorPair) {
	assume_default_colors(colorPair.text(), colorPair.background());
	refresh();
}

void Window::SetEcho(bool isActive) {
	if (isActive) echo();
	else noecho();
}

void Window::Resize(int lines, int columns) {
	resize_window(_window, lines, columns);
}