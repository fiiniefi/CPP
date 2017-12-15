#include "stdafx.h"
#include <random>
#include <iostream>
#include <ctime>
#include <algorithm>
#include <deque>
#include <functional>


void program();



int main()
{
	program();
}




void program()
{
	std::default_random_engine generator;
	std::normal_distribution<double> losuj(0.0, 5.0);
	std::deque<double> kolejka;
	for (int i = 0; i < 80; i++)
		kolejka.push_back(losuj(generator));
	auto predykat = [](double &val) -> bool { std::greater<double> a; std::less<double> b; return (a(val, 0) && b(val, 3)); };
	std::cout << "Ilosc dodatnich elementow mniejszych od 3 w kolekcji: " << std::count_if(kolejka.begin(), kolejka.end(), predykat) << std::endl;
	auto el = std::find_if(kolejka.begin(), kolejka.end(), predykat);
	std::cout << "Pierwszy dodatni element mniejszy od 3 w kolekcji: " << *el << std::endl;
}