#include "stdafx.h"
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include "deklaracje.h"

using namespace wyr;

void costam();
void drzewa();


int main()
{
	drzewa();
	costam();
}


void drzewa()
{
	wyrazenie *w1 = new podziel(new pomnoz(new odejmij(new zmienna("x"), new liczba(1)), new zmienna("x")), new liczba(2));
	wyrazenie *w2 = new podziel(new dodaj(new liczba(3), new liczba(5)), new dodaj(new pomnoz(new liczba(2), new zmienna("x")), new liczba(7)));
	wyrazenie *w3 = new odejmij(new dodaj(new liczba(2), new pomnoz(new zmienna("x"), new liczba(7))), new dodaj(new pomnoz(new zmienna("y"), new liczba(3)), new liczba(5)));
	wyrazenie *w4 = new podziel(new wyr::cos(new pomnoz(new dodaj(new zmienna("x"), new liczba(1)), new zmienna("x"))), new poteguj(new e(), new poteguj(new zmienna("x"), new liczba(2))));
	std::cout << w1->opis() << std::endl << w2->opis() << std::endl << w3->opis() << std::endl << w4->opis() << std::endl;

	for (double i = 0; i < 1.01; i += 0.01)
	{
		zmienna::set("x", i);
		zmienna::set("y", 1 + i);
		std::cout << "i = " << i << std::endl;
		std::cout << "w1 = " << w1->oblicz() << std::endl;
		std::cout << "w2 = " << w2->oblicz() << std::endl;
		std::cout << "w3 = " << w3->oblicz() << std::endl;
		std::cout << "w4 = " << w4->oblicz() << std::endl;
	}
}



void costam()
{
	zmienna var1("x");
	zmienna var2("y", 4);
	zmienna var3("x", 15);
	std::cout << var2.oblicz() << std::endl;
	zmienna::set("x", 20);
	std::cout << var3.opis() << "=" << var3.oblicz() << std::endl;
	pi *p = new pi();
	std::cout << p->opis() << "=" << p->oblicz() << std::endl;
	std::cout << p->getPriority() << std::endl;
	wyr::sin s(new liczba(1));
	std::cout << s.opis() << "=" << s.oblicz() << "   " << s.getPriority() << std::endl;


	wyrazenie *w1 = new podziel(new liczba(3), new liczba(0));

	try
	{
		w1->oblicz();
	}
	catch (divide_by_zero_exception mess)
	{
		std::cout << mess.what() << std::endl;
	}

	zmienna var4("z");
	try
	{
		var4.oblicz();
	}
	catch (unset_value mess)
	{
		std::cout << mess.what() << std::endl;
	}

	wyrazenie *w = new odejmij(
		new pi(),
		new dodaj(
			new liczba(2),
			new pomnoz(
				new zmienna("x"),
				new liczba(7)
			)
		)
	);	std::cout << w->opis() << std::endl;
}