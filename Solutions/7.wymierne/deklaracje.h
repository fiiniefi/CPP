#ifndef OBLICZENIA
#define OBLICZENIA
#pragma warning( disable : 4290 )
#include "stdafx.h"
#include <iostream>


namespace obliczenia
{
	class wyjatek_wymierny;
	class dzielenie_przez_0;
	class przekroczenie_zakresu;
	class wymierna;


	class wyjatek_wymierny : public std::runtime_error
	{
	public:
		using std::runtime_error::runtime_error;
	protected:
		wyjatek_wymierny(wyjatek_wymierny &pattern) noexcept : runtime_error(pattern.what()) { }
	};


	class dzielenie_przez_0 : public wyjatek_wymierny
	{
		using wyjatek_wymierny::wyjatek_wymierny;
	};


	class przekroczenie_zakresu : public wyjatek_wymierny
	{
		using wyjatek_wymierny::wyjatek_wymierny;
	};



	class wymierna
	{
	public:
		wymierna(int licz = 0, int mian = 1) throw(dzielenie_przez_0);
		wymierna(const wymierna &pattern) noexcept;   //kompilator chyba zrobilby to samo, ale co mi szkodzi napisac to jawnie
		wymierna& operator=(const wymierna &pattern) noexcept;   //kompilator chyba zrobilby to samo, ale co mi szkodzi napisac to jawnie
		int getNumerator() const noexcept;
		int getDenominator() const noexcept;
		explicit operator int() noexcept;
		explicit operator double() noexcept;

		friend wymierna operator-(const wymierna &pattern) noexcept;
		friend wymierna operator!(const wymierna &pattern) throw(dzielenie_przez_0);
		friend std::ostream& operator<<(std::ostream &output, const wymierna &pattern) noexcept;
		friend const wymierna operator+(const wymierna &first, const wymierna &second) throw(przekroczenie_zakresu);
		friend const wymierna operator-(const wymierna &first, const wymierna &second) throw(przekroczenie_zakresu);
		friend const wymierna operator*(const wymierna &first, const wymierna &second) throw(przekroczenie_zakresu);
		friend const wymierna operator/(const wymierna &first, const wymierna &second) throw(przekroczenie_zakresu, dzielenie_przez_0);



	private:
		int licznik;
		int mianownik;

		friend int nwd(int a, int b) noexcept;
		friend int nww(int a, int b) throw(przekroczenie_zakresu);
		friend bool isPeriod(int a) noexcept;
		friend std::string make(int a, int b) noexcept;
		friend int mod(int a, int b) noexcept;
	};
}



#endif