#pragma once

#include "Window.h"
#define endl "\n"
#define version "v0.7"

class Okno {
	public:
		static void Initialize();
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
extern char bomb;
extern char flag;
extern char lowDestinyDots;          //░
extern char mediumDestinyDots;       //▒
extern char highDestinyDots;         //▓
