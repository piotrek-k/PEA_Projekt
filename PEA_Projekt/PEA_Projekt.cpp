// PEA_Projekt.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "AdjacencyMatrix.h"

int main()
{
	int action = 0;
	while (true) {
		std::cout << "============" << std::endl;
		std::cout << "PROBLEM KOMIWOJAZERA" << std::endl;
		std::cout << "============" << std::endl << std::endl;
		 
		std::cout << "1. Zaladuj z pliku" << std::endl;
		std::cout << "2. Wygeneruj losowo" << std::endl;
		std::cout << "3. Wprowadz recznie" << std::endl;

		std::cin >> action;

		switch (action) {
		case 1:
		{
			std::string fileName;
			std::cout << "Podaj nazwe pliku: ";
			std::cin >> fileName;

			AdjacencyMatrix* am = new AdjacencyMatrix(fileName);
			am->Display(std::cout);
		}
		break;
		case 2:
		{
			AdjacencyMatrix* am = new AdjacencyMatrix();
			std::cout << "Podaj wielkosc:  ";
			int size = 0;
			std::cin >> size;
			std::cout << "Podaj min:  ";
			int min = 0;
			std::cin >> min;
			std::cout << "Podaj max:  ";
			int max = 0;
			std::cin >> max;
			am->BuildRandomly(size, min, max);
			am->Display(std::cout);
		}
		break;
		case 3:
		{
			std::cout << "Wpisz manualnie: ";
			AdjacencyMatrix* am2 = new AdjacencyMatrix();
			am2->LoadDataFromStream(std::cin, &std::cout);

			am2->Display(std::cout);
		}
		break;
		}
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
