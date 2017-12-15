#include "stdafx.h"
#include <iostream>
#include <string>
#include "deklaracje.h"




kolejka::kolejka() : kolejka(4) {}


kolejka::kolejka(int poj) : pojemnosc(poj), aktualnie(0), poczatek(0)
{
	this->kol = new std::string[poj];
}


kolejka::kolejka(int poj, std::initializer_list<std::string> lista) : kolejka(poj)
{
	for (auto iterator = lista.begin(); iterator != lista.end(); this->aktualnie++, iterator++)
	{
		if (this->aktualnie >= this->pojemnosc)
			throw std::string("Rozmiar kolejki przekroczony juz przy inicjalizacji!\n");
		
		this->kol[aktualnie] = *iterator;
	}
}


kolejka::kolejka(const kolejka &wzor)
{
	this->pojemnosc = wzor.pojemnosc;
	this->aktualnie = wzor.aktualnie;
	this->poczatek = wzor.poczatek;
	this->kol = new std::string[this->pojemnosc];

	for (int i = this->poczatek; i < this->aktualnie; i++)
		this->kol[i] = wzor.kol[i];
}


kolejka::kolejka(kolejka &&wzor)
{
	this->pojemnosc = wzor.pojemnosc;
	this->aktualnie = wzor.aktualnie;
	this->poczatek = wzor.poczatek;
	this->kol = wzor.kol;
	wzor.kol = nullptr;
}


kolejka::~kolejka()
{
	delete[] kol;
}


kolejka& kolejka::operator=(const kolejka &wzor)
{
	this->~kolejka();

	this->pojemnosc = wzor.pojemnosc;
	this->aktualnie = wzor.aktualnie;
	this->poczatek = wzor.poczatek;
	this->kol = new std::string[this->pojemnosc];

	for (int i = this->poczatek; i < this->aktualnie; i++)
		this->kol[i] = wzor.kol[i];
	return *this;
}


kolejka& kolejka::operator=(kolejka &&wzor)
{
	this->~kolejka();

	this->pojemnosc = wzor.pojemnosc;
	this->aktualnie = wzor.aktualnie;
	this->poczatek = wzor.poczatek;
	this->kol = wzor.kol;
	wzor.kol = nullptr;
	return *this;
}


void kolejka::wstaw(std::string slowo)
{
	if (((this->aktualnie) % (this->pojemnosc) == (this->poczatek) % (this->pojemnosc)) && (this->poczatek != this->aktualnie))
		throw std::string("Nie moge dolozyc elementu do kolejki, poniewaz jej pojemnosc zostalaby przekroczona!\n");
	this->kol[(this->aktualnie%this->pojemnosc)] = slowo;
	this->aktualnie++;
}


std::string kolejka::pobierz()
{
	if (this->poczatek >= this->aktualnie)
		throw std::string("Nie ma czego dobierac, brak elementow w kolejce!\n");
	std::string zwroc = this->sprawdz();
	this->poczatek++;
	return zwroc;
}


std::string kolejka::sprawdz()
{
	return this->kol[(this->poczatek%this->pojemnosc)];
}


int kolejka::rozmiar()
{
	return (this->aktualnie - this->poczatek);
}