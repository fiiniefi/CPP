#include "stdafx.h"
#include <iostream>
#include "deklaracje.h"
#include <functional>
#include <string>

using namespace struktury;

void tests();
void pointer_tests();
void program();

int main()
{
	//tests();
	//pointer_tests();
	program();
}



void tests()
{
	bst<int> t(5);

	t.insert(5);
	t.insert(4);
	t.insert(10);
	std::cout << t << std::endl;
	t.remove(5);
	t.remove(11);
	t.insert(11);
	t.insert(7);
	std::cout << t << std::endl;
	bst<int> t2 = t;
	std::cout << t2 << std::endl;
	bst<int> t3 = std::move(t2);
	std::cout << t3 << std::endl;
	t3.insert(55);
	t3.insert(1);
	t3.insert(8);
	std::cout << t3 << std::endl << t << std::endl;
	t = t3;
	std::cout << t << std::endl;
	t3.insert(10);
	t3.remove(10);
	std::cout << t3 << std::endl;
	t3.remove(4);
	t3.remove(1);
	t3.remove(55);
	t3.remove(7);
	t = std::move(t3);
	std::cout << t << std::endl;
	std::cout << t.find(11) << t.find(55) << std::endl;
	std::initializer_list<int> ini = { 1,2,3,4,5,6 };
	bst<int> t4(ini);
	std::cout << t4 << std::endl;
}


void pointer_tests()
{
	int *x1, *x2, *x3, *x4;
	int y1 = 1;
	int y2 = 2;
	int y3 = 3;
	int y4 = 4;
	x1 = &y1;
	x2 = &y2;
	x3 = &y3;
	x4 = &y4;

	bst<int*> tree;
	tree.insert(x3);
	tree.insert(x4);
	tree.insert(x1);
	tree.insert(x2);
	std::cout << tree << std::endl;
}


void program()
{
	bst<double> *tree = new bst<double>();
	std::cout << "add x - add value x to your BST\nremove x - remove value x from your BST\nfind x - check if x is inside your BST\nprint - print your BST in-order\nexit - turn off the program\n\n";
	while (true)
	{
		std::string command;
		std::cin >> command;
		if (command == "add")
		{
			double x;
			std::cin >> x;
			tree->insert(x);
			std::cout << "Value added" << std::endl;
		}
		else if (command == "remove")
		{
			double x;
			std::cin >> x;
			bool y = tree->remove(x);
			if (y)
				std::cout << "Value successfully removed" << std::endl;
			else
				std::cout << "Value " << x << " is not in your BST" << std::endl;
		}
		else if (command == "find")
		{
			double x;
			std::cin >> x;
			bool y = tree->find(x);
			if (y)
				std::cout << "Value " << x << " is inside your BST" << std::endl;
			else
				std::cout << "Value " << x << " is not in your BST" << std::endl;
		}
		else if (command == "print")
		{
			std::cout << *tree << std::endl;
		}
		else if (command == "exit")
		{
			std::cout << "Program closed" << std::endl;
			delete tree;
			return;
		}
	}
}