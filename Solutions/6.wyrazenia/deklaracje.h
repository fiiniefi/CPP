#ifndef DEKLARACJE_H
#define DEKLARACJE_H
#include "stdafx.h"
#include <iostream>
#include <vector>
#include <exception>
#include <map>


namespace wyr
{

	class key_doesnt_exists : public std::runtime_error
	{
		using std::runtime_error::runtime_error;
	};

	class unset_value : public std::runtime_error
	{
		using std::runtime_error::runtime_error;
	};

	class divide_by_zero_exception : public std::runtime_error
	{
		using std::runtime_error::runtime_error;
	};


	class wyrazenie
	{
	public:
		wyrazenie::wyrazenie() = default;
		virtual double oblicz() = 0;
		virtual std::string opis() = 0;
		virtual int getPriority() = 0;
		virtual char getAssociativity();
	};


	class liczba : public wyrazenie
	{
	private:
		double value;
		static const int priority;
	public:
		liczba(double v);
		int getPriority() override;
		double oblicz() override;
		std::string opis() override;
	};


	class stala : public wyrazenie
	{
	protected:
		const std::string name;
		const double value;
		static const int priority;
	public:
		stala(std::string n, double v) : name(n), value(v) {}
		int getPriority() override;
		double oblicz() override;
		std::string opis() override;
	};


	class pi : public stala
	{
	public:
		pi() : stala("pi", 3.14) {}
		//odziedzicze sobie oblicz i opis
	};


	class e : public stala
	{
	public:
		e() : stala("e", 2.71) {}
		//odziedzicze sobie oblicz i opis
	};


	class golden_ratio : public stala
	{
	public:
		golden_ratio() : stala("golden ratio", 1.618) {}
		//odziedzicze sobie oblicz i opis
	};


	class zmienna : public wyrazenie
	{
	private:
		static std::vector<std::pair<std::string, double>> variables;
		static void remove(std::string &name);
		std::string var;
		static const int priority;

	public:
		zmienna(std::string name);
		zmienna(std::string name, double value);
		static void set(std::string name, double value);
		int getPriority() override;
		double oblicz() override;
		std::string opis() override;
	};



	class unary : public wyrazenie   //abstrakcyjna
	{
	protected:
		wyrazenie *left;
	private:
		const int priority;

	public:
		unary(wyrazenie *l) : left(l), priority(900) { }
		int getPriority() override;
	};


	class sin : public unary    //w radianach
	{
		//dziedzicze *left
		//dziedzicze priority prywatnie
	public:
		sin(wyrazenie *w) : unary(w) { }
		double oblicz() override;
		std::string opis() override;
	};


	class cos : public unary
	{
		//dziedzicze *left
		//dziedzicze priority prywatnie
	public:
		cos(wyrazenie *w) : unary(w) { }
		double oblicz() override;
		std::string opis() override;
	};


	class exp : public unary
	{
		//dziedzicze *left
		//dziedzicze priority prywatnie
	public:
		exp(wyrazenie *w) : unary(w) { }
		double oblicz() override;
		std::string opis() override;
	};


	class ln : public unary
	{
		//dziedzicze *left
		//dziedzicze priority prywatnie
	public:
		ln(wyrazenie *w) : unary(w) { }
		double oblicz() override;
		std::string opis() override;
	};


	class abs : public unary
	{
		//dziedzicze *left
		//dziedzicze priority prywatnie
	public:
		abs(wyrazenie *w) : unary(w) { }
		double oblicz() override;
		std::string opis() override;
	};


	class opp : public unary
	{
		//dziedzicze *left
		//dziedzicze priority prywatnie
	public:
		opp(wyrazenie *w) : unary(w) { }
		double oblicz() override;
		std::string opis() override;
	};


	class inv : public unary
	{
		//dziedzicze *left
		//dziedzicze priority prywatnie
	public:
		inv(wyrazenie *w) : unary(w) { }
		double oblicz() override;
		std::string opis() override;
	};



	class binary : public unary    //abstrakcyjna
	{
	protected:
		wyrazenie *right;
		//dziedzicze *left;
		const int priority; //nadpisuje
		const std::string op;

	public:
		binary(wyrazenie *l, wyrazenie *r, std::string o, int prior) : unary(l), right(r), op(o), priority(prior) { }
		int getPriority() override;
		std::string opis() override;
	};



	class dodaj : public binary
	{
		//dziedzicze *left;
		//dziedzicze *right;
		//dziedzicze priority
		//dziedzicze op
		//dziedzicze getPriority()
		//dziedzicze opis()
	public:
		dodaj(wyrazenie *l, wyrazenie *r) : binary(l, r, "+", 600) { }
		double oblicz() override;
	};


	class odejmij : public binary
	{
		//dziedzicze *left;
		//dziedzicze *right;
		//dziedzicze priority
		//dziedzicze op
		//dziedzicze getPriority()
		//dziedzicze opis()
	public:
		odejmij(wyrazenie *l, wyrazenie *r) : binary(l, r, "-", 600) { }
		double oblicz() override;
	};


	class pomnoz : public binary
	{
		//dziedzicze *left;
		//dziedzicze *right;
		//dziedzicze priority
		//dziedzicze op
		//dziedzicze getPriority()
		//dziedzicze opis()
	public:
		pomnoz(wyrazenie *l, wyrazenie *r) : binary(l, r, "*", 700) { }
		double oblicz() override;
	};


	class podziel : public binary
	{
		//dziedzicze *left;
		//dziedzicze *right;
		//dziedzicze priority
		//dziedzicze op
		//dziedzicze getPriority()
		//dziedzicze opis()
	public:
		podziel(wyrazenie *l, wyrazenie *r) : binary(l, r, "/", 700) { }
		double oblicz() override;
	};


	class modulo : public binary
	{
		//dziedzicze *left;
		//dziedzicze *right;
		//dziedzicze priority
		//dziedzicze op
		//dziedzicze getPriority
		//dziedzicze opis
	public:
		modulo(wyrazenie *l, wyrazenie *r) : binary(l, r, "%", 700) { }
		double oblicz() override;
	};


	class poteguj : public binary
	{
		//dziedzicze *left;
		//dziedzicze *right;
		//dziedzicze priority
		//dziedzicze op
		//dziedzicze getPriority
		//dziedzicze opis
	public:
		poteguj(wyrazenie *l, wyrazenie *r) : binary(l, r, "^", 800) { }
		double oblicz() override;
		char getAssociativity() override;
	};


	class log : public binary
	{
		//dziedzicze *left;
		//dziedzicze *right;
		//dziedzicze priority
		//dziedzicze op
		//dziedzicze getPriority
	public:
		log(wyrazenie *l, wyrazenie *r) : binary(l, r, "log", 900) { }
		double oblicz() override;
		std::string opis() override;
	};




	//jakbym sobie chcial zdefiniowac logarytm to musze nadpisac funkcje opis()















	/*class zmienna : public wyrazenie
	{
	private:
		std::string name;
		double value;
	public:
		zmienna::zmienna(std::string n);
		zmienna::zmienna(std::string n, double v);
		void set(double v);
		double oblicz() override;
		std::string opis() override;
	};






	class stala : public wyrazenie
	{
	private:
	static std::map<std::string, double> constants;
	std::string name;
	public:
	stala(std::string n);
	double oblicz() override;
	std::string opis() override;
	};*/


}

#endif