#include "Timer.h"
#include <array>
#include <stdexcept>
#include <thread>

using namespace std;
using namespace std::chrono;

recursive_mutex* Timer::_mutex = new recursive_mutex();
bool Timer::_end = false;
bool Timer::_isPaused = false;
bool Timer::_isWorking = false;
steady_clock::time_point Timer::_start = high_resolution_clock::now();
milliseconds Timer::_time = duration_cast<milliseconds>(_start - _start);

void Timer::reset() {
	_isPaused = false;
	_isWorking = false;
	_start = high_resolution_clock::now();
	_time = duration_cast<milliseconds>(_start - _start);
}

void Timer::start() {
	_isWorking=(true);
	_isPaused=(false);
	_start=(high_resolution_clock::now());
}

void Timer::restart() {
	_isPaused=(false);
	auto now = high_resolution_clock::now();
	_time=(duration_cast<milliseconds>(now - now));
	_isWorking=(true);
	_start=(high_resolution_clock::now());
}

void Timer::resume() {
	if (!_isPaused) return;
	_isPaused=(false);
	_start=(high_resolution_clock::now());
}

void Timer::stop() {
	increment();
	_isWorking=(false);
	_isPaused=(false);
}

void Timer::run() {
	if (_mutex == nullptr) _mutex = new recursive_mutex();
	while (1) {
		if (_end) return;
		if (stdscr == NULL || !_isWorking || _isPaused) {
			this_thread::sleep_for(milliseconds(490));
			continue;
		}
		_mutex->lock();
		//static array<int, 2> prevPos;
		//prevPos = gameWindow.GetCursorPos();
		gameWindow.MoveCursor(15 + 2 * 9, 80);
		gameWindow << "          ";
		increment();
		gameWindow.MoveCursor(15 + 2 * 9, 80);
		gameWindow << "Grasz " << second() << "s";
		//gameWindow.MoveCursor(prevPos[0], prevPos[1]);
		gameWindow.Refresh();
		_mutex->unlock();
		this_thread::sleep_for(milliseconds(490));
	}
}

void Timer::increment() {
	if (_isPaused || !_isWorking) return;
	auto now = high_resolution_clock::now();
	_time += duration_cast<milliseconds>(now - _start);
	_start=(now);
}