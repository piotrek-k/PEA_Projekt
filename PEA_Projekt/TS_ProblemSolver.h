#pragma once
#include "AdjacencyMatrix.h"
#include "Path.h"
class TS_ProblemSolver
{
public:
	static Path* UseBruteForce(AdjacencyMatrix* matrix, int startingPoint, int endPoint);
	static Path* UseDynamicProgramming(AdjacencyMatrix* matrix, int startingPoint, int endPoint, bool verbose = false);
private:
	static void BruteForce_SearchTree(AdjacencyMatrix* matrix, Path* currentlyCheckedPath, int* bestValue, Path* bestPath, int startPoint, int endPoint);
	static int DynamicProgramming_GenerateCombinations(AdjacencyMatrix* matrix, int k, int** calculatedValues, int startPoint, int endPoint, bool verbose = false, std::vector<int> combination = std::vector<int>(), int offset = 0);
	static int DynamicProgramming_CheckCombination(AdjacencyMatrix* matrix, int** calculatedValues, int startPoint, int endPoint, bool verbose = false, std::vector<int> combination = std::vector<int>());
};

