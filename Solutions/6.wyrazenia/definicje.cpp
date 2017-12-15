#include "stdafx.h"
#include <iostream>
#include <map>
#include <algorithm>
#include <string>
#include "deklaracje.h"

using namespace wyr;

char wyrazenie::getAssociativity()
{
	return 'l';
}


const int liczba::priority = 1000;

liczba::liczba(double v)
{
	this->value = v;
}

int liczba::getPriority()
{
	return priority;
}

double liczba::oblicz()
{
	return this->value;
}

std::string liczba::opis()
{
	std::string v = std::to_string(this->value);
	v.erase(v.find_last_not_of('0') + 1, std::string::npos);
	v.erase(v.find_last_not_of('.') + 1, std::string::npos);
	return v;
}


const int stala::priority = 1000;

double stala::oblicz()
{
	return this->value;
}

int stala::getPriority()
{
	return priority;
}

std::string stala::opis()
{
	return this->name;
}


std::vector<std::pair<std::string, double>> zmienna::variables;
const int zmienna::priority = 1000;

void zmienna::remove(std::string &name)
{
	std::vector<std::pair<std::string, double>>::iterator it = std::find_if(variables.begin(), variables.end(),
																[&name](const std::pair<std::string, double> p) -> bool { return name == p.first; });
	if (it != variables.end())
		variables.erase(it);
}

zmienna::zmienna(std::string name) : var(name)
{
	remove(name);
	variables.push_back(std::make_pair(name, NAN));
}

zmienna::zmienna(std::string name, double value) : var(name)
{
	remove(name);
	variables.push_back(std::make_pair(name, value));
}

int zmienna::getPriority()
{
	return priority;
}

void zmienna::set(std::string name, double value)
{
	remove(name);
	variables.push_back(std::make_pair(name, value));
}

double zmienna::oblicz()
{
	std::string variable = this->var;
	std::vector<std::pair<std::string, double>>::iterator it = std::find_if(variables.begin(), variables.end(),
																[&variable](const std::pair<std::string, double> p) -> bool { return variable == p.first; });
	if (it == variables.end())
		throw key_doesnt_exists("Variable doesnt exist!");
	int index = (it - variables.begin());
	if (isnan(((variables.at(index)).second)))
		throw unset_value("Unset value!\n");
	return (variables.at(index)).second;
}

std::string zmienna::opis()
{
	return this->var;
}



int unary::getPriority()
{
	return priority;
}


double sin::oblicz()
{
	double arg = this->left->oblicz();
	return std::sin(arg);
}

std::string sin::opis()
{
	return "sin(" + this->left->opis() + ")";
}


double cos::oblicz()
{
	double arg = this->left->oblicz();
	return std::cos(arg);
}

std::string cos::opis()
{
	return "cos(" + this->left->opis() + ")";
}


double exp::oblicz()
{
	double arg = this->left->oblicz();
	return std::exp(arg);
}

std::string exp::opis()
{
	return "e^(" + this->left->opis() + ")";
}


double ln::oblicz()
{
	double arg = this->left->oblicz();
	return std::log(arg);
}

std::string ln::opis()
{
	return "ln(" + this->left->opis() + ")";
}


double abs::oblicz()
{
	double arg = this->left->oblicz();
	return std::fabs(arg);
}

std::string abs::opis()
{
	return "|" + this->left->opis() + "|";
}


double opp::oblicz()
{
	double arg = this->left->oblicz();
	return arg*(-1);
}

std::string opp::opis()
{
	return "-(" + this->left->opis() + ")";
}


double inv::oblicz()
{
	double arg = this->left->oblicz();
	return 1 / arg;
}

std::string inv::opis()
{
	return "1 / (" + this->left->opis() + ")";
}



int binary::getPriority()
{
	return priority;
}

std::string binary::opis()
{
	std::string result="";
	if (priority > this->left->getPriority())
		result += "(" + this->left->opis() + ")";
	else if (priority == this->left->getPriority() && this->getAssociativity() == 'r')
		result += "(" + this->left->opis() + ")";
	else
		result += this->left->opis();

	result += " " + this->op + " ";

	if (priority > this->right->getPriority())
		result += "(" + this->right->opis() + ")";
	else if (priority == this->right->getPriority() && this->getAssociativity() == 'l')
		result += "(" + this->right->opis() + ")";
	else
		result += this->right->opis();
	return result;
}




double dodaj::oblicz()
{
	double leftvalue = this->left->oblicz();
	double rightvalue = this->right->oblicz();

	return leftvalue + rightvalue;
}


double odejmij::oblicz()
{
	double leftvalue = this->left->oblicz();
	double rightvalue = this->right->oblicz();

	return leftvalue - rightvalue;
}


double pomnoz::oblicz()
{
	double leftvalue = this->left->oblicz();
	double rightvalue = this->right->oblicz();

	return leftvalue * rightvalue;
}


double podziel::oblicz()
{
	double leftvalue = this->left->oblicz();
	double rightvalue = this->right->oblicz();

	if (rightvalue == 0)
		throw divide_by_zero_exception("Zero in denominator!\n");

	return leftvalue / rightvalue;
}


double modulo::oblicz()
{
	//int leftvalue = static_cast<int>(this->left->oblicz());
	//int rightvalue = static_cast<int>(this->right->oblicz());
	
	//return leftvalue % rightvalue;
	double leftvalue = (this->left->oblicz());
	double rightvalue = (this->right->oblicz());
	return fmod(leftvalue, rightvalue);
}


double poteguj::oblicz()
{
	double leftvalue = this->left->oblicz();
	double rightvalue = this->right->oblicz();

	return std::pow(leftvalue, rightvalue);
}


char poteguj::getAssociativity()
{
	return 'r';
}


double log::oblicz()
{
	double leftvalue = this->left->oblicz();
	double rightvalue = this->right->oblicz();

	return std::log(rightvalue) / std::log(leftvalue);
}

std::string log::opis()
{
	return (op + "(" + this->left->opis() + ")" + "^" + "(" + this->right->opis() + ")");
}























/*zmienna::zmienna(std::string n)
{
	this->name = n;
	this->value = NAN;
}

zmienna::zmienna(std::string n, double v)
{
	this->name = n;
	this->value = v;
}

void zmienna::set(double v)
{
	this->value = v;
}

double zmienna::oblicz()
{
	if (isnan(this->value))
		throw unset_value("Unset value of variable" + this->name + "!");
	return this->value;
}

std::string zmienna::opis()
{
	return this->name;
}








std::map<std::string, double> stala::constants = { {"pi", 3.14}, {"e", 2.71}, {"golden ratio", 1.618} };

stala::stala(std::string n)
{
this->name = n;
}

double stala::oblicz()
{
if (constants.end() == constants.find(this->name))
throw key_doesnt_exists("Key doesn't exists!");
return constants[this->name];
}

std::string stala::opis()
{
if (constants.end() == constants.find(this->name))
throw key_doesnt_exists("Key" + this->name + "doesn't exist!");
return std::to_string(constants[this->name]);
}*/