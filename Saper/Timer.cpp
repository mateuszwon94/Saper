#include "Timer.h"

using namespace std;
using namespace std::chrono;

Timer::Timer() {
	_isWorking = false; 
	_isPaused = false;
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
	_isPaused=(false);
	_start=(high_resolution_clock::now());
}

void Timer::pause() {
	operator++();
	_isPaused=(true);
}

void Timer::stop() {
	operator++();
	_isWorking=(false);
	_isPaused=(false);
}

int Timer::second() {
	if (_isWorking)
		operator++();
	return _time.count() / 1000;
}

void Timer::operator()() {
	
}

void Timer::operator++() {
	auto now = high_resolution_clock::now();
	_time += duration_cast<milliseconds>(now - _start);
	_start=(now);
}

Timer::operator std::chrono::milliseconds() {
	if (_isWorking)
		operator++();
	return _time;
}

Timer::operator long long() {
	if (_isWorking)
		operator++();
	return _time.count(); 
}
