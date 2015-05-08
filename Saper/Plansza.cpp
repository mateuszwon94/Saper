﻿#include "Plansza.h"
#include <ctime>
#include <cstdlib>
#include "Menu.h"
#include "Color.h"

using namespace std;

int Plansza::wid = 0;
int Plansza::heig = 0;
int Plansza::n_bombs = 0;
Plansza* Plansza::current = nullptr;
int Plansza::first_clik = 0;

Plansza::Plansza(int a, int b, int bomb, Window& win) : gameWindow(win), highlight_x(0), highlight_y(0), esc(false) {
	width = wid = a;
	height = heig = b;
	n_bomb = n_bombs = bomb;
	licznik = width*height - n_bomb;
	Tboard.resize(height);
	Dboard.resize(height);
	for (int it = 0; it < height; it++) {
		Tboard[it].resize(width);
		Dboard[it].resize(width);
		for (int it2 = 0; it2 < width; it2++) {
			Dboard[it][it2] = mediumDestinyDots;
			Tboard[it][it2] = lowDestinyDots;
		}
	}
	if (current != nullptr)
		delete current;
	current = this;
}

void Plansza::setCLB(std::array<int, 3> values) {
	wid = values[0];
	heig = values[1];
	n_bombs = values[2];
}

Plansza::~Plansza() {
	first_clik = 0;
	undraw();
}

void Plansza::run() {
	Window::SetCursor(false);
	highlight_x = 0;
	highlight_y = 0;
	esc = false;
	_loose = false;
	draw();
	choose();
	Window::SetCursor(true);
}

void Plansza::draw_bombs() {
	bool is_there = false;
	srand(time(NULL));
	for (int i = 0; i < n_bomb; i++) {
		int x = rand() % height;
		int y = rand() % width;
		if (x == first_x && y == first_y)
			is_there = true;
		else if (Tboard[x][y] == bomb)
			is_there = true;
		if (!is_there) {
			Tboard[x][y] = bomb;
			int x_up = x - 1;
			int x_down = x + 1;
			int y_right = y + 1;
			int y_left = y - 1;
			if (x_up >= 0 && Tboard[x_up][y] != bomb) {
				Tboard[x_up][y] = '1';
			}
			if (x_up >= 0 && y_left >= 0 && Tboard[x_up][y_left] != bomb) {
				Tboard[x_up][y_left] = '1';
			}
			if (x_up >= 0 && y_right < width && Tboard[x_up][y_right] != bomb) {
				Tboard[x_up][y_right] = '1';
			}
			if (x_down <height && y_right < width && Tboard[x_down][y_right] != bomb) {
				Tboard[x_down][y_right] = '1';
			}
			if (x_down <height && y_left >= 0 && Tboard[x_down][y_left] != bomb) {
				Tboard[x_down][y_left] = '1';
			}
			if (x_down <height && Tboard[x_down][y] != bomb) {
				Tboard[x_down][y] = '1';
			}
			if (y_left >= 0 && Tboard[x][y_left] != bomb) {
				Tboard[x][y_left] = '1';
			}
			if (y_right < width && Tboard[x][y_right] != bomb) {
				Tboard[x][y_right] = '1';
			}
		} else {
			i--;
			is_there = false;
		}
	}
	znaczniki();
}

void Plansza::znaczniki() {
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			int n_mins = 0;
			if (Tboard[i][j] == '1') {
				//# Sprawdzamy 3 pola nad komorka i,x
				int zi = i - 1; // pole wyzej
				if (zi >= 0) {
					if (Tboard[zi][j] == bomb) {
						n_mins++;
					}
					int zx = j + 1; // pole wyzej i jedna komorka w prawo
					if (zx < width) {
						if (Tboard[zi][zx] == bomb)
							n_mins++;
					}
					zx = j - 1; // pole wyzej i jedna komorka w lewo
					if (zx >= 0) {
						if (Tboard[zi][zx] == bomb)
							n_mins++;
					}
				}
				//# Sprawdzamy pola po prawej i lewej nad komorka i,x
				int zx = j + 1; // jedna komorka w prawo
				if (zx < width) {
					if (Tboard[i][zx] == bomb)
						n_mins++;
					zx = j - 1; // jedna komorka w lewo
					if (zx >= 0) {
						if (Tboard[i][zx] == bomb) {
							n_mins++;
						}
					}
					//# Sprawdzamy 3 pola pod komorka i,x
					int zi = i + 1; // pole wyzej
					if (zi < height) {
						if (Tboard[zi][j] == bomb)
							n_mins++;
						zx = j + 1; // pole nizej i jedna komorka w prawo
						if (zx < width) {
							if (Tboard[zi][zx] == bomb) {
								n_mins++;
							}
						}
						zx = j - 1; // pole nizej i jedna komorka w lewo
						if (zx >= 0) {
							if (Tboard[zi][zx] == bomb)
								n_mins++;
						}
					}
					if (n_mins > 1)
						Tboard[i][j] = 48 + n_mins;
				}
			}
		}
	}
}


void Plansza::draw() {
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			moveCoursor(i + 2, j + 2);
			if (Dboard[i][j] == bomb) {
				static ColorPair color = ColorPair(COLOR_RED, COLOR_WHITE);
				gameWindow.AttrOn(color);
				if (i == highlight_x && j == highlight_y) {
					gameWindow.AttrOn(A_REVERSE);
					drawSign(Dboard[i][j]);
					gameWindow.AttrOff(A_REVERSE);
				} else
					drawSign(Dboard[i][j]);
				gameWindow.AttrOff(color);
			} else {
				if (i == highlight_x && j == highlight_y) {
					gameWindow.AttrOn(A_REVERSE);
					drawSign(Dboard[i][j]);
					gameWindow.AttrOff(A_REVERSE);
				} else
					drawSign(Dboard[i][j]);
			}
		}
	}
	gameWindow << licznik;
	gameWindow.Refresh();
}

void Plansza::undraw() {
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			moveCoursor(i + 2, j + 2);
			gameWindow<<" ";
		}
	}
	gameWindow.Refresh();
}

void Plansza::choose() {
	bool click = false;
	highlight_x = 0;
	highlight_y = 0;
	int c;
	while (!esc) {
		noecho();
		gameWindow >> c;
		echo();
		switch (c) {
			case 'w':
			case KEY_UP:
			case '8':
				if (highlight_x == 0)
					highlight_x = height - 1;
				else
					highlight_x--;
				break;
			case 'x':
			case KEY_DOWN:
			case '2':
				if (highlight_x == height - 1)
					highlight_x = 0;
				else
					highlight_x++;
				break;
			case 'd':
			case KEY_RIGHT:
			case '6':
				if (highlight_y == width - 1)
					highlight_y = 0;
				else
					highlight_y++;
				break;
			case 'a':
			case KEY_LEFT:
			case '4':
				if (highlight_y == 0)
					highlight_y = width - 1;
				else
					highlight_y--;
				break;
			case 'q':
			case '7':
				if(highlight_x > 0 && highlight_y >0){
					highlight_x--;
					highlight_y--;
				}
				break;
			case 'e':
			case '9':
				if (highlight_x >0 && highlight_y < (width-1)){
					highlight_x--;
					highlight_y++;
				}
				break;
			case 'z':
			case '1':
				if (highlight_x < height - 1 && highlight_y >0) {
					highlight_x++;
					highlight_y--;
				}
				break;
			case 'c':
			case '3':
				if (highlight_x < height - 1 && highlight_y < width - 1) {
					highlight_x++;
					highlight_y++;
				}
			case 's':
			case 13:
			case' ':
			case '5':
				choice_x = highlight_x;
				choice_y = highlight_y;
				click = true;
				if (first_clik == 0) {
					first_x = choice_x;
					first_y = choice_y;
					first_clik++;;
				}
				break;
			case '?':
				if(Dboard[highlight_x][highlight_y] == mediumDestinyDots)
					Dboard[highlight_x][highlight_y] = '?';
				else if (Dboard[highlight_x][highlight_y] == '?')
					Dboard[highlight_x][highlight_y] = mediumDestinyDots;
				break;
			case 27:
				esc = true;
				break;
		}
		if (click) {
			if (licznik == 0)
			{
				
				win();
			}
			if (first_clik == 1) {
				draw_bombs();
				first_clik++;
			}
			if (Tboard[choice_x][choice_y] == bomb) {
				uncover();
				uncover_bombs();
				draw();
				_loose = true;
				break;
			}
			if (Tboard[choice_x][choice_y] == lowDestinyDots)
				odslon_pola_wokol(choice_x, choice_y);
			else
				uncover();
			click = false;
		}
		draw();
	}
	noecho();
}

void Plansza::uncover_bombs()
{
	for (int it = 0; it < height; it++) {
		for (int it2 = 0; it2 < width; it2++) {
			if (Tboard[it][it2] == bomb)
				Dboard[it][it2] = Tboard[it][it2];
		}
	}
}
void Plansza::moveCoursor(int line, int column) {
	gameWindow.MoveCursor(line, column);
}

void Plansza::uncover() {
	licznik--;
	Dboard[choice_x][choice_y] = Tboard[choice_x][choice_y];
}

void Plansza::drawSign(char sign) {
	gameWindow << sign;
}

void Plansza::odslon_pola_wokol(int x, int y) {
	bool a = true;
	if ((Dboard[x][y] == mediumDestinyDots || Dboard[x][y] == '?') && Tboard[x][y] != bomb && a) {
		Dboard[x][y] = Tboard[x][y]; licznik--;
		
		if (Tboard[x][y] != lowDestinyDots) a = false;
		if (Tboard[x][y] != bomb && Dboard[x][y] != '?' && a) {
			int zi_p1 = x + 1;
			int zi_m1 = x - 1;
			int zx_p1 = y + 1;
			int zx_m1 = y - 1;
			if (zi_m1 >= 0 && zx_m1 >= 0)
				odslon_pola_wokol(zi_m1, zx_m1); //gora lewo
			if (zi_m1 >= 0)
				odslon_pola_wokol(zi_m1, y); // gora
			if (zi_m1 >= 0 && zx_p1<width)
				odslon_pola_wokol(zi_m1, zx_p1); // gora prawo
			if (zi_p1<height && zx_m1 >= 0)
				odslon_pola_wokol(zi_p1, zx_m1); // dol lewo
			if (zi_p1<height)
				odslon_pola_wokol(zi_p1, y); // dol 
			if (zi_p1<height && zx_p1<width)
				odslon_pola_wokol(zi_p1, zx_p1); // dol prawo
			if (zx_m1 >= 0)
				odslon_pola_wokol(x, zx_m1); // lewo		
			if (zx_p1<width)
				odslon_pola_wokol(x, zx_p1); // prawo
		}
	}
}