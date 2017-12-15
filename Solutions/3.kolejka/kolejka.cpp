#include "stdafx.h"
#include <iostream>
#include <string>
#include <limits>
#include "deklaracje.h"


int main()
{
	std::cout << "TESTUJE SYTUACJE WYJATKOWE:\n" << std::endl;
	kolejka *k;
	try
	{
		std::initializer_list<std::string> lista({ "asd", "dsa", "cda", "acd", "cda", "cdb" });
		k = new kolejka(5, lista);
	}
	catch (std::string message)
	{
		std::cout << message << std::endl;
	}

	k = new kolejka();

	try
	{
		k->pobierz();
	}
	catch (std::string message)
	{
		std::cout << message << std::endl;
	}

	try
	{
		for (int i = 0; i < 5; i++)
			k->wstaw("asd");
	}
	catch (std::string message)
	{
		std::cout << message << std::endl;
	}

	try  //czy dodalo nie wiecej niz 4 elementy
	{
		for (int i = 0; i < 5; i++)
			std::cout << k->pobierz() << std::endl;
	}
	catch (std::string message)
	{
		std::cout << message << std::endl;
	}

	delete k;

	/**************************************************************************************************************************************************************/

	std::cout << "PROGRAM UZYTKOWY:\n\n";

	std::cout << "Command list:\nexit - finish a session\nadd X - add X to your queue\ntake - get element from queue\n\n\n";

	int n;
	std::string command;
	std::cout << "Enter valid size of queue    ";

	while (!(std::cin >> n) || n <= 0)
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	k = new kolejka(n);
	std::cout << "\n\n\nSession started on queue in size " << n << std::endl << std::endl;

	while (true)
	{
		std::getline(std::cin, command);
		std::cout << std::endl;
		if (command == "exit")
			break;
		else if (command[0] == 'a' && command[1] == 'd' && command[2] == 'd' && command[3] == ' ' && command != "add ")
		{
			command = &command[4];
			try
			{
				k->wstaw(command);
				std::cout << "Element successfully added\n";
			}

			catch (std::string message)
			{
				std::cout << message << std::endl << std::endl;
			}
		}

		else if (command == "take")
		{
			try
			{
				std::cout << k->pobierz() << std::endl;
			}
			catch (std::string message)
			{
				std::cout << message << std::endl << std::endl;
			}
		}
	}

	std::cout << "\n\nSession closed\n";
	return 0;
}

