#include "TS_ProblemSolver.h"
#include <math.h>

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
	for (int i = 0; i < v.size(); ++i) { std::cout << v[i] << " "; }
	std::cout << "] " << std::endl;
}

/// <summary>
/// Generuje kombinacje k-elementowe bez powtórzeñ dla zbioru matrix->GetSize() elementowego.
/// </summary>
/// <param name="matrix">Struktura przechowuj¹ca dane o wierzcho³kach</param>
/// <param name="k">Argument pomocniczy przy rekurencji. Wartoœæ startowa: wielkoœæ kombinacji do wygenerowania</param>
/// <param name="calculatedValues">Referencja do tablicy przechowuj¹cej dotychczasowe minimalne drogi</param>
/// <param name="combination">Argument pomocniczy przy rekurencji. Wartoœæ startowa: pusty wektor</param>
/// <param name="offset">Argument pomocniczy przy rekurencji. Wartoœæ startowa: 0</param>
int TS_ProblemSolver::DynamicProgramming_GenerateCombinations(AdjacencyMatrix* matrix, int k, int** calculatedValues, std::vector<int> combination = std::vector<int>(), int offset = 0)
{
	int numberOfNodes = matrix->GetSize();
	int minumumOfAll = INT_MAX;

	if (k == 0) {
		pretty_print(combination);

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

			int foundMinValue = INT_MAX;
			for (int b = 0; b < combination.size(); b++) {
				if (b != destPointIndexInMatrix && foundMinValue > calculatedValues[storageIndexWithoutDestPoint][b] + matrix->GetWeightOfEdge(b, destPointIndexInMatrix)) {
					foundMinValue = calculatedValues[storageIndexWithoutDestPoint][b];
				}
			}

			calculatedValues[storageIndexOfCombination][destPointPositionInS] = foundMinValue;

			if (foundMinValue < minumumOfAll) {
				minumumOfAll = foundMinValue;
			}
		}
		return minumumOfAll;
	}
	for (int i = offset; i <= numberOfNodes - k; ++i) {
		combination.push_back(i);
		DynamicProgramming_GenerateCombinations(matrix, k - 1, calculatedValues, combination, i + 1);
		combination.pop_back();
	}

	return -1;
}

Path* TS_ProblemSolver::UseDynamicProgramming(AdjacencyMatrix* matrix, int startingPoint, int endPoint)
{
	int** calculatedValues = new int* [1 << matrix->GetSize()];

	/**
	  * Utworzenie tablicy, wype³nienie minimalnych dróg dla wartoœci jednoelementowych
	  **/
	for (int pointIndex = 0; pointIndex <= pow(2, matrix->GetSize()); pointIndex++) {
		// inicjalizacja tablicy reprezentuj¹cej wierzcho³ki koñcowe dla ka¿dej z konfiguracji
		calculatedValues[1 << pointIndex] = new int[matrix->GetSize()];

		// odleg³oœci dla zbiorów jednoelementowych
		if (pointIndex != startingPoint) {
			calculatedValues[1 << pointIndex][pointIndex] = matrix->GetWeightOfEdge(startingPoint, pointIndex);
		}
	}

	for (int setSize = 2; setSize < matrix->GetSize(); setSize++) {
		// iteracja przez wszystkie wielkoœci podzbiorów
		// setSize = 1 zosta³ ju¿ wype³niony

		TS_ProblemSolver::DynamicProgramming_GenerateCombinations(matrix, setSize, calculatedValues, std::vector<int>(), 0);
	}

	// powinno wygenerowaæ tylko jedn¹ kombinacjê
	int minimumPathCost = TS_ProblemSolver::DynamicProgramming_GenerateCombinations(matrix, matrix->GetSize(), calculatedValues, std::vector<int>(), 0);

	return nullptr;
}

// 1. uwzglêdniæ startingPoint w obliczaniu drogi