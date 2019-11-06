#include "TS_ProblemSolver.h"
#include <math.h>
#include <bitset>

Path* TS_ProblemSolver::UseBruteForce(AdjacencyMatrix* matrix, int startingPoint, int endPoint)
{
	Path* tempPath = new Path();
	tempPath->SetStartingPoint(startingPoint);

	int bestValue = -1;

	Path* bestPath = new Path();

	BruteForce_SearchTree(matrix, tempPath, &bestValue, bestPath, startingPoint, endPoint);

	return bestPath;
}

void TS_ProblemSolver::BruteForce_SearchTree(AdjacencyMatrix* matrix, Path* currentlyCheckedPath, int* bestValue, Path* bestPath, int startPoint, int endPoint)
{
	if (currentlyCheckedPath->GetNumberOfNodes() == matrix->GetSize() - 1) {
		currentlyCheckedPath->InsertNodeAtTheEnd(matrix, endPoint);
		int result = currentlyCheckedPath->CalculateCost();

		if (*bestValue == -1 || result < *bestValue) {
			*bestValue = result;
			bestPath->ReplaceWithOtherInstance(*currentlyCheckedPath);
		}
		currentlyCheckedPath->RemoveLastEdge();
		return;
	}

	for (int a = 0; a < matrix->GetSize(); a++) {
		if (a == startPoint || a == endPoint) {
			continue;
		}
		if (currentlyCheckedPath->ValueCanBeConnectedToEnd(a)) {
			currentlyCheckedPath->InsertNodeAtTheEnd(matrix, a);
			BruteForce_SearchTree(matrix, currentlyCheckedPath, bestValue, bestPath, startPoint, endPoint);
			currentlyCheckedPath->RemoveLastEdge();
		}
	}
}

void pretty_print(const std::vector<int>& v) {
	static int count = 0;
	std::cout << "combination no " << (++count) << ": [ ";
	for (int i = 0; i < v.size(); ++i) { std::cout << v[i]+1 << " "; }
	std::cout << "] " << std::endl;
}

std::bitset<8> print_binary(int number) {
	std::bitset<8> x(number);
	return x;
}

/// <summary>
/// Generuje kombinacje k-elementowe bez powtórzeñ dla zbioru matrix->GetSize() elementowego.
/// </summary>
/// <param name="matrix">Struktura przechowuj¹ca dane o wierzcho³kach</param>
/// <param name="k">Argument pomocniczy przy rekurencji. Wartoœæ startowa: wielkoœæ kombinacji do wygenerowania</param>
/// <param name="calculatedValues">Referencja do tablicy przechowuj¹cej dotychczasowe minimalne drogi</param>
/// <param name="combination">Argument pomocniczy przy rekurencji. Wartoœæ startowa: pusty wektor</param>
/// <param name="offset">Argument pomocniczy przy rekurencji. Wartoœæ startowa: 0</param>
int TS_ProblemSolver::DynamicProgramming_GenerateCombinations(AdjacencyMatrix* matrix, int k, int** calculatedValues, int startPoint, int endPoint, bool verbose, std::vector<int> combination, int offset)
{
	int numberOfNodes = matrix->GetSize();

	if (k == 0) {
		return DynamicProgramming_CheckCombination(matrix, calculatedValues, startPoint, endPoint, verbose, combination);
	}
	for (int i = offset; i <= numberOfNodes - k; ++i) {
		if (i == startPoint) {
			continue;
		}
		combination.push_back(i);
		DynamicProgramming_GenerateCombinations(matrix, k - 1, calculatedValues, startPoint, endPoint, verbose, combination, i + 1);
		combination.pop_back();
	}

	return -1;
}

int TS_ProblemSolver::DynamicProgramming_CheckCombination(AdjacencyMatrix* matrix, int** calculatedValues, int startPoint, int endPoint, bool verbose, std::vector<int> combination)
{
	int minumumOfAll = INT_MAX;

	if (verbose) {
		pretty_print(combination);
	}

	// pojedynczy podzbiór S o wielkoœci setSize
	// S = combination

	/**
	 * Utworzenie indeksu
	 **/
	int storageIndexOfCombination = 0; // interpretowaæ jako wartoœæ binarna. 1 - oznacza wierzcho³ek brany pod uwagê
	for (int a = 0; a < combination.size(); a++) {
		storageIndexOfCombination |= 1 << combination[a];
	}

	/**
	 * Obliczanie minimalnej d³ugoœci drogi przechodz¹cej przez wszystkie punkty S (combination)
	 * i koñcz¹cej siê na wêŸle "destPointIndexInMatrix"
	 **/
	for (int destPointPositionInS = 0; destPointPositionInS < combination.size(); destPointPositionInS++) {
		int destPointIndexInMatrix = combination[destPointPositionInS];

		int storageIndexWithoutDestPoint = storageIndexOfCombination & ~(1 << destPointIndexInMatrix);

		if (verbose) {
			std::cout << "* storageIndexOfCombination " << print_binary(storageIndexOfCombination) << " withoutdestpoint " << print_binary(storageIndexWithoutDestPoint) << " destPoint: " << destPointIndexInMatrix + 1 << std::endl;
		}

		int foundMinValue = INT_MAX;
		for (int b = 0; b < combination.size(); b++) {
			int indexToCheck = combination[b];
			if (indexToCheck == destPointIndexInMatrix) {
				continue;
			}
			if (verbose) {
				std::cout << "* * checking " << indexToCheck + 1 << " calcVal: " << calculatedValues[storageIndexWithoutDestPoint][indexToCheck] << "+" << matrix->GetWeightOfEdge(indexToCheck, destPointIndexInMatrix) << std::endl;
			}
			if (foundMinValue > calculatedValues[storageIndexWithoutDestPoint][indexToCheck] + matrix->GetWeightOfEdge(indexToCheck, destPointIndexInMatrix)) {
				foundMinValue = calculatedValues[storageIndexWithoutDestPoint][indexToCheck] + matrix->GetWeightOfEdge(indexToCheck, destPointIndexInMatrix);
			}
		}

		calculatedValues[storageIndexOfCombination][destPointIndexInMatrix] = foundMinValue;
		if (verbose) {
			std::cout << "Saving " << foundMinValue << " into " << print_binary(storageIndexOfCombination) << " " << destPointIndexInMatrix << std::endl;
		}

		if (foundMinValue < minumumOfAll) {
			minumumOfAll = foundMinValue;
		}

		if (verbose) {
			std::cout << "minFoundValue: " << foundMinValue << std::endl;
		}
	}

	if (verbose) {
		std::cout << "minimum of all: " << minumumOfAll << std::endl;
	}

	return minumumOfAll;
}

Path* TS_ProblemSolver::UseDynamicProgramming(AdjacencyMatrix* matrix, int startingPoint, int endPoint, bool verbose)
{
	int possibleVerticesCombinations = (int)pow(2, matrix->GetSize());
	int** calculatedValues = new int* [1 << matrix->GetSize()];

	/**
	  * Utworzenie tablicy
	  **/
	for (int x = 0; x <= possibleVerticesCombinations; x++) {
		// inicjalizacja tablicy reprezentuj¹cej wierzcho³ki koñcowe dla ka¿dej z konfiguracji
		calculatedValues[x] = new int[matrix->GetSize()];
		for (int a = 0; a < matrix->GetSize(); a++) {
			calculatedValues[x][a] = 0;
		}
	}

	/**
	  * Wype³nienie minimalnych dróg dla wartoœci jednoelementowych
	  **/
	for (int pointIndex = 0; pointIndex < matrix->GetSize(); pointIndex++) {
		// odleg³oœci dla zbiorów jednoelementowych
		if (pointIndex == startingPoint) {
			continue;
		}

		if (pointIndex != startingPoint) {
			calculatedValues[1 << pointIndex][pointIndex] = matrix->GetWeightOfEdge(startingPoint, pointIndex);
		}

		std::cout << "combination [ " << pointIndex+1 << "] " << calculatedValues[1 << pointIndex][pointIndex] << std::endl;
	}

	for (int setSize = 2; setSize < matrix->GetSize(); setSize++) {
		// iteracja przez wszystkie wielkoœci podzbiorów
		// setSize = 1 zosta³ ju¿ wype³niony

		TS_ProblemSolver::DynamicProgramming_GenerateCombinations(matrix, setSize, calculatedValues, 0, 0, true, std::vector<int>(), 0);
	}

	// powinno wygenerowaæ tylko jedn¹ kombinacjê
	//int minimumPathCost = TS_ProblemSolver::DynamicProgramming_CheckCombination(matrix, calculatedValues, 0, 0, true, fullSet);
	int storageIndexWithoutStartAndDestPoint = (1 << matrix->GetSize()) - 1;
	//std::cout << "all1: " << print_binary(storageIndexWithoutStartAndDestPoint) << std::endl;
	storageIndexWithoutStartAndDestPoint = storageIndexWithoutStartAndDestPoint & ~(1 << startingPoint) & ~(1 << endPoint);
	//std::cout << "without startend: " << print_binary(storageIndexWithoutStartAndDestPoint) << std::endl;

	int minValue = INT_MAX;
	for (int pointIndex = 0; pointIndex < matrix->GetSize(); pointIndex++) {
		if (pointIndex == startingPoint || pointIndex == endPoint) {
			continue;
		}
		int candidate = calculatedValues[storageIndexWithoutStartAndDestPoint][pointIndex] + matrix->GetWeightOfEdge(pointIndex, endPoint);
		if (candidate < minValue) {
			minValue = candidate;
		}
	}
	std::cout << "minValue:" << minValue << std::endl;

	return new Path();
}

// 1. uwzglêdniæ startingPoint w obliczaniu drogi