#include "stdafx.h"
#include <random>
#include <iostream>
#include <ctime>
#include <functional>
#include <fstream>
#include <list>
#include <algorithm>

int program1();
void program2(int k);


int main()
{
	program2(program1());
}


int program1()
{
	std::mt19937 generator(time(0));
	auto generate = std::bind(std::uniform_int_distribution<int>(0, 1000), std::mt19937(generator));
	int k = generate();
	int n = generate();
	std::ofstream plik;
	plik.open("ciag.txt");
	plik << n << '\n';
	std::cout << k << std::endl;
	std::binomial_distribution<unsigned int> losuj(k);
	for (int i = 0; i < n; i++)
		plik << losuj(generator) << '\n';
	plik.close();
	return k;
}

void program2(int k)
{
	std::ifstream plik;
	plik.open("ciag.txt");
	if (!plik.is_open())
		return;
	std::list<int> lista;
	int n;
	plik >> n;
	for (int i = 0; i < n; i++)
	{
		int el;
		plik >> el;
		lista.push_back(el);
	}
	plik.close();
	int tab[3]{ k, 0 };
	std::for_each(lista.begin(), lista.end(), [&tab](const int &n) { if (n < tab[0]) tab[0] = n; if (n > tab[1]) tab[1] = n; tab[2] += n; });
	std::cout << "Wartosc minimalna kolekcji: " << tab[0] << "\nWartosc maksymalna kolekcji: " << tab[1] << "\nWartosc srednia kolekcji: " << tab[2] / lista.size() << std::endl << std::endl;
}