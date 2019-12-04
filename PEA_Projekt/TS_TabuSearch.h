#pragma once
#include "Path.h"
class TS_TabuSearch
{
public:
	static Path* TS_UseTabuSearch(AdjacencyMatrix* matrix, int maxIterations, int tabuListSize, bool verbose);
};

