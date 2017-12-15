#include "stdafx.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include "deklaracje.h"


void comments(std::string path);
void fillAlphabet(std::vector<char> &alphabet);
std::pair<std::string, bool> funcComments(char character, std::string current, std::ifstream &file);


void numbers(std::string path);
std::pair<std::string, bool> funcNumbers(char character, std::string current, std::ifstream &file);


void identifiers(std::string path);
std::pair<std::string, bool> funcIdentifiers(char character, std::string current, std::ifstream &file);



void printFile(std::string path);
std::unordered_map<std::string, unsigned int> count(std::string path);



int main(int argc, char *argv[])
{
	comments(argv[1]);
	numbers(argv[1]);
	identifiers(argv[1]);
}



void comments(std::string path)
{
	std::vector<std::pair<std::string, bool>> states = { std::make_pair("program", true), std::make_pair("one_line_comment", false), std::make_pair("multiline_comment", false),
														 std::make_pair("string", true) };
	std::vector<char> alphabet;
	fillAlphabet(alphabet);
	std::pair<std::string, bool>(*funcpoin)(char, std::string, std::ifstream&) = funcComments;

	try
	{
		FA automat(path, "outComments.txt");
		automat.addAlphabet(std::move(alphabet));
		automat.addStates(std::move(states));
		automat.addFunction(funcpoin);
		automat.start();
	}
	catch (std::string mess)
	{
		std::cout << mess << std::endl;
	}
	printFile("outComments.txt");
}


void fillAlphabet(std::vector<char> &alphabet)
{
	alphabet.reserve(256);
	for (unsigned int i = 0; i < 256; i++)
		alphabet.push_back(i);
}


std::pair<std::string, bool> funcComments(char character, std::string current, std::ifstream &file)
{
	if (current == "one_line_comment")
	{
		if (character == '\n')
			return std::make_pair("program", true);
		else
			return std::make_pair(current, false);
	}
	else if (current == "multiline_comment")
	{
		if (character == '*')
		{
			char next = file.peek();
			if (file.eof())
				return std::make_pair(current, false);
			else if (next == '/')
			{
				file.get();
				return std::make_pair("program", false);
			}
			else
				return std::make_pair(current, false);
		}
		else
			return std::make_pair(current, false);
	}
	else if (current == "program")
	{
		if (character == '/')
		{
			char next = file.peek();
			if (file.eof())
				return std::make_pair(current, false);
			else if (next == '/')
			{
				file.get();
				return std::make_pair("one_line_comment", false);
			}
			else if (next == '*')
			{
				file.get();
				return std::make_pair("multiline_comment", false);
			}
			else
				return std::make_pair(current, true);
		}
		else if (character == '"')
			return std::make_pair("string", true);
		else
			return std::make_pair(current, true);
	}
	else if (current == "string")
	{
		if (character == '\\')
		{
			char next = file.peek();
			if (file.eof())
				return std::make_pair(current, false);
			else if (next == '"')
				return std::make_pair("program", true);  //idea jest taka ze ponownie wchodze w program, ktoremu mowie, ze zamknalem string. otworze go ponownie przy kolejnym cudzyslowie
			else
				return std::make_pair(current, true);
		}
		else if (character == '"')
			return std::make_pair("program", true);
		else
			return std::make_pair(current, true);
	}
	else
		return std::make_pair("", false);
}



void numbers(std::string path)
{
	std::vector<std::pair<std::string, bool>> states = { std::make_pair("program", false), std::make_pair("one_line_comment", false), std::make_pair("multiline_comment", false),
														 std::make_pair("number", true), std::make_pair("string", false), std::make_pair("number_in_string", true) };
	std::vector<char> alphabet;
	fillAlphabet(alphabet);
	std::pair<std::string, bool>(*funcpoin)(char, std::string, std::ifstream&) = funcNumbers;
	try
	{
		FA automat(path, "outNumbers.txt");
		automat.addAlphabet(std::move(alphabet));
		automat.addStates(std::move(states));
		automat.addFunction(funcpoin);
		automat.start();
	}
	catch (std::string mess)
	{
		std::cout << mess << std::endl;
	}
	printFile("outNumbers.txt");
}


std::pair<std::string, bool> funcNumbers(char character, std::string current, std::ifstream &file)
{
	if (current == "one_line_comment")
	{
		if (character == '\n')
			return std::make_pair("program", false);
		else
			return std::make_pair(current, false);
	}
	else if (current == "multiline_comment")
	{
		if (character == '*')
		{
			char next = file.peek();
			if (file.eof())
				return std::make_pair(current, false);
			else if (next == '/')
			{
				file.get();
				return std::make_pair("program", false);
			}
			else
				return std::make_pair(current, false);
		}
		else
			return std::make_pair(current, false);
	}
	else if (current == "number")
	{
		if (character >= '0' && character <= '9')
			return std::make_pair(current, true);
		else if (character == '.')
		{
			char next = file.peek();
			if (file.eof())
				return std::make_pair(current, false);
			else if (next >= '0' && next <= '9')
				return std::make_pair(current, true);
			else
				return std::make_pair("program", false);
		}
		else if (character == '/')
		{
			char next = file.peek();
			if (file.eof())
				return std::make_pair("program", false);
			else if (next == '/')
			{
				file.get();
				return std::make_pair("one_line_comment", false);
			}
			else if (next == '*')
			{
				file.get();
				return std::make_pair("multiline_comment", false);
			}
			else
				return std::make_pair("program", false);
		}
		else if (character == '"')
			return std::make_pair("string", false);
		else
			return std::make_pair("program", false);
	}
	else if (current == "program")
	{
		if (character >= '0' && character <= '9')
			return std::make_pair("number", true);
		else if (character == '-')
		{
			char next = file.peek();
			if (file.eof())
				return std::make_pair(current, false);
			else if (next >= '0' && next <= '9')
				return std::make_pair("number", true);
			else
				return std::make_pair(current, false);
		}
		else if (character == '/')
		{
			char next = file.peek();
			if (file.eof())
				return std::make_pair(current, false);
			else if (next == '/')
			{
				file.get();
				return std::make_pair("one_line_comment", false);
			}
			else if (next == '*')
			{
				file.get();
				return std::make_pair("multiline_comment", false);
			}
			else
				return std::make_pair("program", false);
		}
		else if (character == '"')
			return std::make_pair("string", false);
		else
			return std::make_pair("program", false);
	}
	else if (current == "string")
	{
		if (character == '\\')
		{
			char next = file.peek();
			if (file.eof())
				return std::make_pair(current, false);
			else if (next == '"')
				return std::make_pair("program", false);  //idea jest taka ze ponownie wchodze w program, ktoremu mowie, ze zamknalem string. otworze go ponownie przy kolejnym cudzyslowie
			else
				return std::make_pair(current, false);
		}
		else if (character == '"')
			return std::make_pair("program", false);
		else if ((character >= '0' && character <= '9'))
			return std::make_pair("number_in_string", true);
		else if (character == '-')
		{
			char next = file.peek();
			if (file.eof())
				return std::make_pair(current, false);
			else if (next >= '0' && next <= '9')
				return std::make_pair("number_in_string", true);
			else
				return std::make_pair(current, false);
		}
		else
			return std::make_pair(current, false);
	}
	else if (current == "number_in_string")
	{
		if ((character >= '0' && character <= '9') || character == '.')
			return std::make_pair(current, true);
		else if (character == '"')
			return std::make_pair("program", false);
		else if (character == '\\')
		{
			char next = file.peek();
			if (file.eof())
				return std::make_pair("string", false);
			else if (next == '"')
				return std::make_pair("program", false);  //idea jest taka ze ponownie wchodze w program, ktoremu mowie, ze zamknalem string. otworze go ponownie przy kolejnym cudzyslowie
			else
				return std::make_pair("string", false);
		}
		else
			return std::make_pair("string", false);
	}
	else
		return std::make_pair("", false);
}




void identifiers(std::string path)
{
	std::vector<std::pair<std::string, bool>> states = { std::make_pair("non-identifier", false), std::make_pair("one_line_comment", false), std::make_pair("multiline_comment", false),
														 std::make_pair("identifier", true), std::make_pair("string", false) };
	std::vector<char> alphabet;
	fillAlphabet(alphabet);
	std::pair<std::string, bool>(*funcpointer)(char, std::string, std::ifstream&) = funcIdentifiers;
	int howmany;
	try
	{
		FA automat(path, "outIdentifiers.txt");
		automat.addAlphabet(std::move(alphabet));
		automat.addStates(std::move(states));
		automat.addFunction(funcpointer);
		automat.start();
		howmany = automat.howMany();
	}
	catch (std::string mess)
	{
		std::cout << mess << std::endl;
	}

	printFile("outIdentifiers.txt");
	std::cout << std::endl << "Ilosc identyfikatorow: " << howmany << std::endl << std::endl << std::endl;
	try
	{
		std::unordered_map<std::string, unsigned int> ids = count("outIdentifiers.txt");
		for (auto i : ids)
		{
			std::cout << i.first << ": " << i.second << std::endl;
		}
	}
	catch (std::string mess)
	{
		std::cout << mess << std::endl;
	}
}


std::pair<std::string, bool> funcIdentifiers(char character, std::string current, std::ifstream &file)
{
	if (current == "one_line_comment")
	{
		if (character == '\n')
			return std::make_pair("non-identifier", false);
		else
			return std::make_pair(current, false);
	}
	else if (current == "multiline_comment")
	{
		if (character == '*')
		{
			char next = file.peek();
			if (file.eof())
				return std::make_pair(current, false);
			else if (next == '/')
			{
				file.get();
				return std::make_pair("non-identifier", false);
			}
			else
				return std::make_pair(current, false);
		}
		else
			return std::make_pair(current, false);
	}
	else if (current == "identifier")
	{
		if (character == '/')
		{
			char next = file.peek();
			if (file.eof())
				return std::make_pair(current, false);
			else if (next == '/')
			{
				file.get();
				return std::make_pair("one_line_comment", false);
			}
			else if (next == '*')
			{
				file.get();
				return std::make_pair("multiline_comment", false);
			}
			else
				return std::make_pair("non-identifier", false);
		}
		else if ((character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z') || (character >= '0' && character <= '9') || character == '_')
			return std::make_pair(current, true);
		else if (character == '"')
			return std::make_pair("string", false);
		else
			return std::make_pair("non-identifier", false);
	}
	else if (current == "non-identifier")
	{
		if (character == '/')
		{
			char next = file.peek();
			if (file.eof())
				return std::make_pair(current, false);
			else if (next == '/')
			{
				file.get();
				return std::make_pair("one_line_comment", false);
			}
			else if (next == '*')
			{
				file.get();
				return std::make_pair("multiline_comment", false);
			}
			else
				return std::make_pair("non-identifier", false);
		}
		else if ((character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z') || character == '_')
			return std::make_pair("identifier", true);
		else if (character == '"')
			return std::make_pair("string", false);
		else
			return std::make_pair(current, false);
	}
	else if (current == "string")
	{
		if (character == '\\')
		{
			char next = file.peek();
			if (file.eof())
				return std::make_pair(current, false);
			else if (next == '"')
				return std::make_pair("non-identifier", false);  //idea jest taka ze ponownie wchodze w program, ktoremu mowie, ze zamknalem string. otworze go ponownie przy kolejnym cudzyslowie
			else
				return std::make_pair(current, false);
		}
		else if (character == '"')
			return std::make_pair("non-identifier", false);
		else
			return std::make_pair(current, false);
	}
	else
		return std::make_pair("", false);
}





void printFile(std::string path)
{
	std::ifstream f(path);
	while (!f.eof())
	{
		std::string line;
		std::getline(f, line);
		std::cout << line << '\n';
	}
}


std::unordered_map<std::string, unsigned int> count(std::string path)
{

	std::unordered_map<std::string, unsigned int> liczby;

	std::vector<std::pair<std::string, int>> *ids = new std::vector<std::pair<std::string, int>>();
	std::ifstream file;
	file.open(path);
	if (!file.is_open())
		throw std::string("Cannot open a file!\n");
	while (!file.eof())
	{
		std::string word;
		file >> word;
		if (file.eof())
			continue;
		liczby[word]++;
	}
	return std::move(liczby);
}