#pragma once
#include <ctime>

class Timer {
	public:
		Timer() { }

		void start(time_t *Time = NULL) { _start = time(Time); }

		void restart(time_t *Time = NULL) {
			_time = 0;
			_start = time(Time);
		}

		void resume() { _start = time(NULL); }

		void pause() { _start = 0; }

		time_t stop() {
			_start = 0;
			return _time;
		}

		void operator++() {
			_time += _start - time(NULL);
			_start = time(NULL);
		}

		void operator++(int) { operator++(); }

		~Timer() { }
	private:
		time_t _time = 0;
		time_t _start = 0;

};

