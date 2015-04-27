#include "Okno.h"
//#include "Menu.h"
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
//Menu& menu = Menu(nazwy, specjalne, ile, gameWindow, gameWindow.lines() - 2, 5, false);

void Okno::Initialize(Window& console, Window& gameWindow, Window& shadow) {

	console << "Saper v0.0.0" << endl;
	for (int i = 0; i < console.columns(); ++i)
		console << "_";

	ColorPair okno1 = ColorPair(COLOR_BLACK, COLOR_WHITE);
	ColorPair cien = ColorPair(COLOR_WHITE, COLOR_BLACK);

	gameWindow.AttrOn(okno1);
	shadow.Background(cien);

	SetBorderColoured(gameWindow);
	//gameWindow << menu;

	gameWindow.AttrOn(okno1);
	gameWindow.Background(okno1);
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
	}
	for (register int i = 1; i < window.columns() - 1; ++i) {
		window.MoveCursor(0, i);
		window << singleHorizontal;
	}

	window.AttrOff(upleft);
	window.AttrOff(A_BOLD);

	window.AttrOn(downright);

	window.MoveCursor(0, window.columns()-1);
	window << singleUpRightCorner;

	window.MoveCursor(window.lines() - 1, window.columns() - 1);
	window << singleDownRightCorner;

	window.MoveCursor(window.lines() - 1, 0);
	window << singleDownLeftCorner;

	for (register int i = 1; i < window.lines()-1; ++i) {
		window.MoveCursor(i, window.columns()-1);
		window << singleVertical;
	}
	for (register int i = 1; i < window.columns()-1; ++i) {
		window.MoveCursor(window.lines()-1, i);
		window << singleHorizontal;
	}
	
	window.AttrOff(downright);
}
