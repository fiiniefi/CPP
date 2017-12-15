#include "stdafx.h"
#include <iostream>
#include <string>
#include <cstdlib>

const int B[] = { 9000, 5000, 4000, 1000,
900, 500, 400, 100,
90, 50, 40, 10,
9, 5, 4, 1 };

const std::string R[] = { "|XC|", "|L|", "|XL|", "M",
"CM", "D", "CD", "C",
"XC", "L", "XL", "X",
"IX", "V", "IV", "I" };


int arab2bin(const char *x);
std::string bin2rzym(int x);


int main(int argc, char *argv[])
{
	for (int i = 1; i < argc; i++)
	{
		std::cout << argv[i] << "    ";
		int n = arab2bin(argv[i]);
		if (n == 0)
			continue;
		std::cout << bin2rzym(n) << std::endl;
	}
	system("pause");
}


int arab2bin(const char *x)
{
	if (x == '\0')
	{
		std::cerr << "Err: Liczba jest pusta" << std::endl;
		return 0;
	}

	if (x[0] == '0')
	{
		std::cerr << "Err: 0 na pierwszej pozycji" << std::endl;
		return 0;
	}

	int i;
	for (i = 0; x[i] != 0; i++)
		if (x[i]<'0' || x[i]>'9')
		{
			std::cerr << "Err: Bledny zapis liczby" << std::endl;
			return 0;
		}

	if (i >= 5)
	{
		std::cerr << "Err: Zbyt dluga liczba" << std::endl;
		return 0;
	}

	std::string liczba = x;
	return stoi(liczba);
}


std::string bin2rzym(int x)
{
	std::string rome="";
	for (int i = 0; i < 16 && x > 0; i++)
	{
		if (x >= B[i])
		{
			rome += R[i];
			x -= B[i];
			i--;
		}
	}
	return rome;
}