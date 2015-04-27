#include "Plansza.h"
#include<ctime>
#include <cstdlib>


Plansza::Plansza(int a, int b, int bomb, Window* win) :width(a), height(b), gameWindow(win), n_bomb(bomb), highlight_x(0), highlight_y(0),
				 esc(false)
{
	Tboard.resize(height);
	Dboard.resize(height);
	for (int it = 0; it < height; it++)
	{
		Tboard[it].resize(width);
		Dboard[it].resize(width);
		for (int it2 = 0; it2 < width; it2++)
		{
			Dboard[it][it2] = mediumDestinyDots;
			Tboard[it][it2] = lowDestinyDots;
		}
	}
	draw();
	choose();
}
void Plansza::draw_bombs()
{
	bool is_there = false;
	srand(time(NULL));
	for (int i = 0; i < n_bomb; i++)
	{
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
			if (x_up >= 0 && Tboard[x_up][y] != bomb)
			{
				Tboard[x_up][y] = '1';
			}
			if (x_up >= 0 && y_left >= 0 && Tboard[x_up][y_left] != bomb)
			{
				Tboard[x_up][y_left] = '1';
			}
			if (x_up >= 0 && y_right < width && Tboard[x_up][y_right] != bomb)
			{
				Tboard[x_up][y_right] = '1';
			}
			if (x_down <height && y_right < width && Tboard[x_down][y_right] != bomb)
			{
				Tboard[x_down][y_right] = '1';
			}
			if (x_down <height && y_left >=0 && Tboard[x_down][y_left] != bomb)
			{
				Tboard[x_down][y_left] = '1';
			}
			if (x_down <height && Tboard[x_down][y] != bomb)
			{
				Tboard[x_down][y] = '1';
			}
			if (y_left >= 0 && Tboard[x][y_left] != bomb)
			{
				Tboard[x][y_left] = '1';
			}
			if (y_right < width && Tboard[x][y_right] != bomb)
			{
				Tboard[x][y_right] = '1';
			}
		}
		else {
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
			if (Tboard[i][j] == '1')
			{
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
Plansza::~Plansza()
{
}
void Plansza::draw()
{
	if (has_colors() == FALSE)
	{
		endwin();
		printf("Your terminal does not support color\n");
		exit(1);
	}
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j){
			moveCoursor(i+2, j+2);
			if (Dboard[i][j] == bomb)
			{
				init_pair(1, COLOR_RED, COLOR_WHITE);
				wattron(gameWindow->getWin(), COLOR_PAIR(1));
				if (i == highlight_x && j == highlight_y)
				{
					wattron(gameWindow->getWin(), A_REVERSE);
					drawSign(Dboard[i][j]);
					wattroff(gameWindow->getWin(), A_REVERSE);
				}
				else
					drawSign(Dboard[i][j]);
				wattroff(gameWindow->getWin(), COLOR_PAIR(1));
			}
			else
			{
				if (i == highlight_x && j == highlight_y)
				{
					wattron(gameWindow->getWin(), A_REVERSE);
					drawSign(Dboard[i][j]);
					wattroff(gameWindow->getWin(), A_REVERSE);
				}
				else
					drawSign(Dboard[i][j]);
			}
		}
	}
	gameWindow->Refresh();
}
void Plansza::choose()
{
	static int first_clik = 0;
	bool click = false;
	highlight_x = 0;
	highlight_y = 0;
	int c;
	while (!esc)
	{
		noecho();
		c = wgetch(gameWindow->getWin());
		echo();
		switch (c)
		{
		case 'w':
		case '8':
			if (highlight_x == 0)
				highlight_x = height - 1;
			else
				highlight_x--;
			break;
		case 'x':
		case '2':
			if (highlight_x == height-1)
				highlight_x = 0;
			else
				highlight_x ++;
			break;
		case 'd':
		case '6':
			if (highlight_y == width-1)
				highlight_y=0;
			else
				highlight_y ++;
			break;
		case 'a':
		case '4':
			if (highlight_y == 0)
				highlight_y = width - 1;
			else
				highlight_y--;
			break;
		/*case 'q':
		case '7':
			if (highlight_x == 0 && highlight_y == 0) {
				highlight_x = height - 1;
				highlight_y = width - 1;
			}
			else if (highlight_x == 0 && highlight_y != 0){
				highlight_x = height - 1;
				highlight_y--;
			}
			else if (highlight_x != 0 && highlight_y == 0) {
				highlight_x--;
				highlight_y = width - 1;
			}
			else {
				highlight_x--;
				highlight_y--;
			}
			break;
		case 'e':
		case '9':
			if (highlight_x == 0 && highlight_y == (width-1)) {
				highlight_x = height - 1;
				highlight_y = 0;
			}
			else if (highlight_x == 0 && highlight_y < (width-1)) {
				highlight_x = height - 1;
				highlight_y++;
			}
			else if (highlight_x != 0 && highlight_y == (width-1)) {
				highlight_x--;
				highlight_y = 0;
			}
			else {
				highlight_x--;
				highlight_y++;
			}
			break;*/
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
			Dboard[highlight_x][highlight_y] = '?';
			break;
		case 27:
			esc = true;
			break;
		}
		if (click) {
			if (first_clik == 1) {
				draw_bombs();
				first_clik++;
			}
			if (Tboard[choice_x][choice_y] == bomb) {
				loose();
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
	}
	bool Plansza::loose() {
		return true;
	}

void Plansza::moveCoursor(int line, int column)
{
	wmove(gameWindow->getWin(), line, column);
}
void Plansza::uncover()
{
	
		Dboard[choice_x][choice_y] = Tboard[choice_x][choice_y];
}

void Plansza::drawSign(char sign)
{
	wprintw(gameWindow->getWin(), "%c", sign);
}
void Plansza::odslon_pola_wokol(int x, int y) {
	if ((Dboard[x][y] == mediumDestinyDots || Dboard[x][y] == '?') &&Tboard[x][y]==lowDestinyDots) { 
			Dboard[x][y] = Tboard[x][y];
		if (Tboard[x][y] == lowDestinyDots) { 	
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