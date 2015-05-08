#pragma once

#include <chrono>

class Timer {
	public:
		Timer();

		void start();
		void restart();
		void resume();
		void pause();
		void stop();
		int second();
		
		void operator()();
		void operator++();
		void operator++(int) { operator++(); }

		operator std::chrono::milliseconds();
		operator long long();
		operator int() { return second(); }

	private:
		bool _isPaused;
		bool _isWorking;
		std::chrono::milliseconds _time;
		std::chrono::steady_clock::time_point _start;
};

