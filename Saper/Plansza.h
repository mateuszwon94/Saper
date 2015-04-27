#pragma once
#include "Window.h"
#include <vector>
#include "Okno.h"
using namespace std;

using namespace std;
class Plansza
{
private:
	int height;
	int width;
	Window * gameWindow;
	vector<vector<char>> Tboard;
	vector<vector<char>> Dboard;
	int n_bomb;
	int highlight_x;
	int highlight_y;
	int choice_x;
	int choice_y;
	bool esc;
	void draw_bombs();
	int first_x;
	int first_y;
	void Plansza::odslon_pola_wokol(int x, int y);
	void Plansza::znaczniki();	
	void draw();
	void moveCoursor(int line, int column);
	void drawSign(char sign);
	void choose();
	void uncover();
public:
	Plansza(int a, int b,int bombs, Window* win);
	bool loose();

~Plansza();
};

