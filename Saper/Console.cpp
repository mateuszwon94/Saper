#include <cstdlib>
#include "Console.h"

Console::Console() {
	initscr();
	_columns = COLS;
	_lines = LINES;
	if (has_colors() == FALSE) {
		printf("Your terminal does not support color\n");

		std::exit(1);
	}
	start_color();
}

Console::~Console() {
	while (!_attrybutes.empty())
		AttrOff(_attrybutes.front());
	endwin();
}

void Console::AttrOn(chtype attrybute) {
	_attrybutes.push_back(attrybute);
	attron(attrybute);
	Refresh();
}

void Console::AttrOff(chtype attrybute) {
	_attrybutes.remove(attrybute);
	attroff(attrybute);
	Refresh();
}

void Console::CursSet(bool var) {
	curs_set(var);
}

void Console::AssumeDefaultColors(int text, int background) {
	assume_default_colors(text, background);
	Refresh();
}

void Console::AssumeDefaultColors(ColorPair colorPair) {
	assume_default_colors(colorPair.text(), colorPair.background());
	Refresh();
}

Console& Console::operator<<(char* text) {
	printw(text);
	Refresh();
	return *(this);
}

Console& Console::operator<<(int number) {
	printw("%d",number);
	Refresh();
	return *(this);
}

Console& Console::operator<<(double number) {
	printw("%f", number);
	Refresh();
	return *(this);
}

void Console::Refresh() {
	refresh();
}

void Console::MoveCurosor(int x, int y) {
	move(x, y);
	Refresh();
}

void Console::BorderSet(char ls, char rs, char ts, char bs, char tl, char tr, char bl, char br) {
	border((chtype)ls, (chtype)rs, (chtype)ts, (chtype)bs, (chtype)tl, (chtype)tr, (chtype)bl, (chtype)br);
	Refresh();
}

void Console::BorderSet(chtype ls, chtype rs, chtype ts, chtype bs, chtype tl, chtype tr, chtype bl, chtype br) {
	border(ls, rs, ts, bs, tl, tr, bl, br);
	Refresh();
}

void Console::BorderSet(chtype* ls, chtype* rs, chtype* ts, chtype* bs, chtype* tl, chtype* tr, chtype* bl, chtype* br) {
	border(*ls, *rs, *ts, *bs, *tl, *tr, *bl, *br);
	Refresh();
}