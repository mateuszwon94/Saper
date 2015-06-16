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
*  \brief     Klasa zajmuj¹ca sie zapisem i wyswietlaniem wyników
*  \details   Jest to klasa zajmuj¹ca sie zapisem wyników do pliku, wyswietlaniem w kolejnoœci od najlepszego z podzia³em na poziomy trudnoœci. Jest ona singletonem
*  \author    Magdalena Wieczorek
*  \version   v1.0
*  \date      2015
*/
class Results {
public:
	/*!
	*  \brief     Konstruktor klasy Results
	*  \details  odpowiada za wywo³anie funkcji tworz¹cej plik w celu automatycznej mo¿liwosci zapisu odczytu
	*/
	Results();
	/*!
	*  \brief     Funkcja odpowiadajaca za tworzenie pliku
	*  \details   Funkcja odpowiadajaca za tworzenie pliku o zadanej nazwie i sprawdzenie jego poprawnoœci
	*  @param name parametr podajacy nazwe pliku
	*/
	void createFile(std::string name);
	/*!
	*  \brief     Destruktor klasy Results
	*  \details  odpowiada za zamkniecie pliku
	*/
	~Results();
	/*!
	*  \brief    getter pobieraj¹cy instancje klasy
	*/
	static Results* getInstance();
	/*!
	*  \brief    Funkcja sprawdzaj¹ca czy nie wyst¹pi³ problem z plikiem
	*  \return wartoœc true jesli wystapi³ problem, false jesli nie
	*/
	bool getProblem(){ return problem; }
	/*!
	*  \brief    Prze³adowany operator <<
	*  \details  Prze³adowany operator << pozwalajacy szybko zapisaæ do pliku
	*/
	Results& operator<<(std::string text);
	/*!
	*  \brief    Funkcja ³adujaca stan pliku
	*  \details  Funkcja ³aduj¹ca stan pliku, zapisuje wyniki do opowiednich kontenerów w celu sortowania i poprawnego wyœwietlania
	*/
	void load();
	/*!
	*  \brief    Funkcja odpowiadjaca za wyœwietlanie wyników
	*/
	void view();
	/*!
	*  \brief    zmienna przechowujaca wskaŸnik na plik
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