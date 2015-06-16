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

		static void start();
		static void pause() { _isPaused = (true); }
		static void resume();
		static void stop();
		static void restart();
		static void reset();

		static int second() { return _time.count() / 1000; }
		
		static std::recursive_mutex* getMutex() { return _mutex; }
		static void setMutex(std::recursive_mutex* newMutex) { _mutex = newMutex; }
		
		static void run();
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

