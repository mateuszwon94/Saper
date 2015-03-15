#include "Window.h"
#include "Console.h"

Window::Window(int lines, int columns, int x, int y) {
	_x = x;
	_y = y;
	_lines = lines;
	_columns = columns;
	_window = newwin(lines, columns, x, y);
}

Window::~Window() {
	while (!_attrybutes.empty())
		AttrOff(_attrybutes.front());
	delwin(_window);
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
	console.Refresh();
}

Window::operator WINDOW*() {
	return _window;
}

void Window::Background(chtype attrybute) {
	wbkgd(_window, attrybute);
	Refresh();
}

Window& Window::operator<<(char* text) {
	wprintw(_window,text);
	Refresh();
	return *(this);
}

void Window::MoveCursor(int x, int y) {
	wmove(_window, x, y);
	Refresh();
}

void Window::MoveWindow(int x, int y) {
	mvwin(_window, x, y);
	Refresh();
}

Window& Window::CreateSubWindow(int lines, int columns, int x, int y, bool relativeToOrigin) {
	static Window subWin;

	if (relativeToOrigin) 
		subWin = Window(lines, columns, _x + x, _y + y);
	else
		subWin = Window(lines, columns, x, y);

	_subWindow.push_back(subWin);

	subWin.Refresh();
	Refresh();

	return subWin;
}

void Window::BorderSet(char ls, char rs, char ts, char bs, char tl, char tr, char bl, char br) {
	wborder(_window, (chtype)ls, (chtype)rs, (chtype)ts, (chtype)bs, (chtype)tl, (chtype)tr, (chtype)bl, (chtype)br);
	Refresh();
}

void Window::BorderSet(chtype ls, chtype rs, chtype ts, chtype bs, chtype tl, chtype tr, chtype bl, chtype br) {
	wborder(_window, ls, rs, ts, bs, tl, tr, bl, br);
	Refresh();
}

void Window::BorderSet(chtype* ls, chtype* rs, chtype* ts, chtype* bs, chtype* tl, chtype* tr, chtype* bl, chtype* br) {
	wborder(_window, *ls, *rs, *ts, *bs, *tl, *tr, *bl, *br);
	Refresh();
}