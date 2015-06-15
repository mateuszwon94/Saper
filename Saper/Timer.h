#pragma once

#include <chrono>
#include <mutex>
#include "Window.h"

class Timer {
	public:

		static void reset();
		static void start();
		static void restart();
		static void resume();
		static void pause() { _isPaused = (true); }
		static void stop();
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

