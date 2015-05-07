#pragma once
class Timer
{
private:
	int time;
	int add;
public:
	Timer();
	int stop();
	void start(int st = 0);
~Timer();
};

