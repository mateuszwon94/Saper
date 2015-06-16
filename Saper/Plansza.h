#pragma once

#include "Window.h"
#include <vector>
#include <array>
#include "Okno.h"
#include "Timer.h"
#include <thread>
/*!
*  \brief     Klasa odpowiadajaca za logike gry i wyswietlanie Planszy
*  \details   Jest to klasa odpowiadajaca za logike gry, wyswietlanie planszy, sprawdzanie stanu gry ogolnie za gre.
*  \author    Magdalena Wieczorek
*  \version   v1.0
*  \date      2015
*/
class Plansza {
	public:
		/*!
		*  \brief     Konstruktor klasy Plansza
		*  \details   Konstruktor klasy Planszy
		*  @param a okresla ilosc kolumn planszy
		*  @param b okresla ilosc wierszy planszy
		*  @param bombs okresla ilosc bomb na planszy
		*  @param win jest referencja do okna na którym sie rysuje plansza
		*/
		Plansza(int a = Plansza::getColumns(), int b = Plansza::getLines(), int bombs = Plansza::getBombs(), Window& win = ::gameWindow);

		/*!
		*  \brief     Funkcja sprawdzajaca stan gry
		*  \details   Funkcja  sprawdzajaca stan gry, pausa lub nie
		*  \return falaga esc, równa true jesli uzytkownik wcisnal esc czyli jesli jest pausa.
		*/
		bool isPause() { return esc; }
		/*!
		*  \brief     Funkcja odpowiedzialna za glowna petle gry
		*  \details Glowna petla gry - logika, sprawdzanie eventow rysowanie. 
		*/
		void run();
		/*!
		*  \brief   getter zwracajacy liczbe kolumn planszy
		*  \return wid liczba kolumn planszy
		*/
		static int getColumns() { return wid; }
		/*!
		*  \brief   getter zwracajacy liczbe wierszy planszy
		*  \return heig liczba wierszy planszy
		*/
		static int getLines() { return heig; }
		/*!
		*  \brief   getter zwracajacy liczbe bomb na planszy
		*  \return n_bombs liczba bomb na planszy
		*/
		static int getBombs() { return n_bombs; }
		/*!
		*  \brief   Funkcja ustawiajaca liczbe kolumn, wierszy i bomb na planszy
		*  @param values tablica 3 wartosci, kolumn, wierszy i bomb
		*/
		static void setCLB(std::array<int, 3> values);
		/*!
		*  \brief   getter zwracajacy aktualny stan planszy
		*  \return instanja planszy
		*/
		static Plansza& getCurrent() { return *current; }
		/*!
		*  \brief   getter zwracajacy aktualny stan planszy
		*  \return instanja planszy
		*/
		static void setCurrent(Plansza* plansza) { current = plansza; }
		/*!
		*  \brief   Destruktor Klasy Plansza
		*  \details Czysci ekran i zeruje flagi
		*/
		~Plansza();

	private:
		bool win() { if (licznik == 0) return true; else return false; }
		bool loose() { return _loose; }
		static int heig;
		static int wid;
		int licznik;
		int width;
		int height;
		int n_bomb;
		Window& gameWindow;
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
		void draw_result();
		void undraw_result();
		void draw_timer();
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
		void uncover_bombs();
		static Plansza* current;
		static int first_clik;
		int second;
		static std::thread* timer_thread;
};

