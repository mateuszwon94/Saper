#include "Window.h"
#include "Timer.h"
#include <stdexcept>

using namespace std;

int Window::count = 0;

Window& console = Window();
Window& gameWindow = Window(console.lines() - 5, console.columns() - 8, 3, 4);
Window& shadow = Window(console.lines() - 5, console.columns() - 8, 4, 6);

Window::Window(int lines, int columns, int posLine, int posColumn, WINDOW* window) {
	if (!count) {
		initscr();
		raw();
		window = stdscr;
		lines = LINES;
		columns = COLS;
	}
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
	++count;
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
	Timer::getMutex()->lock();
	wprintw(_window, text);
	Refresh();
	Timer::getMutex()->unlock();
	return *(this);
}

Window& Window::operator<<(string text) {
	Timer::getMutex()->lock();
	wprintw(_window, text.c_str());
	Refresh();
	Timer::getMutex()->unlock();
	return *(this);
}

Window& Window::operator<<(char sign) {
	Timer::getMutex()->lock();
	wprintw(_window, "%c", sign);
	Refresh();
	Timer::getMutex()->unlock();
	return *(this);
}

Window& Window::operator<<(wchar_t sign) {
	Timer::getMutex()->lock();
	wprintw(_window, "%c", sign);
	Refresh();
	Timer::getMutex()->unlock();
	return *(this);
}

Window& Window::operator<<(const unsigned char sign) {
	Timer::getMutex()->lock();
	wprintw(_window, "%c", sign);
	Refresh();
	Timer::getMutex()->unlock();
	return *(this);
}

Window& Window::operator<<(chtype sign) {
	Timer::getMutex()->lock();
	wprintw(_window, "%c", sign);
	Refresh();
	Timer::getMutex()->unlock();
	return *(this);
}

Window & Window::operator<<(chtype* sign) {
	Timer::getMutex()->lock();
	wprintw(_window, "%c", *sign);
	Refresh();
	Timer::getMutex()->unlock();
	return *(this);
}

Window& Window::operator<<(int number) {
	Timer::getMutex()->lock();
	wprintw(_window, "%d", number);
	Refresh();
	Timer::getMutex()->unlock();
	return *(this);
}

Window& Window::operator<<(unsigned int number) {
	Timer::getMutex()->lock();
	wprintw(_window, "%d", number);
	Refresh();
	Timer::getMutex()->unlock();
	return *(this);
}

Window& Window::operator<<(double number) {
	Timer::getMutex()->lock();
	wprintw(_window,"%f", number);
	Refresh();
	Timer::getMutex()->unlock();
	return *(this);
}

Window& Window::operator<<(Menu& menu) {
	Timer::getMutex()->lock();
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
	Timer::getMutex()->unlock();
	return *(this);
}

Window& Window::operator<<(MenuEntry& entry) {

#ifndef TEXT_COLOR
#define TEXT_COLOR
	static ColorPair textColor = ColorPair(COLOR_WHITE, COLOR_BLUE);
	static ColorPair specialTextColor = ColorPair(COLOR_YELLOW, COLOR_BLUE);
#endif
	Timer::getMutex()->lock();
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
	Timer::getMutex()->unlock();
	return *(this);
}

void Window::MoveCursor(int line, int column) {
	wmove(_window, line, column);
	Refresh();
}

array<int, 2>& Window::GetCursorPos() {
	int x, y;
	getyx(_window, y, x);
	static array<int, 2> pos = { x,y };
	return pos;
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