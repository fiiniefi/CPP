#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "deklaracje.h"

void manip_test();
void wrapper_test();
std::string rec_fill(strumienie::PlikWejsciowy &plik); //nie uzylem, ale funkcja fajna i moim zdaniem sprytniejsza niz vector, wiec zostawiam
void fill(strumienie::PlikWejsciowy &plik, std::vector<double> &vec);



int main()
{
	manip_test();
	wrapper_test();
}



void manip_test()
{
	std::ifstream plik;
	plik.open("MarcinDrewniak.txt");
	if (!plik.is_open())
	{
		std::cerr << "Cannot open a file";
		return;
	}

	std::vector<std::string> zd;
	while (!plik.eof())
	{
		std::string zdanie;
		getline(plik, zdanie);
		zd.push_back(zdanie);
	}
	plik.close();

	int il = zd.size();
	std::string ill = std::to_string(il);
	int ile = ill.length();
	ile += 2;


	std::vector<std::string> zdania;
	for (int i = 0; i < zd.size(); i++)
	{
		std::ostringstream out;
		out << index(i+1, ile) << zd[i];
		zdania.push_back(out.str());
	}
	zd.clear();

	std::string pomocnicze="";

	for (int j = 0; j < zdania.size() ; j++)
	{
		std::vector<std::string>::iterator del;
		for (auto i = zdania.begin() + j; i < zdania.end(); i++)
		{
			if (pomocnicze == "")
			{
				pomocnicze = zdania[i - zdania.begin()];
				del = i;
			}
			else
			{
				std::string sub = (zdania[i - zdania.begin()]).substr(ile);
				std::string sub2 = pomocnicze.substr(ile);
				if (sub < sub2)
				{
					pomocnicze = zdania[i - zdania.begin()];
					del = i;
				}
			}
		}
		std::string temp = zdania[j];
		zdania[j] = pomocnicze;
		zdania[del - zdania.begin()] = temp;
		pomocnicze = "";
	}

	std::ofstream plik2;
	plik2.open("MarcinDrewniakOutput.txt", std::ofstream::out | std::ofstream::trunc);
	for (int i = 0; i < zdania.size(); i++)
		plik2 << zdania[i] << '\n';
	plik2.close();
}



void wrapper_test()
{
	strumienie::PlikWejsciowy plik("ciag.txt");
	std::vector<double> vec;
	try
	{
		fill(plik, vec);
		strumienie::PlikWyjsciowy plikout("ciag.txt");
		for (int i = vec.size() - 1; i >= 0; i--)
			plikout << vec[i] << " ";
	}
	catch (std::ios::failure message)
	{
		std::cerr << message.what();
	}
}


void fill(strumienie::PlikWejsciowy &plik, std::vector<double> &vec)
{
	while (!plik.eof())
	{
		double liczba;
		plik >> liczba;
		if (isnan(liczba))
			continue;
		vec.push_back(liczba);
	}
}



std::string rec_fill(strumienie::PlikWejsciowy &plik)
{
	if (plik.eof())
		return "";

	double liczba;
	plik >> liczba;
	std::string zdanie = rec_fill(plik);
	zdanie += std::to_string(liczba) + " ";
	return zdanie;
}