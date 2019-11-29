#include "TS_SimulatedAnnealing.h"
#include <math.h>
#include <time.h>
#include <stdlib.h>

AlgorithmResultContainer* TS_SimulatedAnnealing::UseSimulatedAnnealing(
	AdjacencyMatrix* matrix,
	float T_0,
	float T_min,
	float T_change_param1,
	float T_change_param2,
	int maxNumOfIterations,
	tempDropFunctions tempDropType,
	changeTypes changeType,
	bool verbose)
{
	srand(time(NULL));

	Path* currentPath = new Path(matrix);
	currentPath->GenerateRandom();
	Path* bestPath = new Path(matrix);
	bestPath->ReplaceWithOtherInstance(*currentPath);
	float T = T_0;
	int iterLeft = maxNumOfIterations; // iterations left
	int revokedCount = 0;
	int worseOptionAcceptedCount = 0;
	int coolingCount = 0;

	while (T > T_min&& iterLeft > 0) {
		currentPath->ReplaceWithOtherInstance(*bestPath);
		currentPath->SwapNodes(rand() % matrix->GetSize(), rand() % matrix->GetSize());
		if (verbose) {
			currentPath->Display(std::cout);
			std::cout << " T:" << T << " ";
		}

		int costDiff = currentPath->CalculateCost() - bestPath->CalculateCost();

		if (costDiff < 0) {
			bestPath->ReplaceWithOtherInstance(*currentPath);
			if (verbose) {
				std::cout << " accepted ";
			}
		}
		else {
			double changeProbability = exp(-(double)costDiff / (double)T);
			if (verbose) {
				std::cout << " probab:" << changeProbability << " ";
			}
			double randomValue = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			if (randomValue <= changeProbability) {
				bestPath->ReplaceWithOtherInstance(*currentPath);
				worseOptionAcceptedCount++;
				if (verbose) {
					std::cout << " accepted ";
				}
			}
			else {
				revokedCount++;
				if (verbose) {
					std::cout << " revoked ";
				}
			}
		}

		iterLeft--;
		coolingCount++;
		switch (tempDropType)
		{
		case tempDropFunctions::geometric:
			T = T * pow(T_change_param1, -coolingCount);
			break;
		case tempDropFunctions::logarythmic:
			T = T_change_param1 / log(coolingCount + T_change_param2);
			break;
		case tempDropFunctions::linear:
		default:
			T = T * T_change_param1;
			break;
		}

		if (verbose) {
			std::cout << std::endl;
		}
	}

	std::cout << "Iterations: " << maxNumOfIterations - iterLeft << std::endl;
	std::cout << "Number of revoked proposals: " << revokedCount << std::endl;
	std::cout << "Number of accepted worse options: " << worseOptionAcceptedCount << std::endl;

	return new AlgorithmResultContainer(bestPath, -1);
}

void TS_SimulatedAnnealing::swapElementsInPath(Path* path)
{

}
