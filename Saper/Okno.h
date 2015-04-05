#ifndef OKNO_H
#define OKNO_H

#include "Window.h"
#define endl "\n"

class Okno {
	public:
		static void Initialize(Window& console, Window& gameWindow, Window& shadow);
		static void SetBorderColoured(Window& window);
};

extern char doubleDownLeftCorner;    //╚
extern char doubleUpLeftCorner;      //╔
extern char doubleUpRightCorner;     //╗
extern char doubleDownRightCorner;   //╝
extern char doubleHorizontalAndUp;   //╩
extern char doubleHorizontalAndDown; //╦
extern char doubleVerticalAndRight;  //╠
extern char doubleVerticalAndLeft;   //╣
extern char doubleHorizontal;        //═
extern char doubleVertical;          //║
extern char doubleCross;             //╬

extern char singleDownLeftCorner;    //└
extern char singleUpLeftCorner;      //┌
extern char singleUpRightCorner;     //┐
extern char singleDownRightCorner;   //┘
extern char singleHorizontalAndUp;   //┴
extern char singleHorizontalAndDown; //┬
extern char singleVerticalAndRight;  //├
extern char singleVerticalAndLeft;   //┤
extern char singleHorizontal;        //─
extern char singleVertical;          //│
extern char singleCross;             //┼

extern char lowDestinyDots;          //░
extern char mediumDestinyDots;       //▒
extern char highDestinyDots;         //▓
#endif
