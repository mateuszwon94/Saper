#include "Timer.h"
#include <ctime>


Timer::Timer()
{
}

void Timer::start(int a)
{
	add=a;
	time = clock();
}
int Timer::stop()
{
	time = clock() - time;
	return ((float)time) / CLOCKS_PER_SEC + add;
}
Timer::~Timer()
{
}
