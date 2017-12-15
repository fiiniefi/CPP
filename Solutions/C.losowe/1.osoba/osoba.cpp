#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>
#include <functional>
#include <algorithm>
#include <random>
#include <list>
#include <ctime>
#include <chrono>

using namespace std;

class osoba
{
public:
	osoba(string imie, string nazwisko, chrono::time_point<chrono::system_clock> data = chrono::system_clock::now()) : imie(imie), nazwisko(nazwisko), ur(data) {}
	osoba(const osoba &pattern)
	{
		this->imie = pattern.imie;
		this->nazwisko = pattern.nazwisko;
		this->ur = pattern.ur;
	}
	osoba& operator=(const osoba &pattern)
	{
		if (this == &pattern)
			return *this;
		this->~osoba();
		this->imie = pattern.imie;
		this->nazwisko = pattern.nazwisko;
		this->ur = pattern.ur;
	}
	string getImie() const
	{
		return this->imie;
	}
	string getNazwisko() const
	{
		return this->nazwisko;
	}
	auto getData() const
	{
		return this->ur;
	}
	friend ostream& operator<<(ostream &output, const osoba &pattern);
private:
	string imie;
	string nazwisko;
	chrono::time_point<chrono::system_clock> ur;
};


ostream& operator<<(ostream &output, const osoba &pattern)
{
	auto t = chrono::system_clock::to_time_t(pattern.getData());
	return output << pattern.getImie() << " " << pattern.getNazwisko() << "   " << asctime(localtime(&t));
}


void program();
void print_list(list<osoba> &lista);


int main()
{
	program();
}



void program()
{
	ifstream plik;
	plik.open("dane.txt");
	if (!plik.is_open())
		return;
	int n;
	plik >> n;
	list<osoba> lista;
	mt19937 silnik(time(0));
	uniform_int_distribution<int64_t> losuj(-97761600000000, 1496188800000000);
	chrono::system_clock::time_point punkt = chrono::system_clock::now();
	//auto generate = std::bind(std::uniform_int_distribution<int64_t>(-97761600000000, 1496188800000000), std::mt19937(silnik));
	punkt -= punkt.time_since_epoch();

	for (int i = 0; i < n; i++)
	{
		string imie;
		string nazwisko;
		plik >> imie;
		plik >> nazwisko;
		lista.push_back(osoba(imie, nazwisko, punkt += chrono::system_clock::duration(losuj(silnik))));
	}
	print_list(lista);
	lista.sort([](const osoba &val1, const osoba &val2) -> bool { return (val1.getImie() < val2.getImie()); });
	print_list(lista);
	lista.sort([](const osoba &val1, const osoba &val2) -> bool { return (val1.getNazwisko() < val2.getNazwisko()); });
	print_list(lista);
	lista.sort([](const osoba &val1, const osoba &val2) -> bool {return (val1.getData() < val2.getData()); });
	print_list(lista);
}



void print_list(list<osoba> &lista)
{
	list<osoba>::const_iterator i;
	for (i = lista.begin(); i != lista.end(); ++i)
		cout << *i << std::endl;
	cout << endl;
}