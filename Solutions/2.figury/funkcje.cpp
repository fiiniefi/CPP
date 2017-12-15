#include "stdafx.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include "deklaracje.h"


punkt::punkt()
{
	this->x = 0;
	this->y = 0;
}


punkt::punkt(const double a, const double b)
{
	this->x = a;
	this->y = b;
}


punkt::punkt(const punkt &pattern)
{
	this->x = pattern.x;
	this->y = pattern.y;
}


punkt& punkt::operator=(const punkt &pattern)
{
	if (*this == pattern)
		return *this;
	this->~punkt();
	this->x = pattern.x;
	this->y = pattern.y;

	return *this;
}


bool punkt::operator==(const punkt &pattern)
{
	if (this->x == pattern.x && this->y == pattern.y)
		return 1;
	else
		return 0;
}


void punkt::move(const double x, const double y)
{
	this->x += x;
	this->y += y;
}


void punkt::rotation(const double x, const double y, const double alpha)
{
	this->x = (((this->x - x) * cos(alpha / 180)) - ((this->y - y) * sin(alpha / 180)) + x);
	this->y = (((this->x - x) * sin(alpha / 180)) + ((this->y - y) * cos(alpha / 180)) + y);
}


std::ostream& operator<<(std::ostream &output, const punkt &pattern)
{
	return output << "(" << pattern.x << "," << pattern.y << ")";
}






odcinek::odcinek(punkt a, punkt b)
{
	if (a.x == b.x && a.y == b.y)
		throw std::string("Blad: Nie mozna utworzyc odcinka o zerowej dlugosci!\n");
	this->a = a;
	this->b = b;
}


odcinek::odcinek(const odcinek &pattern)
{
	this->a = pattern.a;
	this->b = pattern.b;
}


odcinek& odcinek::operator=(const odcinek &pattern)
{
	if (*this == pattern)
		return *this;
	this->~odcinek();
	this->a = pattern.a;
	this->b = pattern.b;

	return *this;
}


bool odcinek::operator==(const odcinek &pattern)
{
	if (this->a == this->b)
		return 1;
	else
		return 0;
}


void odcinek::move(const double x, const double y)
{
	this->a.move(x, y);
	this->b.move(x, y);
}


void odcinek::rotation(const double x, const double y, const double alpha)
{
	this->a.rotation(x, y, alpha);
	this->b.rotation(x, y, alpha);
}


double odcinek::length()
{
	double d = (this->b.x - this->a.x)*(this->b.x - this->a.x) + (this->b.y - this->a.y)*(this->b.y - this->a.y);
	if (d < 0)
		d += -1;
	return sqrt(d);
}


bool odcinek::onSegment(const punkt c) const
{
	//ponizszy algorytm sprawdza, czy punkty sa wspolliniowe. jesli tak - jego wartosc jest rowna 0. wzor wyprowadzony z wyznacznika macierzy kwadratowej
	if (((this->a.x*this->b.y + this->a.y*c.x + this->b.x*c.y) - (this->b.y*c.x) - (this->a.x*c.y) - (this->a.y*this->b.x)) != 0)
		return 0;
	if ((std::min(this->a.x, this->b.x) <= c.x) && (std::max(this->a.x, this->b.x) >= c.x ))  //min(x1,x2)<=x3<=max(x1,x2)
		if ((std::min(this->a.y, this->b.y) <= c.y) && (std::max(this->a.y, this->b.y) >= c.y))  //min(y1,y2)<=y3<=max(y1,y2)
			return 1;
	return 0;
}


punkt odcinek::midpoint()
{
	punkt a = punkt(((this->a.x + this->b.x) / 2), ((this->a.y + this->b.y) / 2));
	return a;
}


punkt odcinek::intercept(const odcinek compared)
{
	//ponizej jakis dlugi wzor z wikipedii na punkt wspolny. wzor nie uwzglednia rownoleglych prostych, w tym identycznych
	//double xl = (((this->a.x*this->b.y - this->a.y*this->b.x) * (compared.a.x - compared.b.x)) - ((this->a.x - this->b.x) * (compared.a.x * compared.b.y - compared.a.y * compared.b.x)));
	//double yl = (((this->a.x*this->b.y - this->a.y*this->b.x) * (compared.a.y - compared.b.y)) - ((this->a.y - this->b.y) * (compared.a.x * compared.b.y - compared.a.y * compared.b.x)));
	//double xym = (((this->a.x - this->b.x)*(compared.a.y - compared.b.y)) - ((this->a.y - this->b.y) * (compared.a.x - compared.b.x)));

	double athis = factor(this->a, this->b);
	double acompared = factor(compared.a, compared.b);
	
	if (athis == INFINITY || acompared == INFINITY)
	{
		if ((this->a.y == compared.a.y))
			throw std::string("Odcinki nie przecinaja sie w konkretnym punkcie!\n");
	}

	if (athis == acompared)
		throw std::string("Odcinki nie przecinaja sie w konkretnym punkcie!\n");

	double bthis = (-1)*(athis*this->a.x) + this->a.y;
	double bcompared = (-1)*(acompared*compared.a.x) + compared.a.y;


	double przecx = (bcompared - bthis) / (athis - acompared);
	double przecy = (athis*przecx) + bthis;

	punkt point = punkt(przecx, przecy);
	//if (this->onSegment(point)==0 || compared.onSegment(point) == 0)
		//throw std::string("Nie istnieje punkt przeciecia!\n");
	return point;
}


std::ostream& operator<<(std::ostream &output, const odcinek &pattern)
{
	return output << "Punkt a: " << pattern.a << ", Punkt b: " << pattern.b << "\n";
}





trojkat::trojkat(punkt a, punkt b, punkt c)
{
	//ponizszy algorytm sprawdza, czy punkty sa wspolliniowe. jesli tak - jego wartosc jest rowna 0. wzor wyprowadzony z wyznacznika macierzy kwadratowej
	if (((a.x*b.y + a.y*c.x + b.x*c.y) - (b.y*c.x) - (a.x*c.y) - (a.y*b.x)) == 0)
		throw std::string("Nie mozna utworzyc trojkata - punkty sa wspolliniowe!\n");
	this->a = a;
	this->b = b;
	this->c = c;
}


trojkat::trojkat(const trojkat &pattern)
{
	this->a = pattern.a;
	this->b = pattern.b;
	this->c = pattern.c;
}


trojkat& trojkat::operator=(const trojkat &pattern)
{
	if (*this == pattern)
		return *this;
	this->~trojkat();
	this->a = pattern.a;
	this->b = pattern.b;
	this->c = pattern.c;

	return *this;
}


bool trojkat::operator==(const trojkat &pattern)
{
	if ((this->a == this->b) && (this->b == this->c))
		return 1;
	else
		return 0;
}


void trojkat::move(const double x, const double y)
{
	this->a.move(x, y);
	this->b.move(x, y);
	this->c.move(x, y);
}


void trojkat::rotation(const double x, const double y, const double alpha)
{
	this->a.rotation(x, y, alpha);
	this->b.rotation(x, y, alpha);
	this->c.rotation(x, y, alpha);
}


double trojkat::circuit()
{
	odcinek a = odcinek(this->a, this->b);
	odcinek b = odcinek(this->b, this->c);
	odcinek c = odcinek(this->a, this->c);

	return (a.length() + b.length() + c.length());
}


double trojkat::area()
{
	//z wzoru Herona
	odcinek ao = odcinek(this->a, this->b);
	odcinek bo = odcinek(this->b, this->c);
	odcinek co = odcinek(this->a, this->c);

	double a = ao.length();
	double b = bo.length();
	double c = co.length();
	double p = this->circuit() / 2;

	return sqrt((p* (p - a)*(p - b)*(p - c)));
}


bool trojkat::isInside(punkt in)
{
	double afirst = factor(this->a, this->b);
	double asecond = factor(this->b, this->c);
	double athird = factor(this->a, this->c);

	if (afirst == INFINITY)
		afirst = 10000;
	if (asecond == INFINITY)
		asecond = 10000;
	if (athird == INFINITY)
		athird = 10000;

	double bfirst = this->a.y - (afirst*this->a.x);
	double bsecond = this->b.y - (asecond*this->b.x);
	double bthird = this->c.y - (athird*this->c.x);

	double firstcheck = (afirst*this->c.x - this->c.y + bfirst)*(afirst*in.x - in.y + bfirst);
	double secondcheck = (asecond*this->a.x - this->a.y + bsecond)*(asecond*in.x - in.y + bsecond);
	double thirdcheck = (athird*this->b.x - this->b.y + bthird)*(athird*in.x - in.y + bthird);

	if ((firstcheck < 0 || secondcheck < 0 || thirdcheck < 0) && (firstcheck != 0 && secondcheck != 0 && thirdcheck != 0))
		return 0;
	else
		return 1;
}


punkt trojkat::middle() //srodek ciezkosci
{
	odcinek ab = odcinek(this->a, this->b);
	odcinek bc = odcinek(this->b, this->c);

	punkt middleab = ab.midpoint();
	punkt middlebc = bc.midpoint();

	odcinek middleabc = odcinek(middleab, this->c);
	odcinek middlebca = odcinek(middlebc, this->a);

	return middleabc.intercept(middlebca);

	/*double afirst = factor(middleab, this->c);
	double asecond = factor(middlebc, this->a);
	double bfirst = (middleab.y - (afirst*middleab.x));
	double bsecond = (middlebc.y - (asecond*middlebc.x));*/

}


std::ostream& operator<<(std::ostream& output, const trojkat &pattern)
{
	return output << "Punkt a: " << pattern.a << ", Punkt b : " << pattern.b << ", Punkt c : " << pattern.c << "\n";
}





double distance(punkt a, punkt b)
{
	double d = (b.x - a.x)*(b.x - a.x) + (b.y - a.y)*(b.y - a.y);
	if (d < 0)
		d *= -1;
	return sqrt(d);
}


bool parallel(odcinek first, odcinek second)
{
	double ff = factor(first.a, first.b);
	double sf = factor(second.a, second.b);

	if (ff == sf)
		return 1;
	else
		return 0;
}


bool perpendicular(odcinek first, odcinek second)
{
	double ff = factor(first.a, first.b);
	double sf = factor(second.a, second.b);

	if (ff == INFINITY && second.b.y - second.a.y == 0)
		return 1;
	else if (sf == INFINITY && first.b.y - first.a.y == 0)
		return 1;

	else if ((ff*sf) == -1)
		return 1;
	else
		return 0;
}


double factor(punkt a, punkt b)  //wspolczynnik kierunkowy ze wzoru
{
	if (b.x - a.x == 0)
		return INFINITY;
	return ((b.y - a.y) / (b.x - a.x));
}


bool separable(trojkat first, trojkat second)
{
	if (first.isInside(second.a) == 1 || first.isInside(second.b) == 1 || first.isInside(second.c) == 1)
		return 0;
	else if (second.isInside(first.a) == 1 || second.isInside(first.b) == 1 || second.isInside(first.c) == 1)
		return 0;
	else
		return 1;
}


bool included(trojkat first, trojkat second)
{
	if (second.isInside(first.a) == 1 && second.isInside(first.b) == 1 && second.isInside(first.c) == 1)
		return 1;
	else
		return 0;
}