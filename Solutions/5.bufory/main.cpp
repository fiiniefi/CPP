#include "stdafx.h"
#include <iostream>
#include <string>
#include "struktury_danych.h"

void testy_listy();
void testy_kolejki();
void testy_stosu();


int main()
{
	testy_kolejki();
	testy_stosu();
	testy_listy();
}


void testy_kolejki()
{
	std::cout << "\n\nTESTY KOLEJKI:\n\n";
	kolejka k;
	std::cout << "rozmiar kolejki: " << k.ile() << std::endl;
	k.wstaw(4.5);
	k+=(3.4);
	std::cout << "element pierwszy do zdjecia: " << k.gotowy() << std::endl;
	std::cout << "zdejmuje: " << --k << std::endl;
	k += 2.1;
	std::cout << "element pierwszy do zdjecia: " << *k << std::endl;
	std::cout << "rozmiar kolejki: " << k.ile() << std::endl;
}


void testy_stosu()
{
	std::cout << "\n\nTESTY STOSU:\n\n";
	stos s;
	std::cout << "rozmiar stosu: " << s.ile() << std::endl;
	s.wstaw(4.44);
	s += 3.33;
	s += 1.23;
	std::cout << "element pierwszy do zdjecia: " << s.gotowy() << std::endl;
	std::cout << "zdejmuje: " << --s << std::endl;
	s += 23.33;
	s += 2.21;
	s.wstaw(3142.2124);
	std::cout << "element pierwszy do zdjecia: " << *s << std::endl;
	std::cout << "rozmiar stosu: " << s.ile() << std::endl;
}


void testy_listy()
{
	std::cout << "\n\nTESTY LISTY:\n\n";
	lista l;
	l.wstaw(1, 3.5);
	l.wstaw(0, 10.2);
	l.wstaw(2, 8.1);
	std::cout << l.usun(1);
	std::cout << "  " << l.usun(1);
	std::cout << "   " << l.usun(0) << "\n";
	l.wstaw(0, 1.44);
	l.wstaw(0, 44.1);
	std::cout << "Lista l w chwili obecnej: ";
	std::cout << l << "\n";
	lista l2 = l;
	std::cout << "Lista l2 zainicjalizowana lista l: " << l2 << "\n";
	lista l3 = std::move(l2);
	std::cout << "Lista l2 przeniesiona do l3: " << l3 << "\n";
	std::cout << "Dodaje do l 3.12 i 4.13. Nastepnie przypisuje ja liscie l3: ";
	l.wstaw(5, 3.12);
	l.wstaw(1, 4.13);
	l3 = l;
	std::cout << l3 << std::endl;
	std::cout << "Rozmiar l3: " << l3.getSize() << std::endl;
	std::cout << "Trzeci element l3: " << l3[2] << std::endl;
	std::cout << "Wczytuje przeladowanym operatorem >> do l3: ";
	std::cin >> l3;
	std::cout << l3 << std::endl;
}