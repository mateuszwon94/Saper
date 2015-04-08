#ifndef OKNO_H
#define OKNO_H

#include "Window.h"
#define endl "\n"

class Okno {
	public:
		static void Initialize(Window& console, Window& gameWindow, Window& shadow);
		static void SetBorderColoured(Window& window);
};

extern const unsigned char doubleDownLeftCorner;    //╚
extern const unsigned char doubleUpLeftCorner;      //╔
extern const unsigned char doubleUpRightCorner;     //╗
extern const unsigned char doubleDownRightCorner;   //╝
extern const unsigned char doubleHorizontalAndUp;   //╩
extern const unsigned char doubleHorizontalAndDown; //╦
extern const unsigned char doubleVerticalAndRight;  //╠
extern const unsigned char doubleVerticalAndLeft;   //╣
extern const unsigned char doubleHorizontal;        //═
extern const unsigned char doubleVertical;          //║
extern const unsigned char doubleCross;             //╬

extern const unsigned char singleDownLeftCorner;    //└
extern const unsigned char singleUpLeftCorner;      //┌
extern const unsigned char singleUpRightCorner;     //┐
extern const unsigned char singleDownRightCorner;   //┘
extern const unsigned char singleHorizontalAndUp;   //┴
extern const unsigned char singleHorizontalAndDown; //┬
extern const unsigned char singleVerticalAndRight;  //├
extern const unsigned char singleVerticalAndLeft;   //┤
extern const unsigned char singleHorizontal;        //─
extern const unsigned char singleVertical;          //│
extern const unsigned char singleCross;             //┼

extern const unsigned char lowDestinyDots;          //░
extern const unsigned char mediumDestinyDots;       //▒
extern const unsigned char highDestinyDots;         //▓
#endif
