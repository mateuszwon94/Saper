#include "Okno.h"
#include "Help.h"
#include "Timer.h"
#include <vector>

int ile = 2;
std::string nazwy[] = { "Nowa Gra", "Zamknij" };
int specjalne[] = { 0, 0 };

char doubleDownLeftCorner = 200;	//╚
char doubleUpLeftCorner = 201;      //╔
char doubleUpRightCorner = 187;     //╗
char doubleDownRightCorner = 188;   //╝
char doubleHorizontalAndUp = 202;   //╩
char doubleHorizontalAndDown = 203; //╦
char doubleVerticalAndRight = 204;  //╠
char doubleVerticalAndLeft = 185;   //╣
char doubleHorizontal = 205;        //═
char doubleVertical = 186;          //║
char doubleCross = 206;             //╬

char singleDownLeftCorner = 192;	//└
char singleUpLeftCorner = 218;      //┌
char singleUpRightCorner = 191;     //┐
char singleDownRightCorner = 217;   //┘
char singleHorizontalAndUp = 193;   //┴
char singleHorizontalAndDown = 194; //┬
char singleVerticalAndRight = 195;  //├
char singleVerticalAndLeft = 180;   //┤
char singleHorizontal = 196;        //─
char singleVertical = 179;          //│
char singleCross = 197;             //┼

char lowDestinyDots = 176;          //░
char mediumDestinyDots = 177;       //▒
char highDestinyDots = 178;         //▓
char bomb = 207;
char fklag = '?';

void Okno::Initialize() {
	Timer::getMutex()->lock();
	keypad(console, true);
	keypad(gameWindow, true);
	keypad(shadow, true);

	console << "Saper " << version << endl;
	for (int i = 0; i < console.columns(); ++i)
		console << "_";

	ColorPair okno1 = ColorPair(COLOR_BLACK, COLOR_WHITE);
	ColorPair cien = ColorPair(COLOR_WHITE, COLOR_BLACK);

	gameWindow.AttrOn(okno1);
	shadow.Background(cien);

	SetBorderColoured(gameWindow);

	gameWindow.AttrOn(okno1);
	gameWindow.Background(okno1);

	//static Help help = Help(65, 40, 1, 97);
	Timer::getMutex()->unlock();
}

void Okno::SetBorderColoured(Window& window) {
	ColorPair upleft = ColorPair(COLOR_WHITE, COLOR_WHITE);
	ColorPair downright = ColorPair(COLOR_BLACK, COLOR_WHITE);

	window.AttrOn(A_BOLD);

	window.AttrOn(upleft);

	window << singleUpLeftCorner;

	for (register int i = 1; i < window.lines() - 1; ++i) {
		window.MoveCursor(i, 0);
		window << singleVertical; 
		window.MoveCursor(i, 75);
		window << singleVertical;
		window.MoveCursor(i, 75+21);
		window << singleVertical;
	}
	for (register int i = 1; i < window.columns() - 1; ++i) {
		window.MoveCursor(0, i);
		window << singleHorizontal;
		if ( 75 < i && i < 75+21) {
			window.MoveCursor(3, i);
			window << singleHorizontal;
			window.MoveCursor(23, i);
			window << singleHorizontal;
			window.MoveCursor(31, i);
			window << singleHorizontal;
			window.MoveCursor(40, i);
			window << singleHorizontal;
		}
	}
	
	window.MoveCursor(0, 75);
	window << singleHorizontalAndDown;
	window.MoveCursor(0, 75+21);
	window << singleHorizontalAndDown;

	window.AttrOff(upleft);
	window.AttrOff(A_BOLD);

	window.AttrOn(downright);

	window.MoveCursor(0, window.columns()-1);
	window << singleUpRightCorner;

	window.MoveCursor(window.lines() - 1, window.columns() - 1);
	window << singleDownRightCorner;

	window.MoveCursor(window.lines() - 1, 0);
	window << singleDownLeftCorner;

	for (int i = 1; i < window.lines()-1; ++i) {
		window.MoveCursor(i, window.columns()-1);
		window << singleVertical;
	}
	for (int i = 1; i < window.columns()-1; ++i) {
		window.MoveCursor(window.lines()-1, i);
		window << singleHorizontal;
	}
	
	window.MoveCursor(window.lines() - 1, 75);
	window << singleHorizontalAndUp;
	window.MoveCursor(window.lines() - 1, 75+21);
	window << singleHorizontalAndUp;

	window.AttrOff(downright);


}
