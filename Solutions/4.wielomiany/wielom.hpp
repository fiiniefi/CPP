#ifndef WIELOMIAN_H
#define WIELOMIAN_H
#include "stdafx.h"
#include <iostream>

struct indeks_wartosc
{
	int indeks;
	double wartosc;
};


class wielomian
{
private:
	int stopien;
	double *wspolczynniki;
	
public:
	wielomian(int st = 0, double wsp = 1.0);
	wielomian(int st, const double wsp[]);
	wielomian(std::initializer_list<double> wsp);
	wielomian(const wielomian &w);
	wielomian(wielomian &&w);
	wielomian& operator=(const wielomian &w);
	wielomian& operator=(wielomian &&w);
	~wielomian();

	wielomian& operator+=(const wielomian &v);
	wielomian& operator-=(const wielomian &v);
	wielomian& operator*=(const wielomian &v);
	wielomian& operator*=(double c);
	double operator()(double x) const; // obliczenie wartoœci wielomianu w x-sie
	double operator[](int i) const; // odczytanie i-tego wspó³czynnika
	double operator[](indeks_wartosc acc) const; //zapisanie do i-tego indeksu wartosci typu double

	int get_stopien();

	friend std::istream& operator>>(std::istream &we, wielomian &w);
	friend std::ostream& operator<<(std::ostream &wy, const wielomian &w);
	friend wielomian operator+(const wielomian &u, const wielomian &v);
	friend wielomian operator-(const wielomian &u, const wielomian &v);
	friend wielomian operator*(const wielomian &u, const wielomian &v);
	friend wielomian operator*(const wielomian &u, double c);	friend int stopien_plus(const wielomian &u, const wielomian &v);
	friend int stopien_minus(const wielomian &u, const wielomian &v);
	friend double* policz_wspolczynniki_suma(const wielomian &u, const wielomian &v, int st);
	friend double* policz_wspolczynniki_roznica(const wielomian &u, const wielomian &v, int st);
	friend double* policz_wspolczynniki_iloczyn(const wielomian &u, const wielomian &v, int st);
};

#endif WIELOMIAN_H