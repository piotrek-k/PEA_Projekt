#include "TS_ProblemSolver.h"
#include <math.h>
#include <bitset>
#include "DP_CombinationInfo.h"

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
	if (currentlyCheckedPath->GetNumberOfNodes() == matrix->GetSize()) {
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
	std::cout << "combination " << ": [";
	for (int i = 0; i < v.size(); ++i) { std::cout << v[i] + 1 << " "; }
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
void TS_ProblemSolver::DynamicProgramming_GenerateCombinations(AdjacencyMatrix* matrix, int k, DP_CombinationInfo** calculatedValues, int startPoint, int endPoint, bool verbose, std::vector<int> combination, int offset)
{
	int numberOfNodes = matrix->GetSize();

	if (k == 0) {
		DynamicProgramming_CheckCombination(matrix, calculatedValues, startPoint, endPoint, verbose, combination);
		return;
	}
	for (int i = offset; i <= numberOfNodes - k; ++i) {
		if (i == startPoint) {
			continue;
		}
		combination.push_back(i);
		DynamicProgramming_GenerateCombinations(matrix, k - 1, calculatedValues, startPoint, endPoint, verbose, combination, i + 1);
		combination.pop_back();
	}

	return;
}

void TS_ProblemSolver::DynamicProgramming_CheckCombination(AdjacencyMatrix* matrix, DP_CombinationInfo** calculatedValues, int startPoint, int endPoint, bool verbose, std::vector<int> combination)
{
	// Wnêtrze funkcji przetwarza pojedynczy podzbiór S (combination) wraz z wszystkimi zakoñczeniami

	//int minimumOfAllEndings = INT_MAX;

	if (verbose) {
		pretty_print(combination);
	}

	/**
	 * Obliczanie minimalnej d³ugoœci drogi przechodz¹cej przez wszystkie punkty S (combination)
	 * i koñcz¹cej siê na wêŸle "destPointIndexInMatrix"
	 **/
	for (int destPointPositionInS = 0; destPointPositionInS < combination.size(); destPointPositionInS++) {
		int destPointIndexInMatrix = combination[destPointPositionInS];

		DynamicProgramming_D(matrix, calculatedValues, startPoint, endPoint, destPointIndexInMatrix, verbose, combination);
	}
}

/// <summary>
/// Optymalna d³ugoœæ œcie¿ki wychodz¹cej z startingPoint,
/// przechodz¹cej przez punkty z "combination" i koñcz¹cej siê na destPointIndexInMatrix.
/// Obliczana wartoœæ to minimum z kosztów kombinacji nie zawieraj¹cych destPointIndexInMatrix.
/// </summary>
int TS_ProblemSolver::DynamicProgramming_D(AdjacencyMatrix* matrix, DP_CombinationInfo** calculatedValues, int startPoint, int endPoint, int destPointIndexInMatrix, bool verbose, std::vector<int> combination)
{
	/**
	 * Utworzenie indeksu (np. dla zbioru [2,3]: 00001100)
	 **/
	int storageIndexOfCombination = 0; // interpretowaæ jako wartoœæ binarna. 1 - oznacza wierzcho³ek brany pod uwagê
	for (int a = 0; a < combination.size(); a++) {
		storageIndexOfCombination |= 1 << combination[a];
	}

	//std::cout << "Ustalanie kosztow dla kombinacji: " << storageIndexOfCombination;

	int storageIndexWithoutDestPoint = storageIndexOfCombination & ~(1 << destPointIndexInMatrix);

	if (verbose) {
		std::cout << "* storageIndexOfCombination " << print_binary(storageIndexOfCombination) << " withoutdestpoint " << print_binary(storageIndexWithoutDestPoint) << " destPoint: " << destPointIndexInMatrix << std::endl;
	}

	int foundMinValue = INT_MAX;
	int stepToMinimumCost = -1;

	for (int b = 0; b < combination.size(); b++) {
		int indexToCheck = combination[b];
		if (indexToCheck == destPointIndexInMatrix) {
			continue;
		}
		if (verbose) {
			std::cout << "* * checking index " << indexToCheck << "(" << print_binary(storageIndexWithoutDestPoint) << ")" << " with cost: " << calculatedValues[storageIndexWithoutDestPoint]->GetCostToDirection(indexToCheck) << "+" << matrix->GetWeightOfEdge(indexToCheck, destPointIndexInMatrix) << std::endl;
		}
		int candidate = calculatedValues[storageIndexWithoutDestPoint]->GetCostToDirection(indexToCheck) + matrix->GetWeightOfEdge(indexToCheck, destPointIndexInMatrix);
		if (foundMinValue > candidate) {
			foundMinValue = candidate;
			stepToMinimumCost = indexToCheck;
		}
	}

	calculatedValues[storageIndexOfCombination]->SetCombinationCostToDirection(destPointIndexInMatrix, foundMinValue);

	calculatedValues[storageIndexWithoutDestPoint]->TrySetMinimumStep(destPointIndexInMatrix, stepToMinimumCost, foundMinValue);
	if (verbose) {
		std::cout << "* Saving " << foundMinValue << " into " << print_binary(storageIndexOfCombination) << ":" << destPointIndexInMatrix << std::endl;
		std::cout << "* StepToMinimum dla " << print_binary(storageIndexWithoutDestPoint) << ": " << stepToMinimumCost << std::endl;
	}

	return foundMinValue;
}

Path* TS_ProblemSolver::UseDynamicProgramming(AdjacencyMatrix* matrix, int startingPoint, int endPoint, bool verbose)
{
	const int possibleVerticesCombinations = (int)pow(2, matrix->GetSize());
	DP_CombinationInfo** calculatedValues = new DP_CombinationInfo * [possibleVerticesCombinations + 1];

	/**
	  * Utworzenie tablicy
	  **/
	for (int x = 0; x <= possibleVerticesCombinations; x++) {
		calculatedValues[x] = new DP_CombinationInfo(matrix->GetSize());
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
			calculatedValues[1 << pointIndex]->SetCombinationCostToDirection(pointIndex, matrix->GetWeightOfEdge(startingPoint, pointIndex));
			calculatedValues[1 << pointIndex]->TrySetMinimumStep(pointIndex, startingPoint, matrix->GetWeightOfEdge(startingPoint, pointIndex));
		}
		if (verbose) {
			std::cout << "combination [ " << pointIndex << "] " << calculatedValues[1 << pointIndex]->GetCostToDirection(pointIndex) << std::endl;
		}
	}

	/**
	  * Wype³nienie tablicy calculatedValues dla wszystkich pozosta³ych wielkoœci podzbiorów
	  **/
	for (int setSize = 2; setSize < matrix->GetSize(); setSize++) {
		TS_ProblemSolver::DynamicProgramming_GenerateCombinations(matrix, setSize, calculatedValues, 0, 0, verbose, std::vector<int>(), 0);
	}

	/**
	  * Znalezienie minimalnej drogi dla wszystkich wêz³ów
	  **/
	std::vector<int> combination = std::vector<int>();
	for (int pointIndex = 0; pointIndex < matrix->GetSize(); pointIndex++) {
		combination.push_back(pointIndex);
	}
	int minValue = DynamicProgramming_D(matrix, calculatedValues, startingPoint, endPoint, endPoint, verbose, combination);

	if (verbose) {
		std::cout << "minValue:" << minValue << std::endl; //" stepToMin: " << nextStepOfMin
	}
	else {
		std::cout << "Uzyskana najkrotsza droga: " << minValue << std::endl;
	}

	/**
	  * Generowanie œcie¿ki
	  **/
	Path* path = new Path(matrix);
	int edgeBegin = endPoint;
	int edgeEnd = -1;
	int storageIndexPath = (1 << matrix->GetSize()) - 1;
	for (int a = 0; a < matrix->GetSize(); a++) {
		storageIndexPath &= ~(1 << edgeBegin);
		edgeEnd = calculatedValues[storageIndexPath]->GetMinimumStepForDirection(edgeBegin);
		if (edgeEnd == -1) {
			edgeEnd = startingPoint;
		}
		path->InsertEdge(PathEdge(edgeBegin, edgeEnd));
		edgeBegin = edgeEnd;
	}

	for (int x = 0; x <= possibleVerticesCombinations; x++) {
		delete calculatedValues[x];
	}
	delete[] calculatedValues;
	calculatedValues = NULL;

	return path;
}

// 1. sprawdziæ poprawnoœæ po³¹czeñ z pierwszym i ostatnim wierzcho³kiem