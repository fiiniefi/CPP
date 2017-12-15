#include "stdafx.h"
#include <iostream>
#include <string>
#include "wielom.hpp"

void testy_konstruktorow();
void testy_sytuacji_wyjatkowych();
void testy_operacji_arytmetycznych();
void program();

int main()
{
	testy_konstruktorow();
	testy_sytuacji_wyjatkowych();
	testy_operacji_arytmetycznych();

	program();
}


void program()
{
	std::cout << "\n\nPROGRAM:\n";
	wielomian w1;
	wielomian w2;
	double c;
	int i;
	std::cin >> w1 >> w2;
	std::cout << "Podaj stala:\n";
	std::cin >> c;
	std::cout << "Suma wielomianow: " << w1 + w2 << std::endl;
	std::cout << "Roznica wielomianow: " << w1 - w2 << std::endl;
	std::cout << "Iloczyn wielomianow: " << w1*w2 << std::endl;
	std::cout << "Wielomian*stala: " << w1*c << std::endl;
	std::cout << "Podaj indeks: ";
	std::cin >> i;
	std::cout << "Wspolczynnik sumy nr " << i << ": " << (w1 + w2)[i] << std::endl;
	std::cout << "Wskaz punkt x, w ktorym wylicze wartosc iloczynu wielomianow w1 i w2: ";
	std::cin >> c;
	std::cout << "Wartosc iloczynu wielomianow w1*w2 w punkcie " << c << ": " << (w1*w2)(c) << std::endl;
}

void testy_konstruktorow()
{
	std::cout << "TESTY KONSTRUKTOROW:\nBezargumentowy:\n";
	wielomian w1;
	std::cout << w1 << "\nwielomian(int,double):\n";
	wielomian w2(3, 2.1);
	std::cout << w2 << "\nwielomian(int, const double[]):\n";
	double tab[] = { 1.1,1.2,1.3,1.4,1.5,1.6,1.7 };
	wielomian w3(4, tab);
	std::cout << w3 << "\nwielomian(initializer_list<double>):\n";
	std::initializer_list<double> lista{ 1, 3.5, 4.2, 4.44, 3.14 };
	wielomian w4(lista);
	std::cout << w4 << "\nwielomian(const wielomian&):\n";
	wielomian w5 = w3;
	std::cout << w5 << "\noperator=(const wielomian&):\n";
	w4 = w5;
	std::cout << w4 << std::endl;
	w2 = std::move(w1);
	std::cout << "uzywam przypisania przenoszacego dla w2=w1: " << w2 << std::endl;
	wielomian w6 = std::move(w4);
	std::cout << "uzywam przypisania przenoszacego dla w6=w4: " << w6 << std::endl;
}

void testy_sytuacji_wyjatkowych()
{
	std::cout << "\n\nTESTY SYTUACJI WYJATKOWYCH:\n";
	wielomian w1(3, 0.0);
	double tab1[] = { 4.1,4.2,4.3,4.4,0 };
	wielomian w2(4, tab1);
	std::initializer_list<double> lista{ 1, 3.5, 4.2, 4.44, 0 };
	wielomian w3(lista);
	double tab2[] = { 4.1,4.2,4.3,4.4 };
	double tab3[] = { -4.1,-4.2,-4.3,-4.4 };
	wielomian w4(3, tab2);
	wielomian w5(3, tab2);
	wielomian w6(3, tab3);
	std::cout << w4 + w6;
	std::cout << std::endl;
	std::cout << w4 + w6 << std::endl << w4 - w5 << std::endl;;
	std::cout << w4 - w5;
	std::cout << std::endl;
	std::cout << w4[4] << std::endl << w4[-1] << std::endl;
	indeks_wartosc n;
	n.indeks = -1;
	n.wartosc = 5.4;
	std::cout << w4[n] << std::endl;
	n.indeks = 4;
	std::cout << w4[n] << std::endl;
	n.indeks = 3;
	n.wartosc = 0.0;

	try
	{
		w4[n];
	}
	catch (std::string komunikat)
	{
		std::cout << komunikat;
	}
}

void testy_operacji_arytmetycznych()
{
	std::cout << "\n\nTESTY OPERACJI ARYTMETYCZNYCH:\n";
	double tab1[] = { 1.2,3,4.5,3 };
	wielomian w1(3, tab1);
	std::initializer_list<double> lista{ 15.4,5.3,1.3,4.4,3.4,8.2 };
	wielomian w2(lista);

	std::cout << "w1+w2: " << w1 + w2 << std::endl;
	std::cout << "w1-w2: " << w1 - w2 << std::endl;

	double tab2[] = { 1,2,3.2 };
	double tab3[] = { 1,2.3 };

	wielomian w3(2, tab2);
	wielomian w4(1, tab3);

	std::cout << "w3*w4: " << w3*w4 << std::endl;
	std::cout << "w3*2.5: " << w3*2.5 << std::endl;
	w3 += w4;
	std::cout << "w3+=w4: " << w3 << std::endl;
	w3 -= w4 += w3;
	std::cout << "w3-=w4+=w3: " << w3 << std::endl;
	w3 *= w4;
	std::cout << "w3*=w4: " << w3 << std::endl;
	w3 *= 2.5;
	std::cout << "w3*=2.5: " << w3 << std::endl;
	std::cout << "wartosc w3 w punkcie 1.5: " << w3(1.5) << std::endl;
	std::cout << "wspolczynnik w3 przy x^2: " << w3[2] << std::endl;
	indeks_wartosc n;
	n.indeks = 2;
	n.wartosc = -14;
	std::cout << "zamieniam wspolczynnik w3 przy x^2 na -14:  " << w3[n] << std::endl;
	std::cout << "i sprawdzam, czy zostalo: " << w3[2] << std::endl;
}