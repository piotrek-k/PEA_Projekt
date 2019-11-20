#pragma once
#include "AdjacencyMatrix.h"
#include "Path.h"
#include "AlgorithmResultContainer.h"
class TS_BranchAndBound
{
public:
	static AlgorithmResultContainer* UseBranchAndBound(AdjacencyMatrix* matrix, int startingPoint);

private:
	static void SearchTree(AdjacencyMatrix* matrix, Path* currentlyCheckedPath, Path* bestPath, int startAndEndPoint, int* globalUpperBound);
	static int LowerBound(AdjacencyMatrix* matrix, Path* currentlyCheckedPath);
};

