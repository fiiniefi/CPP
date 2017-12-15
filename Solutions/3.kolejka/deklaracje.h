#include "stdafx.h"
#ifndef KOLEJKA_H
#define KOLEJKA_H
#include <iostream>
#include <string>


class kolejka
{
private:
	std::string *kol;
	int pojemnosc;
	int aktualnie;
	int poczatek;

public:
	void wstaw(std::string slowo);
	std::string pobierz();
	std::string sprawdz();
	int rozmiar();
	kolejka& operator=(const kolejka &wzor);
	kolejka& operator=(kolejka &&wzor);

	kolejka();
	kolejka(int poj);
	kolejka(int poj, std::initializer_list<std::string> lista);
	kolejka(const kolejka &wzor);
	kolejka(kolejka &&wzor);
	~kolejka();
};

#endif KOLEJKA_H