#pragma once
#include <string>
#include <fstream>
#include "Window.h"
#include <vector>
#include <algorithm>   
struct Pair {
	std::string rozmiar;
	int wynik;
};
/*!
*  \brief     Klasa zajmuj�ca sie zapisem i wyswietlaniem wynik�w
*  \details   Jest to klasa zajmuj�ca sie zapisem wynik�w do pliku, wyswietlaniem w kolejno�ci od najlepszego z podzia�em na poziomy trudno�ci. Jest ona singletonem
*  \author    Magdalena Wieczorek
*  \version   v1.0
*  \date      2015
*/
class Results {
public:
	/*!
	*  \brief     Konstruktor klasy Results
	*  \details  odpowiada za wywo�anie funkcji tworz�cej plik w celu automatycznej mo�liwosci zapisu odczytu
	*/
	Results();
	/*!
	*  \brief     Funkcja odpowiadajaca za tworzenie pliku
	*  \details   Funkcja odpowiadajaca za tworzenie pliku o zadanej nazwie i sprawdzenie jego poprawno�ci
	*  @param name parametr podajacy nazwe pliku
	*/
	void createFile(std::string name);
	/*!
	*  \brief     Destruktor klasy Results
	*  \details  odpowiada za zamkniecie pliku
	*/
	~Results();
	/*!
	*  \brief    getter pobieraj�cy instancje klasy
	*/
	static Results* getInstance();
	/*!
	*  \brief    Funkcja sprawdzaj�ca czy nie wyst�pi� problem z plikiem
	*  \return warto�c true jesli wystapi� problem, false jesli nie
	*/
	bool getProblem(){ return problem; }
	/*!
	*  \brief    Prze�adowany operator <<
	*  \details  Prze�adowany operator << pozwalajacy szybko zapisa� do pliku
	*/
	Results& operator<<(std::string text);
	/*!
	*  \brief    Funkcja �adujaca stan pliku
	*  \details  Funkcja �aduj�ca stan pliku, zapisuje wyniki do opowiednich kontener�w w celu sortowania i poprawnego wy�wietlania
	*/
	void load();
	/*!
	*  \brief    Funkcja odpowiadjaca za wy�wietlanie wynik�w
	*/
	void view();
	/*!
	*  \brief    zmienna przechowujaca wska�nik na plik
	*/
	std::fstream file;
private:
	void viewT();
	void viewF();
	bool show;
	int copy(int first, std::string text);
	Pair copy(std::string text, int first, int end);
	void sorting();
	std::vector<int> easy;
	std::vector<int> mild;
	std::vector<int> hard;
	std::vector<Pair> own30;
	std::vector<Pair> own70;
	std::vector<Pair> own;

	static Results* _instance;
	bool problem;
	//SORTOWANIE
};