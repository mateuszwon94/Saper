#pragma once

#include "Window.h"
#include "Results.h"
#define endl "\n"
#define version "v1.0.0"

/*!
*  \brief     Klasa pomocnicza
*  \details   Jest to klasa pomocnicza zajmujaca sie inicjalizacja wszystkich okien i odpowiednim ich przygotowaniem do wyswietlenia
*  \author    Mateusz Winiarski
*  \version   v1.0
*  \date      2015
*/
class Okno {
	public:
		/*!
		*  \brief     Funkcja inicjalizuje wiele potrzebnych zmienych
		*  \details   Stworzona w calu zawarcia inicjalizacji potrzebnych w pliku Saper.cpp w jednym miejscu
		*/
		static void Initialize();

		/*!
		*  \brief     Ustawia obramowanie dla wskazanego okna
		*  @param window Okno dla ktorego maja byc ustawione obramowania
		*/
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
