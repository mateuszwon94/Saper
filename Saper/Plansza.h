#pragma once

#include "Window.h"
#include <vector>
#include "Okno.h"
#include "Timer.h"

class Plansza {
	public:
		Plansza(int a, int b, int bombs, Window* win);

		bool loose() { return _loose; }
		bool isPause() { return esc; }
		void run();

		static int getWidth() { return wid; }
		static int getHeight() { return heig; }
		static int getColumns() { return wid; }
		static int getLines() { return heig; }
		static int getBombs() { return n_bombs; }

		static void setWidth(int width) { wid = width; }
		static void setHeight(int heigth) { heig = heigth; }
		static void setColumns(int columns) { wid = columns; }
		static void setLines(int lines) { heig = lines; }
		static void setBombs(int bombs) { n_bombs = bombs; }

		static Plansza& getCurrent() { return *current; }
		static void setCurrent(Plansza& plansza) { current = &plansza; }
		static void setCurrent(Plansza* plansza) { current = plansza; }

		~Plansza();

	private:
		static int heig;
		static int wid;
		int width;
		int height;
		int n_bomb;
		Window * gameWindow;
		std::vector<std::vector<char>> Tboard;
		std::vector<std::vector<char>> Dboard;
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
		void odslon_pola_wokol(int x, int y);
		void znaczniki();
		void draw();
		void undraw();
		void moveCoursor(int line, int column);
		void drawSign(char sign);
		void choose();
		void uncover();
		static Plansza* current;
		static int first_clik;
};
