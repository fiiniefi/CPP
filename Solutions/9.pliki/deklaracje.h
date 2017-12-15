#pragma once
#include "stdafx.h"
#include <iostream>
#include <fstream>


std::istream& clearline(std::istream &input);

class ignore
{
private:
	int x;
public:
	ignore(int x) : x(x) {}
	friend std::istream& operator>>(std::istream &input, ignore &manip);
};


std::ostream& comma(std::ostream &output);
std::ostream& colon(std::ostream &output);

class index
{
private:
	int x;
	int w;
public:
	index(int x, int w = 0) : x(x), w(w) {}
	friend std::ostream& operator<<(std::ostream &output, index &manip);
};


namespace strumienie
{
	class PlikWejsciowy
	{
	private:
		std::ifstream plik;
	public:
		PlikWejsciowy(std::string sciezka, std::ios_base::openmode mode = std::ios_base::in);
		~PlikWejsciowy();
		PlikWejsciowy& operator>>(std::string &zdanie);
		PlikWejsciowy& operator>>(char &znak);
		PlikWejsciowy& operator>>(int &liczba);
		PlikWejsciowy& operator>>(double &liczba);
		bool eof()
		{
			return plik.eof();
		}
	};

	class PlikWyjsciowy
	{
	private:
		std::ofstream plik;
	public:
		PlikWyjsciowy(std::string sciezka, std::ios_base::openmode mode = std::ios_base::out);
		~PlikWyjsciowy();
		PlikWyjsciowy& operator<<(std::string zdanie);
		PlikWyjsciowy& operator<<(char znak);
		PlikWyjsciowy& operator<<(int liczba);
		PlikWyjsciowy& operator<<(double liczba);
	};

	PlikWyjsciowy& newline(PlikWyjsciowy &plik);
}