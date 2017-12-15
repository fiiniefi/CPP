#include "stdafx.h"
#include <iostream>
#include "struktury_danych.h"


lista::lista()
{
	this->first = this->last = nullptr;
	this->size = 0;
}

lista::lista(const lista &pattern) : lista()
{
	if (pattern.getSize() == 0)
		return;
	wezel *iterator = pattern.first;
	do
	{
		this->wstaw(this->size, iterator->value);
		iterator = iterator->next;
	}while(iterator != pattern.first);
}

lista::lista(lista &&pattern) : lista()
{
	if (pattern.getSize() == 0)
		return;
	this->size = pattern.size;
	this->first = pattern.first;
	this->last = pattern.last;
	pattern.first = pattern.last = nullptr;
}

lista::~lista()
{
	if (this->first == nullptr)
		return;
	wezel *iterator = first;
	wezel *iteratorpom = first->next;
	for (int i=0; i<this->size; i++)
	{
		delete iterator;
		iterator = iteratorpom;
		iteratorpom = iteratorpom->next;
	}
	this->size=0;
	this->first = this->last = nullptr;
}

lista& lista::operator=(const lista &pattern)
{
	this->~lista();
	
	if (pattern.getSize() == 0)
		return *this;
	this->size = 0;
	this->first = this->last = nullptr;
	wezel *iterator = pattern.first;
	do
	{
		this->wstaw(this->size, iterator->value);
		iterator = iterator->next;
	}while(iterator != pattern.first);
	return *this;
}

lista& lista::operator=(lista &&pattern)
{
	this->~lista();
	
	if (pattern.getSize() == 0)
		return *this;
	this->size = pattern.size;
	this->first = pattern.first;
	this->last = pattern.last;
	pattern.first = pattern.last = nullptr;
	return *this;
}

lista::wezel& lista::operator[](int pos) const
{
	if (pos < 0 || pos >= this->size)
		throw std::string("operator[](int): bledny indeks!\n");
	return this->first->index(pos);
}

void* lista::wezel::operator new(size_t)
{
	try
	{
		return (Memory::getInstance()).getAddress();
	}
	catch (std::string message)
	{
		std::string newmess = "operator new(size_t):" + message;
		throw std::string(newmess);
	}
}

void lista::wezel::operator delete(void *address)
{
	try
	{
		Memory::getInstance().freeAddress(reinterpret_cast<wezel*>(address));
	}
	catch (std::string message)
	{
		std::string newmess;
		newmess = "operator delete(void*):" + message;
		throw std::string(newmess);
	}
}


void lista::wstaw(int pos, double val)
{
	if (pos < 0)
		throw std::string("wstaw(int,double): indeks mniejszy od 0!\n");
	else if (pos > this->size)
		pos = this->size;
	if (this->first == nullptr && this->last == nullptr)
	{
		wezel *add = new wezel(val);
		add->next = add;
		add->previous = add;
		first = add;
		last = add;
		this->size++;
		return;
	}
	wezel *a=this->first->wstaw(pos, val);
	if (pos == 0)
		first = a;
	else if (pos == this->size)
		last = a;
	this->size++;
}

double lista::usun(int pos)
{
	if (size <= 0)
		throw std::string("usun(int): nie ma czego usuwac!\n");
	else if (pos >= this->size)
		throw std::string("usun(int): za wysoki indeks!\n");
	else if (this->first == this->last)
	{
		double v = first->value;
		delete first;
		this->first = this->last = nullptr;
		this->size--;
		return v;
	}
	else if (pos == this->size-1)
	{
		this->size--;
		wezel *h = last->previous;
		double v = last->usun(0);
		last = h;
		return v;
	}
	else if (pos == 0)
	{	
		this->size--;
		wezel *h = first->next;
		double v = first->usun(0);
		first = h;
		return v;
	}
	this->size--;
	return first->usun(pos);
}

int lista::getSize() const
{
	return this->size;
}

std::ostream& operator<<(std::ostream &wy, const lista &pattern)
{
	if (pattern.getSize() == 0)
		return wy;
	lista::wezel *iterator = pattern.first;
	do
	{
		wy<<*iterator<<" ";
		iterator = iterator->next;
	} while (iterator != pattern.first);
	return wy;
}

std::istream& operator>>(std::istream &we, lista &list)
{
	list.~lista();

	double s;
	we >> s;
	double v;

	for (int i = 0; i < s; i++)
	{
		we >> v;
		list.wstaw(i, v);
	}
	return we;
}



lista::wezel::wezel(double val)
{
	this->value = val;
}

lista::wezel::wezel(const wezel &pattern)
{
	this->value = pattern.value;
}

lista::wezel::wezel(wezel &&pattern)
{
	this->value = pattern.value;
}

lista::wezel* lista::wezel::wstaw(int pos, double val)
{
	if (pos == 0)
	{
		wezel *add=new wezel(val);
		add->next = this;
		add->previous = this->previous;
		this->previous->next = add;
		this->previous = add;
		return add;
	}

	return this->next->wstaw(pos - 1, val);
}

double lista::wezel::usun(int pos)
{
	if (pos == 0)
	{
		double v = this->value;
		this->previous->next = this->next;
		this->next->previous = this->previous;
		delete this;
		return v;
	}
	return this->next->usun(pos - 1);
}

lista::wezel& lista::wezel::index(int pos)
{
	if (pos == 0)
		return *this;
	return this->next->index(pos - 1);
}

lista::wezel& lista::wezel::operator=(const wezel& pattern)
{
	this->~wezel();
	
	this->value = pattern.value;
	return *this;
}

lista::wezel& lista::wezel::operator=(wezel &&pattern)
{
	this->~wezel();
	
	this->value = pattern.value;
	return *this;
}




void kolejka::wstaw(double val)
{
	lista::wstaw(this->size, val);
}

kolejka& kolejka::operator+=(double val)
{
	this->wstaw(val);
	return *this;
}

double kolejka::usun()
{
	return lista::usun(0);
}

double kolejka::operator--()
{
	try
	{
		return this->usun();
	}
	catch (std::string message)
	{
		std::string newmess;
		newmess = "kolejka::operator--():" + message;
		throw std::string(newmess);
	}
}

double kolejka::gotowy()
{
	return this->first->value;
}

double kolejka::operator*()
{
	return this->gotowy();
}

int kolejka::ile()
{
	return this->size;
}




void stos::wstaw(double val)
{
	lista::wstaw(0, val);
}

stos& stos::operator+=(double val)
{
	this->wstaw(val);
	return *this;
}

double stos::usun()
{
	return lista::usun(0);
}

double stos::operator--()
{
	try
	{
		return this->usun();
	}
	catch (std::string message)
	{
		std::string newmess;
		newmess = "stos::operator--():" + message;
		throw std::string(newmess);
	}
}

double stos::gotowy()
{
	return this->last->value;
}

double stos::operator*()
{
	return this->gotowy();
}

int stos::ile()
{
	return this->size;
}



lista::wezel Memory::ground[Memory::size];
bool Memory::flags[Memory::size]; //1 - free, 0 - occupied

lista::wezel* Memory::getAddress()
{
	int i;
	for (i = 0; i < size && flags[i] == 0; i++);
	
	if (i == size)
		throw std::string("getAddress(): wszystkie sloty sa zajete!\n");
	else
	{
		flags[i] = 0;
		return &ground[i];
	}

}

void Memory::freeAddress(lista::wezel *address)
{
	int i = 0;
	while (i != size && &ground[i] != address)
		i++;

	if (i == size)
		throw std::string("freeAddress(): miejsce pod wezel nie zostalo wziete z tej tablicy!\n");
	else
		flags[i] = 1;
}