#include "Okno.h"
//#include "Menu.h"
#include <vector>

int ile = 2;
std::string nazwy[] = { "Nowa Gra", "Zamknij" };
int specjalne[] = { 0, 0 };

const unsigned char doubleDownLeftCorner = 200;    //╚
const unsigned char doubleUpLeftCorner = 201;      //╔
const unsigned char doubleUpRightCorner = 187;     //╗
const unsigned char doubleDownRightCorner = 188;   //╝
const unsigned char doubleHorizontalAndUp = 202;   //╩
const unsigned char doubleHorizontalAndDown = 203; //╦
const unsigned char doubleVerticalAndRight = 204;  //╠
const unsigned char doubleVerticalAndLeft = 185;   //╣
const unsigned char doubleHorizontal = 205;        //═
const unsigned char doubleVertical = 186;          //║
const unsigned char doubleCross = 206;             //╬

const unsigned char singleDownLeftCorner = 192;    //└
const unsigned char singleUpLeftCorner = 218;      //┌
const unsigned char singleUpRightCorner = 191;     //┐
const unsigned char singleDownRightCorner = 217;   //┘
const unsigned char singleHorizontalAndUp = 193;   //┴
const unsigned char singleHorizontalAndDown = 194; //┬
const unsigned char singleVerticalAndRight = 195;  //├
const unsigned char singleVerticalAndLeft = 180;   //┤
const unsigned char singleHorizontal = 196;        //─
const unsigned char singleVertical = 179;          //│
const unsigned char singleCross = 197;             //┼

const unsigned char lowDestinyDots = 176;          //░
const unsigned char mediumDestinyDots = 177;       //▒
const unsigned char highDestinyDots = 178;         //▓

void Okno::Initialize(Window& console, Window& gameWindow, Window& shadow) {

	console << "Saper v0.0.0" << endl;
	for (int i = 0; i < console.columns(); ++i)
		console << "_";

	ColorPair okno1 = ColorPair(COLOR_BLACK, COLOR_WHITE);
	ColorPair cien = ColorPair(COLOR_WHITE, COLOR_BLACK);

	gameWindow.AttrOn(okno1);
	shadow.Background(cien);

	SetBorderColoured(gameWindow);

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
		window.MoveCursor(i, 75);
		window << singleVertical;
	}
	for (register int i = 1; i < window.columns() - 1; ++i) {
		window.MoveCursor(0, i);
		window << singleHorizontal;
	}
	
	window.MoveCursor(0, 75);
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

	window.AttrOff(downright);


}
