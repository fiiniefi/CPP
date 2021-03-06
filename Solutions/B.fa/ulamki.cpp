#include "stdafx.h"
#include <iostream>
#include "deklaracje.h"

//for tests only

void tests();
void exception_tests();


int main()
{
	std::cout << static_cast<long long int>(INT_MAX)*static_cast<long long int>(INT_MAX) << std::endl;
	tests();
}



void tests()
{
	std::cout << obliczenia::mod(-1, 5);
	std::cout << "KONSTRUKTORY:" << std::endl;
	obliczenia::wymierna w1;
	obliczenia::wymierna w2(1);
	obliczenia::wymierna w3(1, -2);
	obliczenia::wymierna w4 = w1;
	obliczenia::wymierna w5(2, 8);
	obliczenia::wymierna w6(-3, 16);
	obliczenia::wymierna w7(114, 451);
	std::cout << "Domyslnie skonstruowany ulamek: " << w1 << std::endl;
	std::cout << "Domyslny mianownik: " << w2 << std::endl;
	std::cout << "Ujemny mianownik: " << w3 << std::endl;
	std::cout << "Konstruktor kopiujacy (przypisuje pierwszy): " << w4 << std::endl;  //asddsa
	w4 = w2;
	/*asdsa
	asadssad
	asd*/
	std::cout << "Przypisanie kopiujace (przypisuje drugi): " << w4 << std::endl;
	std::cout << "\nTESTY GETTEROW:" << std::endl;
	std::cout << "Licznik ulamka -1/2: " << w3.getNumerator() << std::endl;
	std::cout << "Mianownik ulamka -1/2: " << w3.getDenominator() << std::endl;
	std::cout << "\nTESTY KONWERSJI:" << std::endl;
	std::cout << "Ulamek -1/2 jako liczba calkowita: " << static_cast<int>(w3) << std::endl;
	std::cout << "Ulamek -1/2 jako liczba zmiennoprzecinkowa: " << static_cast<double>(w3) << std::endl;
	std::cout << "\nTESTY MODYFIKACJI ULAMKOW:" << std::endl;
	std::cout << "Zmiana znaku ulamka -1/2: " << -w3 << std::endl;
	std::cout << "Zamiana licznika z mianownikiem w ulamku -3/16: " << !w6 << std::endl;
	std::cout << "Ulamek -1/2 po operacjach: " << w3 << std::endl;
	std::cout << "\nTESTY OPERACJI ARYTMETYCZNYCH NA ULAMKACH: " << std::endl;
	std::cout << "2/8 + 114/451 = " << w5 + w7 << std::endl;
	std::cout << "-3/16 - 114/451 = " << w6 - w7 << std::endl;
	std::cout << "-3/16 * 114/451 = " << w6 * w7 << std::endl;
	std::cout << "114/451 div 2/8 = " << w7 / w5 << std::endl;
	std::cout << "\nTESTY OKRESOW:" << std::endl;
	obliczenia::wymierna o1(18333, 99900);
	obliczenia::wymierna o2(-12795, 1067);   //1457, 2867
	std::cout << "18333/99900 = " << o1 << std::endl;
	std::cout << "-12795/1067 = " << o2 << std::endl;
	exception_tests();
}


void exception_tests()
{
	obliczenia::wymierna w1;
	obliczenia::wymierna w2(0);
	obliczenia::wymierna w3(INT_MAX, 2);

	std::cout << "\nTESTY SYTUACJI WYJATKOWYCH:" << std::endl;
	try
	{
		obliczenia::wymierna sw1(1.34, 0);
	}
	catch (obliczenia::dzielenie_przez_0 exc)
	{
		std::cout << "Definiuje ulamek o mianowniku rownym 0: " << exc.what() << std::endl;
	}
	try
	{
		!w2;
	}
	catch (obliczenia::dzielenie_przez_0 exc)
	{
		std::cout << "Zamieniam licznik i mianownik miejscami, ale licznik to 0: " << exc.what() << std::endl;
	}
	try
	{
		w3 + w3;
	}
	catch (obliczenia::przekroczenie_zakresu exc)
	{
		std::cout << "W wyniku dodawania przekraczam zakres typu int od gory: " << exc.what() << std::endl;
	}
	try
	{
		(-w3) + (-w3);
	}
	catch (obliczenia::przekroczenie_zakresu exc)
	{
		std::cout << "W wyniku dodawania przekraczam zakres typu int od dolu: " << exc.what() << std::endl;
	}
	try
	{
		w3 - (-w3);
	}
	catch (obliczenia::przekroczenie_zakresu exc)
	{
		std::cout << "W wyniku odejmowania przekraczam zakres typu int od gory: " << exc.what() << std::endl;
	}
	try
	{
		(-w3) - w3;
	}
	catch (obliczenia::przekroczenie_zakresu exc)
	{
		std::cout << "W wyniku odejmowania przekraczam zakres typu int od dolu: " << exc.what() << std::endl;
	}
	try
	{
		w3 * w3;
	}
	catch (obliczenia::przekroczenie_zakresu exc)
	{
		std::cout << "W wyniku mnozenia przekraczam zakres typu int od gory: " << exc.what() << std::endl;
	}
	try
	{
		(-w3) * w3;
	}
	catch (obliczenia::przekroczenie_zakresu exc)
	{
		std::cout << "W wyniku mnozenia przekraczam zakres typu int od dolu: " << exc.what() << std::endl;
	}
	try
	{
		w3 / w3;
	}
	catch (obliczenia::przekroczenie_zakresu exc)
	{
		std::cout << "W wyniku dzielenia przekraczam zakres typu int od gory: " << exc.what() << std::endl;
	}
	try
	{
		(-w3) / (-w3);
	}
	catch (obliczenia::przekroczenie_zakresu exc)
	{
		std::cout << "W wyniku dzielenia przekraczam zakres typu int od dolu: " << exc.what() << std::endl;
	}
	try
	{
		w3 / w1;
	}
	catch (obliczenia::dzielenie_przez_0 exc)
	{
		std::cout << "W wyniku dzielenia dostaje ulamek o mianowniku rownym 0: " << exc.what() << std::endl;
	}
}