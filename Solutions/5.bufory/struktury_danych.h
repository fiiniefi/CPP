#include "stdafx.h"
#include <iostream>
#include <algorithm>


class lista
{
protected:
	class wezel;
	wezel *first;
	wezel *last;
	int size;
public:
	lista();
	lista(const lista &pattern);
	lista(lista &&pattern);
	~lista();
	lista& operator=(const lista &pattern);
	lista& operator=(lista &&pattern);
	void wstaw(int pos, double val);
	double usun(int pos);
	int getSize() const;
	wezel& operator[](int pos) const;

	friend std::istream& operator>>(std::istream &we, lista &list);
	friend std::ostream& operator<<(std::ostream &wy, const lista &pattern);
	friend std::ostream& operator<<(std::ostream& wy, const wezel& pattern);
	friend class Memory;

protected:
	class wezel
	{
	public:
		wezel *next;
		wezel *previous;
		double value;

		wezel() = default;
		wezel(double val); 
		wezel(const wezel &pattern);
		wezel(wezel &&pattern);
		wezel* wstaw(int pos, double val);
		double usun(int pos);
		wezel& index(int pos);
		wezel& operator=(const wezel &pattern);
		wezel& operator=(wezel &&pattern);
		static void* operator new(size_t);
		static void operator delete(void *address);

		friend std::ostream& operator<<(std::ostream& wy, const wezel& pattern)
		{
			return wy << pattern.value;
		}
	};
};


class kolejka : protected lista
{
//posiadam chronione pola first, last oraz size. mam tez odziedziczona klase wezel
public:
	using lista::lista; //dziedziczenie konstruktorow
	kolejka& operator+=(double val);
	double operator--();
	double operator*();
	void wstaw(double val);
	double usun();
	double gotowy();
	int ile();
};


class stos : protected lista
{
//posiadam chronione pola first, last oraz size. mam tez odziedziczona klase wezel
public:
	using lista::lista;
	stos& operator+=(double val);
	double operator--();
	double operator*();
	void wstaw(double val);
	double usun();
	double gotowy();
	int ile();
};



class Memory
{
private:
	static const int size = 10;
	static lista::wezel ground[size];
	static bool flags[size]; //1 - free, 0 - occupied
	Memory()
	{
		std::fill_n(flags, size, 1);
	}

public:
	static Memory& getInstance()
	{
		static Memory instance; //statyczny obiekt jest inicjalizowany przy pierwszym wywolaniu i istnieje do konca programu
		return instance;
	}
	~Memory() = default;
	Memory(Memory const&) = delete;
	Memory(Memory &&) = delete;
	void operator=(Memory const&) = delete;
	void operator=(Memory &&) = delete;
	lista::wezel* getAddress();
	void freeAddress(lista::wezel *address);
};