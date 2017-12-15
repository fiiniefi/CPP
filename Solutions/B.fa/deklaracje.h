#pragma once
#include "stdafx.h"
#include <vector>
#include <functional>
#include <fstream>




class FA
{
private:
	std::ifstream ifile;
	std::ofstream ofile;
	std::vector<std::pair<std::string, bool>> states;
	std::vector<char> alphabet;
	std::function<std::pair<std::string, bool>(char, std::string, std::ifstream&)> func;
	std::pair<std::string, bool> current;
	std::string buffer;
	int how_many;
	void resetBuffer();
	void flush();
public:
	FA(std::string input, std::string output);
	~FA();
	void addStates(std::vector<std::pair<std::string, bool>> pattern);
	void addAlphabet(std::vector<char> pattern);
	void addFunction(std::pair<std::string, bool>(*funcpointer)(char, std::string, std::ifstream&));
	void start();
	int howMany();
};