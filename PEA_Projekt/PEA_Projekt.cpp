// PEA_Projekt.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include<fstream>
#include "AdjacencyMatrix.h"
#include "Path.h"
#include "TS_DynamicProgramming.h"
#include "TS_BranchAndBound.h"
#include "TS_BruteForce.h"
#include "TS_SimulatedAnnealing.h"
#include "TimeCounter.h"
#include "BulkDataTester.h"

int main(int argc, char** argv)
{
	AdjacencyMatrix* lastAM = new AdjacencyMatrix();

	if (argc > 1 && std::string(argv[1]) == "SA") {
		if (argc < 10) {
			std::cout << "algortihm filename param1 param2 tempdroptype tstart tmin max_iterations verb" << std::endl;
		}
		else {
			std::string fileName = std::string(argv[2]);
			float param1 = atof(argv[3]);
			float param2 = atof(argv[4]);
			int tempDrop = atoi(argv[5]);
			int tstart = atoi(argv[6]);
			int tmin = atoi(argv[7]);
			int max_iterations = atoi(argv[8]);
			int verbose = atoi(argv[9]);
			lastAM = new AdjacencyMatrix(fileName);
			//lastAM->Display(std::cout);
			lastAM->DisplayDetails(std::cout);

			if (lastAM != NULL) {
				//TimeCounter* timeCounter = new TimeCounter();
				//timeCounter->ResetCounter();
				//timeCounter->StartNextMeasurement();
				AlgorithmResultContainer* result = TS_SimulatedAnnealing::UseSimulatedAnnealing(
					lastAM,
					tstart,
					tmin,
					param1,
					param2,
					max_iterations,
					TS_SimulatedAnnealing::tempDropFunctions(tempDrop),
					TS_SimulatedAnnealing::changeTypes::swap,
					verbose);
				//timeCounter->EndSingleMeasurement();
				//std::cout << "Czas wykonania algorytmu: " << timeCounter->Summarize() << "ms" << std::endl;
				result->path->Display(std::cout);
			}
			else {
				std::cout << "lastAM null" << std::endl;
			}
		}
	}
	else {

		int action = 0;

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
			std::cout << "8. Branch & Bound" << std::endl;
			std::cout << "9. Pomiary dla etapu 1." << std::endl;
			std::cout << "10. Wyzarzanie" << std::endl;
			std::cout << "11. Funkcja celu: greedy solution" << std::endl;

			std::cin >> action;

			switch (action) {
			case 1:
			{
				std::string fileName;
				std::cout << "Podaj nazwe pliku: ";
				std::cin >> fileName;

				lastAM = new AdjacencyMatrix(fileName);
				lastAM->Display(std::cout);
				lastAM->DisplayDetails(std::cout);
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
				Path* path = new Path(lastAM);
				path->GenerateRandom(lastAM->GetSize());
				path->Display(std::cout);
			}
			break;
			case 5:
			{
				Path* path = new Path(lastAM);
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
					path->InsertEdge(PathEdge(from, to));
				} while (weight != -1);
				path->Display(std::cout);
			}
			break;
			case 6:
			{
				if (lastAM != NULL) {
					TimeCounter* timeCounter = new TimeCounter();
					timeCounter->ResetCounter();
					timeCounter->StartNextMeasurement();
					Path* path = TS_BruteForce::UseBruteForce(lastAM, 0, 0);
					timeCounter->EndSingleMeasurement();
					std::cout << "Czas wykonania algorytmu: " << timeCounter->Summarize() << "ms" << std::endl;
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
					TimeCounter* timeCounter = new TimeCounter();
					timeCounter->ResetCounter();
					timeCounter->StartNextMeasurement();
					AlgorithmResultContainer* result = TS_DynamicProgramming::UseDynamicProgramming(lastAM, 0, false);
					timeCounter->EndSingleMeasurement();
					std::cout << "Czas wykonania algorytmu: " << timeCounter->Summarize() << "ms" << std::endl;
					result->path->Display(std::cout);
				}
				else {
					std::cout << "lastAM null" << std::endl;
				}
			}
			break;
			case 8:
			{
				if (lastAM != NULL) {
					TimeCounter* timeCounter = new TimeCounter();
					timeCounter->ResetCounter();
					timeCounter->StartNextMeasurement();
					AlgorithmResultContainer* result = TS_BranchAndBound::UseBranchAndBound(lastAM, 0);
					timeCounter->EndSingleMeasurement();
					std::cout << "Czas wykonania algorytmu: " << timeCounter->Summarize() << "ms" << std::endl;
					result->path->Display(std::cout);
				}
				else {
					std::cout << "lastAM null" << std::endl;
				}
			}
			break;
			case 9:
			{
				std::string path;
				std::cout << "Sciezka do listy plikow (lista powinna byc w tym samym folderze co dane): " << std::endl;
				std::cin >> path;
				BulkDataTester tester = BulkDataTester();
				tester.LoadFileNames(path, std::cout);
				std::ofstream results_file;
				std::string pathToResults = tester.basePath + "\\testing_RESULTS.txt";
				results_file.open(pathToResults);
				std::cout << "Wyniki w " << pathToResults << std::endl;

				std::cout << "== TEST DP: ==" << std::endl;
				results_file << "== TEST DP: ==" << std::endl;
				tester.TestAlgorithm(TS_DynamicProgramming::UseDynamicProgramming, results_file, std::cout, 10);
				std::cout << "== TEST B&B: ==" << std::endl;
				results_file << "== TEST B&B: ==" << std::endl;
				tester.TestAlgorithm(TS_BranchAndBound::UseBranchAndBound, results_file, std::cout, 10);
			}
			case 10:
			{
				if (lastAM != NULL) {
					TimeCounter* timeCounter = new TimeCounter();
					timeCounter->ResetCounter();
					timeCounter->StartNextMeasurement();
					AlgorithmResultContainer* result = TS_SimulatedAnnealing::UseSimulatedAnnealing(
						lastAM,
						100,
						1,
						0.99,
						2.0,
						500,
						TS_SimulatedAnnealing::tempDropFunctions::linear,
						TS_SimulatedAnnealing::changeTypes::swap);
					timeCounter->EndSingleMeasurement();
					std::cout << "Czas wykonania algorytmu: " << timeCounter->Summarize() << "ms" << std::endl;
					result->path->Display(std::cout);
				}
				else {
					std::cout << "lastAM null" << std::endl;
				}
			}
			break;
			case 11:
			{
				Path* path = new Path(lastAM);
				path->GenerateGreedySolution(1);
				path->Display(std::cout);
			}
			break;
			}
		}
	}
}