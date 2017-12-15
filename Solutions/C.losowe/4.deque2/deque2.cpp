#include "stdafx.h"
#include <random>
#include <iostream>
#include <ctime>
#include <algorithm>
#include <deque>


void program();


int main()
{
	program();
}



void program()
{
	std::mt19937 generator(time(0));
	std::binomial_distribution<unsigned int> losuj(10);
	std::deque<int> kolejka;
	for (int i = 0; i < 80; i++)
		kolejka.push_back(losuj(generator));
	std::remove_if(kolejka.begin(), kolejka.end(), [](const int &val) -> bool { return (val < 2 || val > 8); });
	std::cout << std::count_if(kolejka.begin(), kolejka.end(), [](int val) -> bool { return ((val > 4) && (val < 6)); }) << std::endl;
}