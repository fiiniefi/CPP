#include "stdafx.h"
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include "deklaracje.h"


obliczenia::wymierna::wymierna(int licz, int mian) throw(dzielenie_przez_0)
{
	if (mian == 0)
		throw dzielenie_przez_0("wymierna(int,int): Zero in denominator!\n");

	else if (mian < 0)
	{
		mian *= -1;
		licz *= -1;
	}

	if (licz != 0)
	{
		int dzielnik;
		if (mian == 1)
			dzielnik = 1;
		else
			dzielnik = nwd(std::abs(licz), mian);
		licz /= dzielnik;
		mian /= dzielnik;
	}

	this->licznik = licz;
	this->mianownik = mian;
}


obliczenia::wymierna::wymierna(const wymierna &pattern) noexcept
{
	this->licznik = pattern.licznik;
	this->mianownik = pattern.mianownik;
}


obliczenia::wymierna& obliczenia::wymierna::operator=(const wymierna &pattern) noexcept
{
	this->licznik = pattern.licznik;
	this->mianownik = pattern.mianownik;
	return *this;
}


int obliczenia::wymierna::getNumerator() const noexcept
{
	return this->licznik;
}


int obliczenia::wymierna::getDenominator() const noexcept
{
	return this->mianownik;
}


obliczenia::wymierna obliczenia::operator-(const wymierna &pattern) noexcept
{
	return wymierna(pattern.licznik*(-1), pattern.mianownik);
}


obliczenia::wymierna obliczenia::operator!(const wymierna &pattern) throw(dzielenie_przez_0)
{
	if (pattern.licznik == 0)
		throw dzielenie_przez_0("operator!(): Zero in denominator!\n");
	
	wymierna w(pattern.mianownik, pattern.licznik);

	if (w.mianownik < 0)
	{
		w.licznik *= -1;
		w.mianownik *= -1;
	}

	return w;
}


obliczenia::wymierna::operator int() noexcept
{
	return this->licznik / this->mianownik;
}


obliczenia::wymierna::operator double() noexcept
{
	return static_cast<double>(this->licznik) / static_cast<double>(this->mianownik);
}


const obliczenia::wymierna obliczenia::operator+(const wymierna &first, const wymierna &second) throw(przekroczenie_zakresu)
{
	int mult;

	try
	{
		mult = nww(first.mianownik, second.mianownik);
	}
	catch (przekroczenie_zakresu mess)
	{
		std::string messstr = "operator+(wymierna&, wymierna&): " + static_cast<std::string>(mess.what());
		throw przekroczenie_zakresu(messstr);
	}

	int multfirst = mult / first.mianownik;
	int multsecond = mult / second.mianownik;

	if ((((static_cast<long long int>(first.licznik) * multfirst) + (static_cast<long long int>(second.licznik) * multsecond)) > INT_MAX) || 
	(((static_cast<long long int>(first.licznik) * multfirst) + (static_cast<long long int>(second.licznik) * multsecond)) < INT_MIN))
		throw przekroczenie_zakresu("operator+(wymierna&, wymierna&): Result is too big!\n");
	
	int newnum = (first.licznik * multfirst) + (second.licznik * multsecond);
	return wymierna(newnum, mult);
}


const obliczenia::wymierna obliczenia::operator-(const wymierna &first, const wymierna &second) throw(przekroczenie_zakresu)
{
	int mult;

	try
	{
		mult = nww(first.mianownik, second.mianownik);
	}
	catch (przekroczenie_zakresu mess)
	{
		std::string messstr = "operator-(wymierna&, wymierna&): " + static_cast<std::string>(mess.what());
		throw przekroczenie_zakresu(messstr);
	}

	int multfirst = mult / first.mianownik;
	int multsecond = mult / second.mianownik;

	if ((((static_cast<long long int>(first.licznik) * multfirst) - (static_cast<long long int>(second.licznik) * multsecond)) > INT_MAX) ||
	(((static_cast<long long int>(first.licznik) * multfirst) - (static_cast<long long int>(second.licznik) * multsecond)) < INT_MIN))
		throw przekroczenie_zakresu("operator-(wymierna&, wymierna&): Result is too big!\n");

	int newnum = (first.licznik * multfirst) - (second.licznik * multsecond);
	return wymierna(newnum, mult);
}


const obliczenia::wymierna obliczenia::operator*(const wymierna &first, const wymierna &second) throw(przekroczenie_zakresu)
{
	if (((static_cast<long long int>(first.licznik) * static_cast<long long int>(second.licznik)) > INT_MAX) ||
	(static_cast<long long int>(first.licznik) * static_cast<long long int>(second.licznik) < INT_MIN) ||
	(static_cast<long long int>(first.mianownik) * static_cast<long long int>(second.mianownik) > INT_MAX))
		throw przekroczenie_zakresu("operator*(wymierna&, wymierna&): Result is too big!\n");

	return wymierna((first.licznik * second.licznik), (first.mianownik * second.mianownik));
}


const obliczenia::wymierna obliczenia::operator/(const wymierna &first, const wymierna &second) throw(przekroczenie_zakresu, dzielenie_przez_0)
{
	if (((static_cast<long long int>(first.licznik) * static_cast<long long int>(second.mianownik)) > INT_MAX) ||     //zakresy...
	(static_cast<long long int>(first.licznik) * static_cast<long long int>(second.mianownik) < INT_MIN) ||
	(static_cast<long long int>(first.mianownik) * static_cast<long long int>(second.licznik) > INT_MAX) ||
	(static_cast<long long int>(first.mianownik) * static_cast<long long int>(second.licznik) < INT_MIN))
		throw przekroczenie_zakresu("operator/(wymierna&, wymierna&): Result is too big!\n");
	else if ((first.mianownik * second.licznik) == 0)
		throw dzielenie_przez_0("operator/(wymierna&, wymierna&): Zero in denominator!\n");

	int newnum = first.licznik * second.mianownik;
	int newden = first.mianownik * second.licznik;

	if (newden < 0)
	{
		newnum *= -1;
		newden *= -1;
	}

	return wymierna(newnum, newden);
}






int obliczenia::nwd(int a, int b) noexcept
{
	while (b != 0)
	{
		int r = a % b;
		a = b;
		b = r;
	}

	return a;
}


int obliczenia::nww(int a, int b) throw(przekroczenie_zakresu)
{
	long long int mult = (static_cast<long long int>(a)) * (static_cast<long long int>(b));
	mult /= obliczenia::nwd(a, b);

	if (mult > INT_MAX)
		throw przekroczenie_zakresu("Result is too big!\n");

	else
		return static_cast<int>(mult);
}


bool obliczenia::isPeriod(int a) noexcept
{
	if (a == 1)
		return false;

	if ((a % 2 == 0) || (a % 5 == 0))
	{
		while ((a % 2 == 0) || (a % 5 == 0))
		{
			if (a % 2 == 0)
				a /= 2;
			else
				a /= 5;
		}

		if (a == 1)
			return false;
		else
			return true;
	}
	
	return true;
}


std::string obliczenia::make(int a, int b) noexcept
{
	std::vector<int> modulos;
	std::vector<char> numbers;
	int calk = a / b;
	modulos.push_back(a = abs(a) % b);
	
	std::string res = std::to_string(calk)+'.';

	while (true)
	{
		if (a < b)
			a *= 10;
		numbers.push_back(a / b + '0');

		for (unsigned int i = 0; i < modulos.size(); i++)   //poczatkowy wyraz
		{
			for (unsigned int j = 1; j <= modulos.size() / 2; j++)    //ilosc wyrazow
			{
				if (i + j + j - 1 < modulos.size())          //sprawdzam, czy nie wyskocze poza tablice sprawdzajac okres. warunek sprawdza, czy ostatnia cyfra drugiej czesci nie jest poza tablica
				{
					int k = modulos.size() - 2 * j; //idea k to pominiêcie operacji zrobionych poprzednio

					for (int p = k; ; p++)    
					{
						if (modulos[p] != modulos[p + j])
							break;
						if (p == k + j - 1)
						{
							for (unsigned int h = 0; h < numbers.size() - j; h++)
							{
								if (h == k)   //bo "najnowsze" modulo wygeneruje jakby kolejna liczbe po przecinku, nie generuje tej "wpisywanej" w danym kroku
									res += '(';
								res += numbers[h];
							}
							res += ')';
							return res;
						}
					}
				}
			}
		}

		modulos.push_back(a = mod(a,b));
	}
}


int obliczenia::mod(int a, int b) noexcept   //z internetu
{
	const int result = a % b;
	return result >= 0 ? result : result + b;
}


std::ostream& obliczenia::operator<<(std::ostream &output, const obliczenia::wymierna &pattern) noexcept
{
	if (!isPeriod(pattern.mianownik))
	{
		std::string res = std::to_string((pattern.licznik) / (pattern.mianownik*1.0));
		res.erase(res.find_last_not_of('0') + 1, std::string::npos);
		res.erase(res.find_last_not_of('.') + 1, std::string::npos);
		return output << res;
	}
	else
		return output << make(pattern.licznik, pattern.mianownik);
}