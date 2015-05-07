#pragma once
#include "Window.h"
#include <vector>
#include "Okno.h"
using namespace std;

using namespace std;
class Plansza
{
private:
	static int heig;
	static int wid;
	int width;
	int height;
	int n_bomb;
	Window * gameWindow;
	vector<vector<char>> Tboard;
	vector<vector<char>> Dboard;
	static int n_bombs;
	int highlight_x;
	int highlight_y;
	int choice_x;
	int choice_y;
	bool esc;
	bool _loose;
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
	bool loose() { return _loose; }
	bool isPause() { return esc; }
	void Plansza::run();
	static int getWidth(){ return wid; }
	static int getHeight() { return heig; }
	static int getBombs() { return n_bombs; }
~Plansza();
};

