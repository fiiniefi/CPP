#include "stdafx.h"
#include "deklaracje.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>


void FA::resetBuffer()
{
	this->buffer = "";
}

void FA::flush()
{
	ofile << buffer;
	this->resetBuffer();
}


FA::FA(std::string input, std::string output) : how_many(0)
{
	ifile.open(input);
	if (!ifile.is_open())
		throw std::string("Cannot open an input file!\n");
	ofile.open(output, std::ios::trunc);
	if (!ofile.is_open())
		throw std::string("Cannot open an output file!\n");

	this->resetBuffer();
}


FA::~FA()
{
	this->flush();
	if(ifile.is_open())
		ifile.close();
	if (ofile.is_open())
		ofile.close();
}


void FA::addStates(std::vector<std::pair<std::string, bool>> pattern)
{
	states = pattern;
	current = pattern[0];
}


void FA::addAlphabet(std::vector<char> pattern)
{
	alphabet = pattern;
}


void FA::addFunction(std::pair<std::string, bool>(*funcpointer)(char, std::string, std::ifstream&))
{
	func = funcpointer;
}


void FA::start()
{
	while (!ifile.eof())
	{
		char character = ifile.get();
		if (ifile.eof())
		{
			if (current.second)
				how_many++;
			continue;
		}
		auto it = std::find_if(alphabet.begin(), alphabet.end(), [&character](char letter) { return letter == character; });
		if (it == alphabet.end())
		{
			this->flush();
			throw std::string("Character is not inside the alphabet\n");
		}

		std::pair<std::string, bool> newstate = func(character, current.first, ifile);
		if (newstate.first == "")
		{
			this->flush();
			throw std::string("Wrong character in transition function\n");
		}
		if (newstate.first != current.first)
		{
			if (newstate.second == false && current.second == true)
			{
				this->buffer += " ";
				how_many++;
			}
			this->flush();
			this->current = newstate;
		}
		if (this->current.second)
			buffer += character;
	}
	this->flush();
}


int FA::howMany()
{
	return this->how_many;
}