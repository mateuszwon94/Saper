#include "Window.h"
/*Window::Window() {
	Window::Window();
}*/

Window::Window(int lines, int columns, int posLine, int posColumn, WINDOW* window) {
	_x = posLine;
	_y = posColumn;
	_lines = lines;
	_columns = columns;
	_window = window;
	_window->_flags;
	if (_window == stdscr) {

		Resize(75, 175);
		start_color();
		keypad(stdscr, TRUE);
		raw();
		refresh();
		ColorPair tlo(COLOR_WHITE, COLOR_BLUE);
		refresh();
		Window::AssumeDefaultColors(tlo);
		
		//refresh();
		
		//Window::SetEcho(false);
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

void Window::Refresh() {
	wrefresh(_window);
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

Window& Window::operator<<(wchar_t sign) {
	wprintw(_window, "%c", sign);
	Refresh();
	return *(this);
}

Window& Window::operator<<(unsigned char sign) {
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

/*Window& Window::operator<<(Menu& menu) {
	for (MenuEntry entry : menu()) {
		MoveCursor(entry.line, entry.column);
		(*this) << entry;
	}
	Refresh();
	return *(this);
}

Window& Window::operator<<(MenuEntry& entry) {

#ifndef TEXT_COLOR
#define TEXT_COLOR
	ColorPair textColor = ColorPair(COLOR_WHITE, COLOR_BLUE);
	ColorPair specialTextColor = ColorPair(COLOR_YELLOW, COLOR_BLUE);
#endif

	AttrOn(textColor);
	for (register int i = 0; i < entry.name.length(); ++i) {
		if (i == entry.special) {
			AttrOn(specialTextColor);
			AttrOn(A_BOLD);
			*(this) << entry.name[0];
			AttrOff(A_BOLD);
			AttrOff(specialTextColor);
		}
		else *(this) << entry.name[0];
	}
	AttrOff(textColor);

	return *(this);
}*/

void Window::operator>>(char* text) {
	wgetstr(_window,text);
}

void Window::operator>>(char& sign) {
	sign = wgetch(_window);
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