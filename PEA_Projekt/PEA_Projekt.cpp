// PEA_Projekt.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "AdjacencyMatrix.h"
#include "Path.h"
#include "TS_ProblemSolver.h"

int main()
{
	int action = 0;
	AdjacencyMatrix* lastAM = new AdjacencyMatrix();
	while (true) {
		std::cout << "============" << std::endl;
		std::cout << "PROBLEM KOMIWOJAZERA" << std::endl;
		std::cout << "============" << std::endl << std::endl;

		std::cout << "1. Macierz: zaladuj z pliku" << std::endl;
		std::cout << "2. Macierz: generowanie losowe" << std::endl;
		std::cout << "3. Macierz: wprowadzanie reczne" << std::endl;
		std::cout << "4. Funkcja celu: permutacja losowa" << std::endl;
		std::cout << "5. Funkcja celu: wprowadzanie reczne" << std::endl;
		std::cout << "6. Brute Force" << std::endl;
		std::cout << "7. Dynamic programming" << std::endl;

		std::cin >> action;

		switch (action) {
		case 1:
		{
			std::string fileName;
			std::cout << "Podaj nazwe pliku: ";
			std::cin >> fileName;

			lastAM = new AdjacencyMatrix(fileName);
			lastAM->Display(std::cout);
		}
		break;
		case 2:
		{
			lastAM = new AdjacencyMatrix();
			std::cout << "Podaj wielkosc:  ";
			int size = 0;
			std::cin >> size;
			std::cout << "Podaj min:  ";
			int min = 0;
			std::cin >> min;
			std::cout << "Podaj max:  ";
			int max = 0;
			std::cin >> max;
			lastAM->BuildRandomly(size, min, max);
			lastAM->Display(std::cout);
		}
		break;
		case 3:
		{
			std::cout << "Wpisz recznie: ";
			lastAM = new AdjacencyMatrix();
			lastAM->LoadDataFromStream(std::cin, &std::cout);

			lastAM->Display(std::cout);
		}
		break;
		case 4:
		{
			Path* path = new Path();
			path->GenerateRandom(lastAM, lastAM->GetSize());
			path->Display(std::cout);
		}
		break;
		case 5:
		{
			Path* path = new Path();
			std::cout << "WprowadŸ dane (-1 konczy wprowadzanie):" << std::endl;
			int weight = 0;
			int from = 0;
			int to = 0;
			do {
				std::cout << "Waga: " << std::endl;
				std::cin >> weight;

				if (weight == -1) {
					break;
				}

				std::cout << "Od: " << std::endl;
				std::cin >> from;
				std::cout << "Do: " << std::endl;
				std::cin >> to;
				path->InsertEdge(Edge(from, to, weight));
			} while (weight != -1);
			path->Display(std::cout);
		}
		break;
		case 6:
		{
			if (lastAM != NULL) {
				Path* path = TS_ProblemSolver::UseBruteForce(lastAM, 0, 0);
				path->Display(std::cout);
			}
			else {
				std::cout << "lastAM null" << std::endl;
			}
		}
		break;
		case 7:
		{
			if (lastAM != NULL) {
				Path* path = TS_ProblemSolver::UseDynamicProgramming(lastAM, 0, 0);
				path->Display(std::cout);
			}
			else {
				std::cout << "lastAM null" << std::endl;
			}
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
