#pragma once
#include "AdjacencyMatrix.h"
#include "Path.h"
class TS_ProblemSolver
{
public:
	static Path* UseBruteForce(AdjacencyMatrix* matrix, int startingPoint, int endPoint);
private:
	static void BruteForce_SearchTree(AdjacencyMatrix* matrix, Path* currentlyCheckedPath, int* bestValue, Path* bestPath, int startPoint, int endPoint);
};

