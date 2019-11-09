#pragma once
#include "AdjacencyMatrix.h"
#include "Path.h"
class TS_BranchAndBound
{
public:
	static Path* UseBranchAndBound(AdjacencyMatrix* matrix, int startingPoint);

private:
	static void SearchTree(AdjacencyMatrix* matrix, Path* currentlyCheckedPath, Path* bestPath, int startAndEndPoint, int* globalUpperBound);
	static int LowerBound(AdjacencyMatrix* matrix, Path* currentlyCheckedPath);
};

