#include "Window.h"

using namespace std;

Window* Window::gw = nullptr;

Window::Window(int lines, int columns, int posLine, int posColumn, WINDOW* window) {
	_x = posLine;
	_y = posColumn;
	_lines = lines;
	_columns = columns;
	_window = window;
	_window->_flags;
	if (_window == stdscr) {

		Resize(50, 170);
		start_color();
		keypad(stdscr, TRUE);
		raw();
		refresh();
		ColorPair tlo(COLOR_WHITE, COLOR_BLUE);
		refresh();
		Window::AssumeDefaultColors(tlo);
		
		//refresh();
		
		Window::SetEcho(false);
	}
	else if (window == NULL)
		_window = newwin(lines, columns, posLine, posColumn);
	else _window = window;
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

void Window::Background(chtype attrybute) {
	wbkgd(_window, attrybute);
	Refresh();
}

Window& Window::operator<<(char* text) {
	wprintw(_window, text);
	Refresh();
	return *(this);
}

Window& Window::operator<<(string text) {
	wprintw(_window, text.c_str());
	Refresh();
	return *(this);
}

Window& Window::operator<<(char sign) {
	wprintw(_window, "%c", sign);
	Refresh();
	return *(this);
}

Window& Window::operator<<(wchar_t sign) {
	wprintw(_window, "%c", sign);
	Refresh();
	return *(this);
}

Window& Window::operator<<(const unsigned char sign) {
	wprintw(_window, "%c", sign);
	Refresh();
	return *(this);
}

Window& Window::operator<<(chtype sign) {
	wprintw(_window, "%c", sign);
	Refresh();
	return *(this);
}

Window & Window::operator<<(chtype* sign) {
	wprintw(_window, "%c", *sign);
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

Window& Window::operator<<(Menu& menu) {

	unsigned int line = menu.PosLine();
	unsigned int column = menu.PosColumn();
	int i = 1;
	for (MenuEntry& entry : menu) {
		MoveCursor(line, column);
		(*this) << i <<". " << entry;
		line += 2;
		i++;
	}

	Refresh();
	return *(this);
}

Window& Window::operator<<(MenuEntry& entry) {

#ifndef TEXT_COLOR
#define TEXT_COLOR
	static ColorPair textColor = ColorPair(COLOR_WHITE, COLOR_BLUE);
	static ColorPair specialTextColor = ColorPair(COLOR_YELLOW, COLOR_BLUE);
#endif

	AttrOn(A_BOLD);
	if (entry) {
		for (int i = 0; i < entry.Name().length(); ++i) {
			if (i == entry.Special()) {
				AttrOn(specialTextColor);
				*(this) << entry.Name()[i];
				AttrOff(specialTextColor);
			} else {
				AttrOn(textColor);
				*(this) << entry.Name()[i];
				AttrOff(textColor);
			}
		}
	} else
		*(this) << entry.Name();
	AttrOff(A_BOLD);

	return *(this);
}

void Window::MoveCursor(int line, int column) {
	wmove(_window, line, column);
	Refresh();
}

void Window::MoveWindow(int line, int column) {
	mvwin(_window, line, column);
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
	if (_window == stdscr)
		resize_term(lines, columns);
	else if (_window != NULL)
		wresize(_window, lines, columns);
	_lines = lines;
	_columns = columns;
}
WINDOW * Window::getWin()
{
	return _window;
}