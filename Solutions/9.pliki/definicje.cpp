#include "stdafx.h"
#include <iostream>
#include <string>
#include "deklaracje.h"



std::istream& clearline(std::istream &input)
{
	while (input.peek() != EOF && input.get() != '\n');
	return input;
}


std::istream& operator>>(std::istream &input, ignore &manip)
{
	if (manip.x <= 0)
		return input;
	while (input.peek() != EOF && input.get() != '\n' && (--manip.x) > 0);
	return input;
}



std::ostream& comma(std::ostream &output)
{
	return output << ", ";
}


std::ostream& colon(std::ostream &output)
{
	return output << ": ";
}


std::ostream& operator<<(std::ostream &output, index &manip)
{
	std::string value = std::to_string(manip.x);
	output << '[';
	manip.w -= value.length();
	manip.w -= 2;

	while ((manip.w--) > 0)
		output << " ";
	output << manip.x;
	output << ']';
	return output;
}





strumienie::PlikWejsciowy::PlikWejsciowy(std::string sciezka, std::ios_base::openmode mode)
{
	plik.open(sciezka, mode);
	if (!plik.is_open())
		throw std::string("Cannot open a file in PlikWejsciowy!\n");
}

strumienie::PlikWejsciowy::~PlikWejsciowy()
{
	if (plik.is_open())
		plik.close();
}

strumienie::PlikWejsciowy& strumienie::PlikWejsciowy::operator>>(std::string &zdanie)
{
	std::getline(plik, zdanie);
	if (plik.fail())
		throw std::ios::failure("Input stream error on string\n");
	return *this;
}

strumienie::PlikWejsciowy& strumienie::PlikWejsciowy::operator>>(char &znak)
{
	this->plik >> znak;
	if (plik.fail())
		throw std::ios::failure("Input stream error on char\n");
	return *this;
}

strumienie::PlikWejsciowy& strumienie::PlikWejsciowy::operator>>(int &liczba)
{
	while (isspace(plik.peek()))
		plik.get();
	if (plik.eof())
	{
		liczba = NAN;
		return *this;
	}
	this->plik >> liczba;
	if (plik.fail())
		throw std::ios::failure("Input stream error on int\n");
	return *this;
}

strumienie::PlikWejsciowy& strumienie::PlikWejsciowy::operator>>(double &liczba)
{
	while (isspace(plik.peek()))
		plik.get();
	if (plik.eof())
	{
		liczba = NAN;
		return *this;
	}
	this->plik >> liczba;
	if (plik.fail())
		throw std::ios::failure("Input stream error on double\n");
	return *this;
}



strumienie::PlikWyjsciowy::PlikWyjsciowy(std::string sciezka, std::ios_base::openmode mode)
{
	plik.open(sciezka, mode);
	if (!plik.is_open())
		throw std::string("Cannot open a file in PlikWyjsciowy!\n");
}

strumienie::PlikWyjsciowy::~PlikWyjsciowy()
{
	if (plik.is_open())
		plik.close();
}

strumienie::PlikWyjsciowy& strumienie::PlikWyjsciowy::operator<<(std::string zdanie)
{
	this->plik << zdanie;
	if (plik.fail())
		throw std::ios::failure("Output stream error on string\n");
	return *this;
}

strumienie::PlikWyjsciowy& strumienie::PlikWyjsciowy::operator<<(char znak)
{
	this->plik << znak;
	if (plik.fail())
		throw std::ios::failure("Output stream error on char\n");
	return *this;
}

strumienie::PlikWyjsciowy& strumienie::PlikWyjsciowy::operator<<(int liczba)
{
	this->plik << liczba;
	if (plik.fail())
		throw std::ios::failure("Output stream error on int\n");
	return *this;
}

strumienie::PlikWyjsciowy& strumienie::PlikWyjsciowy::operator<<(double liczba)
{
	this->plik << liczba;
	if (plik.fail())
		throw std::ios::failure("Output stream error on double\n");
	return *this;
}



strumienie::PlikWyjsciowy& strumienie::newline(strumienie::PlikWyjsciowy& plik)
{
	return plik << '\n';
}