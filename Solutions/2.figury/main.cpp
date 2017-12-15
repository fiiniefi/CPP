#include "stdafx.h"
#include <iostream>
#include "deklaracje.h"


int main()
{
	punkt pfirst;
	punkt psecond = punkt(4.2, 5.7);
	punkt pthird = psecond;
	std::cout << "\tPUNKTY\n\n";
	std::cout << "pfirst po zwyklym konstruktorze: " << pfirst << std::endl << "psecond po konstruktorze kopiujacym: " << psecond << std::endl << "pthird po zainicjalizowaniu psecond: " << pthird << std::endl;
	punkt pfourth = punkt(-3.4, 2.1);
	pthird = pfourth;
	std::cout << "pfourth po zwyklym konstruktorze: " << pfourth << std::endl << "pthird po przypisaniu pfourth: " << pthird << std::endl;
	pthird.move(9.4, -6.1);
	std::cout << "pthird po przesunieciu o (9.4, -6.1): " << pthird << std::endl;
	std::cout << "odleglosc miedzy pfirst, a pthird: " << distance(pfirst, pthird) << std::endl << std::endl;
	std::cout << "\n\tODCINKI\n\n";
	punkt ofirstinia = punkt(4.2, 8.5);
	punkt ofirstinib = punkt(-1.2, 0.4);
	odcinek ofirst = odcinek(ofirstinia, ofirstinib);
	odcinek osecond = ofirst;
	std::cout << "ofirst po zwyklym konstruktorze: " << ofirst << "osecond po konstruktorze kopiujacym: " << osecond << std::endl;
	punkt othirdinia = punkt(3.4, 2);
	punkt othirdinib = punkt(0, -3.4);
	odcinek othird = odcinek(othirdinia, othirdinib);
	osecond = othird;
	std::cout << "othird po zwyklym konstruktorze: " << othird << "osecond po przypisaniu othird: " << osecond << std::endl;
	osecond.move(2.1, 0.4);
	std::cout << "osecond po przesunieciu o (2.1, 0.4): " << osecond << std::endl;
	osecond.rotation(3.4, 2.3, 84);
	std::cout << "osecond po obroceniu wokol punktu (3.4,2.3) o 84 stopni: " << osecond << std::endl;
	std::cout << "dlugosc osecond: " << osecond.length() << std::endl << std::endl;
	punkt ofourthinia = punkt(3, 2);
	punkt ofourthinib = punkt(2, 1);
	odcinek ofourth = odcinek(ofourthinia, ofourthinib);
	std::cout << "ofourth po zwyklym konstruktorze: " << ofourth;
	punkt pfifth = punkt(2.5, 1.5);
	punkt psixth = punkt(2, 1);
	punkt pseventh = punkt(2.3, 1.2);
	std::cout << "czy (2.5,1.5) lezy na odcinku ofourth: " << ofourth.onSegment(pfifth) << ", czy (2.3,1.2) lezy na odcinku ofourth: " << ofourth.onSegment(pseventh) << std::endl;
	std::cout << "srodek odcinka ofourth: " << ofourth.midpoint() << std::endl << std::endl;
	punkt ofifthinia = punkt(2, 4);
	punkt ofifthinib = punkt(4, 6);
	odcinek ofifth = odcinek(ofifthinia, ofifthinib);
	punkt osixthinia = punkt(2, 4);
	punkt osixthinib = punkt(4, 2);
	odcinek osixth = odcinek(osixthinia, osixthinib);
	punkt oseventhinia = punkt(4, 6);
	punkt oseventhinib = punkt(6, 8);
	odcinek oseventh = odcinek(oseventhinia, oseventhinib);
	std::cout << "czy (2,4)-(4,6) jest rownolegly do (2,4)-(4,2): " << parallel(ofifth, osixth) << std::endl;
	std::cout << "czy (2,4)-(4,6) jest rownolegly do (4,6)-(6,8): " << parallel(ofifth, oseventh) << std::endl;
	std::cout << "czy (2,4)-(4,6) jest prostopadly do (4,6)-(6-8): " << perpendicular(ofifth, oseventh) << std::endl;
	std::cout << "czy (2,4)-(4,6) jest prostopadly do (2,4)-(4,2): " << perpendicular(ofifth, osixth) << std::endl;
	std::cout << "punkt przeciecia (2,4)-(4,6) z (2,4)-(4,2): " << ofifth.intercept(osixth) << std::endl << std::endl;

	std::cout << "\n\tTROJKATY\n\n";

	punkt fftr = punkt(1, 3);
	punkt fstr = punkt(4, 4);
	punkt fttr = punkt(3, 7);
	trojkat tfirst = trojkat(fftr, fstr, fttr);
	std::cout << "obwod trojkata (1,3)-(4,4)-(3,7): " << tfirst.circuit() << std::endl;
	std::cout << "pole trojkata (1,3)-(4,4)-(3,7): " << tfirst.area() << std::endl;

	punkt inside = punkt(3, 5);
	punkt outside = punkt(4, 6);
	std::cout << "czy (3,5) lezy w srodku trojkata (1,3)-(4,4)-(3,7): " << tfirst.isInside(inside) << std::endl;
	std::cout << "czy (4,6) lezy w srodku trojkata (1,3)-(4,4)-(3,7): " << tfirst.isInside(outside) << std::endl;
	std::cout << "srodek trojkata (1,3)-(4,4)-(3,7): " << tfirst.middle() << std::endl;

	punkt sftr = punkt(2, 1);
	punkt sstr = punkt(4, 2);
	punkt sttr = punkt(3, 5);
	punkt sttr2 = punkt(3, 3);
	trojkat tsecond = trojkat(sftr, sstr, sttr);
	trojkat tthird = trojkat(sftr, sstr, sttr2);
	std::cout << "czy trojkaty (1,3)-(4,4)-(3,7) i (2,1)-(4,2)-(3,5) sa rozlaczne: " << separable(tfirst, tsecond) << std::endl;
	std::cout << "czy trojkaty (1,3)-(4,4)-(3,7) i (2,1)-(4,2)-(3,3) sa rozlaczne: " << separable(tfirst, tthird) << std::endl;

	punkt tftr = punkt(1, 3);
	punkt tstr = punkt(5, 4);
	punkt tttr = punkt(3, 9);
	trojkat tfourth = trojkat(tftr, tstr, tttr);

	std::cout << "czy trojkat (1,3)-(4,4)-(3,7) jest zawarty w trojkacie (2,1)-(4,2)-(3,5): " << included(tfirst, tsecond) << std::endl;
	std::cout << "czy trojkat (1,3)-(4,4)-(3,7) jest zawarty w trojkacie (1,3)-(4,4)-(3,7): " << included(tfirst, tfirst) << std::endl;
	std::cout << "czy trojkat (1,3)-(4,4)-(3,7) jest zawarty w trojkacie (1,3)-(5,4)-(3,9): " << included(tfirst, tfourth) << std::endl;
	std::cout << "czy trojkat (1,3)-(5,4)-(3,9) jest zawarty w trojkacie (1,3)-(4,4)-(3,7): " << included(tfourth, tfirst) << std::endl;
}