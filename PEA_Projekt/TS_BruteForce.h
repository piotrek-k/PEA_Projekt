#pragma once
#include "Path.h"
#include "AdjacencyMatrix.h"
class TS_BruteForce
{
public:
	static Path* UseBruteForce(AdjacencyMatrix* matrix, int startingPoint, int endPoint);
private:
	static void SearchTree(AdjacencyMatrix* matrix, Path* currentlyCheckedPath, int* bestValue, Path* bestPath, int startPoint);
};

