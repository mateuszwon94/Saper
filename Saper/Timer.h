#pragma once

#include <chrono>
#include <mutex>
#include "Window.h"

/*!
*  \brief     Klasa odpowiedzialna za licznik czasu
*  \details   Jest to klasa zajmujaca sie mozliwosciami licznika czasu. Moze go uruchomic, spauzowac, wznowic czy zrestartowac oraz podac czas w sekundach.
*  \author    Mateusz Winiarski
*  \version   v1.0
*  \date      2015
*  \warning   Moze mylic sie przy dluzszych okresach czasu co wyniki z narzutu wywolywania metod.
*/
class Timer {
	public:
		/*!
		*  \brief     Funkcja startujaca licznik
		*/
		static void start();

		/*!
		*  \brief     Funkcja zatrzymujaca licznik
		*/
		static void pause() { _isPaused = (true); }

		/*!
		*  \brief     Funkcja wznawiajaca prace licznika
		*/
		static void resume();

		/*!
		*  \brief     Funkcja konczaca prace licznika
		*/
		static void stop();

		/*!
		*  \brief     Funkcja restartujaca prace licznika
		*/
		static void restart();

		/*!
		*  \brief     Funkcja resetujaca ustawienia licznika
		*/
		static void reset();

		/*!
		*  \brief     Funkcja obliczajaca przez ile sekund pracowal licznik
		*  \return    Ilosc sekund przez jakie licznik pracowal
		*/
		static int second() { return _time.count() / 1000; }
		
		/*!
		*  \brief     Funkcja zwracajaca Mutex.
		*  \details   Jest on uzywany do chronienia wyswietlania w konsoli, zeby przypadkiem watek licznika nie zaczal konfliktowac sie z watkiem aplikacji
		*/
		static std::recursive_mutex* getMutex() { return _mutex; }

		/*!
		*  \brief     Funkcja ustawiajaca Mutex.
		*  @param newMutex nowy Mutex jaki ma byc ustawiony. Wykorzystywane jesli z jakiegos powodu nie ma w danej chwili ustalonego Mutexu
		*/
		static void setMutex(std::recursive_mutex* newMutex) { _mutex = newMutex; }
		
		/*!
		*  \brief     Funkcja uruchamiana przez drugi watek w Plansza.
		*/
		static void run();

		/*!
		*  \brief     Funkcja ustawiajaca flage konca pracy. Po jej wykonaniu watek odpowiedzialny za licznik jest zamykany.
		*/
		static void end() { _end = true; }

	private:
		static void increment();
		explicit Timer() = default;
		static bool _end;
		static bool _isPaused;
		static bool _isWorking;
		static std::chrono::milliseconds _time;
		static std::chrono::steady_clock::time_point _start;
		static std::recursive_mutex* _mutex;
};

