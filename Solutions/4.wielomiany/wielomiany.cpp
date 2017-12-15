#include "stdafx.h"
#include <iostream>
#include <string>
#include <algorithm>
#include "wielom.hpp"

//zamiast std::cerr wolalbym wyjatki, no ale specyfikacja

wielomian::wielomian(int st, double wsp)
{
	if (wsp == 0 && st != 0)
	{
		std::cerr << "wielomian(int,double): Wspolczynnik przy najwyzszej potedze rowny 0!\n";
		return;
	}
	this->stopien = st;
	this->wspolczynniki = new double[st + 1];
	this->wspolczynniki[st] = wsp;
	for (int i = 0; i < st; i++)
		wspolczynniki[i] = 0;
}

wielomian::wielomian(int st, const double wsp[])
{
	if (wsp[st] == 0)
	{
		std::cerr << "wielomian(int, const double[]): Wspolczynnik przy najwyzszej potedze rowny 0!\n";
		return;
	}
	this->stopien = st;
	this->wspolczynniki = new double[st + 1];
	for (int i = 0; i <= st; i++)
		this->wspolczynniki[i] = wsp[i];
}

wielomian::wielomian(std::initializer_list<double> wsp)
{
	if (*(wsp.end() - 1) == 0)
	{
		std::cerr << "wielomian(initializer_list<double>): Wspolczynnik przy najwyszej potedze rowny 0!\n";
		return;
	}
	this->stopien = wsp.size() - 1;
	this->wspolczynniki = new double[this->stopien + 1];
	int i = 0;
	for (auto iterator = wsp.begin(); iterator != wsp.end(); iterator++, i++)
		this->wspolczynniki[i] = *iterator;
}

wielomian::wielomian(const wielomian &w)
{
	this->stopien = w.stopien;
	this->wspolczynniki = new double[this->stopien + 1];
	for (int i = 0; i <= this->stopien; i++)
		this->wspolczynniki[i] = w.wspolczynniki[i];
}

wielomian::wielomian(wielomian &&w)
{
	this->stopien = w.stopien;
	this->wspolczynniki = w.wspolczynniki;
	w.wspolczynniki = nullptr;
}

wielomian& wielomian::operator=(const wielomian &w)
{
	this->~wielomian();

	this->stopien = w.stopien;
	this->wspolczynniki = new double[this->stopien + 1];
	for (int i = 0; i <= this->stopien; i++)
		this->wspolczynniki[i] = w.wspolczynniki[i];
	return *this;
}

wielomian& wielomian::operator=(wielomian &&w)
{
	this->~wielomian();
	
	this->stopien = w.stopien;
	this->wspolczynniki = w.wspolczynniki;
	w.wspolczynniki = nullptr;
	return *this;
}

wielomian::~wielomian()
{
	delete[] this->wspolczynniki;
}


std::istream& operator>>(std::istream &we, wielomian &w)
{
	while (!(we >> w.stopien) || w.stopien <= 0)
	{
		we.clear();
		we.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	w.~wielomian();
	w.wspolczynniki = new double[w.stopien + 1];
	for (int i = 0; i <= w.stopien; i++)
		we >> w.wspolczynniki[i];
	return we;
}

std::ostream& operator<<(std::ostream &wy, const wielomian &w)
{
	wy << w.wspolczynniki[w.stopien] << "x^" << w.stopien;
	for (int i = w.stopien-1; i >= 0; i--)
	{
		wy << ' ' << std::showpos << w.wspolczynniki[i] << "x^" << std::noshowpos << i;
	}
	return wy;
}

wielomian operator+(const wielomian &u, const wielomian &v)
{
	int st = stopien_plus(u, v);
	if (st < 0)
	{
		std::cerr << "operator+(wielomian,wielomian): Wielomiany sa przeciwne!\n";
		wielomian w(0, 0.0);
		return w;
	}

	double *wsp = policz_wspolczynniki_suma(u, v, st);
	wielomian w(st, wsp);
	delete[] wsp;
	return w;
}

wielomian operator-(const wielomian &u, const wielomian &v)
{
	int st = stopien_minus(u, v);
	if (st < 0)
	{
		std::cerr << "operator-(wielomian,wielomian): Wielomiany sa identyczne!\n";
		return u;
	}

	double *wsp = policz_wspolczynniki_roznica(u, v, st);
	wielomian w(st, wsp);
	delete[] wsp;
	return w;
}

wielomian operator*(const wielomian &u, const wielomian &v)
{
	int st = u.stopien + v.stopien;
	double *wsp = policz_wspolczynniki_iloczyn(u, v, st);

	wielomian w(st, wsp);
	delete[] wsp;
	return w;
}

wielomian operator*(const wielomian &u, double c)
{
	wielomian w = u;
	for (int i = 0; i <= w.stopien; i++)
		w.wspolczynniki[i] *= c;
	return w;
}

wielomian& wielomian::operator+=(const wielomian &v)
{
	int st = stopien_plus(*this, v);
	if (st < 0)
	{
		std::cerr << "operator+(wielomian): Wielomiany sa przeciwne!\n";
		return *this;
	}

	double *wsp = policz_wspolczynniki_suma(*this, v, st);
	*this = wielomian(st, wsp);
	delete[] wsp;
	return *this;
}

wielomian& wielomian::operator-=(const wielomian &v)
{
	int st = stopien_minus(*this, v);
	if (st < 0)
	{
		std::cerr << "operator-(wielomian): Wielomiany sa identyczne!\n";
		return *this;
	}

	double *wsp = policz_wspolczynniki_roznica(*this, v, st);
	*this = wielomian(st, wsp);
	delete[] wsp;
	return *this;
}

wielomian& wielomian::operator*=(const wielomian &v)
{
	int st = this->stopien + v.stopien;
	double *wsp = policz_wspolczynniki_iloczyn(*this, v, st);

	*this = wielomian(st, wsp);
	delete[] wsp;
	return *this;
}

wielomian& wielomian::operator*=(double c)
{
	for (int i = 0; i <= this->stopien; i++)
		this->wspolczynniki[i] *= c;
	return *this;
}

double wielomian::operator()(double x) const
{
	if (this->stopien == 0)
		return this->wspolczynniki[0];
	double wynik = x*this->wspolczynniki[this->stopien] + this->wspolczynniki[this->stopien - 1];
	for (int i = this->stopien-2; i >= 0; i--)
		wynik = wynik*x + this->wspolczynniki[i];
	return wynik;
}

double wielomian::operator[](int i) const
{
	if (i > this->stopien || i < 0)
	{
		std::cerr << "operator[](int): Bledny indeks!\n";
		return NAN;
	}

	return this->wspolczynniki[i];
}

double wielomian::operator[](indeks_wartosc acc) const
{
	if (acc.indeks > this->stopien || acc.indeks < 0)
	{
		std::cerr << "operator[](indeks_wartosc): Bledny indeks!\n";
		return NAN;
	}

	else if (acc.indeks == this->stopien && acc.wartosc == 0 && this->stopien != 0)
		throw std::string("operator[](indeks_wartosc): Nie moge przypisac wspolczynnika 0 najwyzszej potedze!\n");

	return (this->wspolczynniki[acc.indeks] = acc.wartosc);
}

int wielomian::get_stopien() //brzmi slabo, ale konwencja gettera wymaga
{
	return this->stopien;
}


int stopien_plus(const wielomian &u, const wielomian &v)
{
	int st = std::max(u.stopien, v.stopien);

	if (u.stopien == v.stopien)
		while (st >= 0 && (u.wspolczynniki[st] + v.wspolczynniki[st] == 0))
			st--;
	return st;
}

int stopien_minus(const wielomian &u, const wielomian &v)
{
	int st = std::max(u.stopien, v.stopien);

	if (u.stopien == v.stopien)
		while (st >= 0 && (u.wspolczynniki[st] - v.wspolczynniki[st] == 0))
			st--;
	return st;
}

double* policz_wspolczynniki_suma(const wielomian &u, const wielomian &v, int st)
{
	double *wsp = new double[st + 1];
	int i;
	for (i = 0; i <= u.stopien && i <= v.stopien && i <= st; i++)
		wsp[i] = u.wspolczynniki[i] + v.wspolczynniki[i];
	if (u.stopien > v.stopien)
		for (;i <= u.stopien && i <= st;i++)
			wsp[i] = u.wspolczynniki[i];

	else if (v.stopien > u.stopien)
		for (;i <= v.stopien && i <= st;i++)
			wsp[i] = v.wspolczynniki[i];
	return wsp;
}

double* policz_wspolczynniki_roznica(const wielomian &u, const wielomian &v, int st)
{
	double *wsp = new double[st + 1];
	int i;
	for (i = 0; i <= u.stopien && i <= v.stopien && i <= st; i++)
		wsp[i] = u.wspolczynniki[i] - v.wspolczynniki[i];
	if (u.stopien > v.stopien)
		for (;i <= u.stopien && i <= st; i++)
			wsp[i] = u.wspolczynniki[i];

	else if (v.stopien > u.stopien)
		for (;i <= v.stopien && i <= st; i++)
			wsp[i] = v.wspolczynniki[i] * (-1);
	return wsp;
}

double* policz_wspolczynniki_iloczyn(const wielomian &u, const wielomian &v, int st)
{
	double *wsp = new double[st + 1];
	for (int i = 0; i <= st; i++)
		wsp[i] = 0;

	for (int i = 0; i <= u.stopien; i++)
		for (int j = 0; j <= v.stopien; j++)
			wsp[i + j] += u.wspolczynniki[i] * v.wspolczynniki[j];
	return wsp;
}