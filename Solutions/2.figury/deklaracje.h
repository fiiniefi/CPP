#include "stdafx.h"
#include <iostream>
#ifndef asd
#define asd

class punkt;
class odcinek;
class trojkat;
double distance(punkt a, punkt b);
bool parallel(odcinek first, odcinek second);
bool perpendicular(odcinek first, odcinek second);
double factor(punkt a, punkt b); //pomocnicza

bool separable(trojkat first, trojkat second);
bool included(trojkat first, trojkat second);

class punkt
{
private:
	double x;
	double y;

public:
	punkt();
	punkt(const double a, const double b);
	punkt(const punkt &pattern);
	punkt& operator=(const punkt &pattern);
	bool operator==(const punkt &pattern);
	void move(const double x, const double y);
	void rotation(const double x, const double y, const double alpha);
	friend std::ostream& operator<<(std::ostream& output, const punkt &pattern);

	friend odcinek;
	friend trojkat;
	friend double factor(punkt a, punkt b);
	friend double distance(punkt a, punkt b);
	friend bool perpendicular(odcinek first, odcinek second);
};


class odcinek
{
private:
	punkt a;
	punkt b;

public:
	odcinek(punkt a, punkt b);
	odcinek(const odcinek &pattern);
	odcinek& operator=(const odcinek &pattern);
	bool operator==(const odcinek &pattern);
	void move(const double x, const double y);
	void rotation(const double x, const double y, const double alpha); //obrot wokol punktu (x,y) o kat alpha
	double length();
	bool onSegment(const punkt a) const;
	punkt midpoint();
	punkt intercept(const odcinek compared);
	friend std::ostream& operator<<(std::ostream& output, const odcinek &pattern);
	friend bool parallel(odcinek first, odcinek second);
	friend bool perpendicular(odcinek first, odcinek second);
};


class trojkat
{
private:
	punkt a;
	punkt b;
	punkt c;

public:
	trojkat(punkt a, punkt b, punkt c);
	trojkat(const trojkat &pattern);
	trojkat& operator=(const trojkat &pattern);
	bool operator==(const trojkat &pattern);
	void move(const double x, const double y);
	void rotation(const double x, const double y, const double alpha); //obrot wokol punktu (x,y) o kat alpha
	double circuit();
	double area();
	bool isInside(punkt in);
	punkt middle();
	friend bool separable(trojkat first, trojkat second);
	friend bool included(trojkat first, trojkat second);
	friend std::ostream& operator<<(std::ostream& output, const trojkat &pattern);
};
#endif