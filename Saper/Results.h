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
*  \brief     Klasa zajmujaca sie zapisem i wyswietlaniem wynikow
*  \details   Jest to klasa zajmujaca sie zapisem wyników do pliku, wyswietlaniem w kolejnosci od najlepszego z podzialem na poziomy trudnosci. Jest ona singletonem
*  \author    Magdalena Wieczorek
*  \version   v1.0
*  \date      2015
*/
class Results {
public:
	/*!
	*  \brief     Konstruktor klasy Results
	*  \details  odpowiada za wywolanie funkcji tworzacej plik w celu automatycznej mozliwosci zapisu odczytu
	*/
	Results();
	/*!
	*  \brief     Funkcja odpowiadajaca za tworzenie pliku
	*  \details   Funkcja odpowiadajaca za tworzenie pliku o zadanej nazwie i sprawdzenie jego poprawnosci
	*  @param name parametr podajacy nazwe pliku
	*/
	void createFile(std::string name);
	/*!
	*  \brief     Destruktor klasy Results
	*  \details  odpowiada za zamkniecie pliku
	*/
	~Results();
	/*!
	*  \brief    getter pobierajacy instancje klasy
	*/
	static Results* getInstance();
	/*!
	*  \brief    Funkcja sprawdzajaca czy nie wystapil problem z plikiem
	*  \return wartosc true jesli wystapil problem, false jesli nie
	*/
	bool getProblem(){ return problem; }
	/*!
	*  \brief    Przeladowany operator <<
	*  \details  Przeladowany operator << pozwalajacy szybko zapisac do pliku
	*/
	Results& operator<<(std::string text);
	/*!
	*  \brief    Funkcja ladujaca stan pliku
	*  \details  Funkcja ladujaca stan pliku, zapisuje wyniki do opowiednich kontenerów w celu sortowania i poprawnego wyswietlania
	*/
	void load();
	/*!
	*  \brief    Funkcja odpowiadjaca za wyswietlanie wyników
	*/
	void view();
	/*!
	*  \brief    zmienna przechowujaca wskaznik na plik
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