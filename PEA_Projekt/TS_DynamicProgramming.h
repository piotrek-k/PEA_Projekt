#pragma once
#include "AdjacencyMatrix.h"
#include "Path.h"
#include "DP_CombinationInfo.h"
#include "AlgorithmResultContainer.h"
class TS_DynamicProgramming
{
public:
	static AlgorithmResultContainer* UseDynamicProgramming(AdjacencyMatrix* matrix, int startingPoint);
	static AlgorithmResultContainer* UseDynamicProgramming(AdjacencyMatrix* matrix, int startingPoint, bool verbose = false);
private:
	static void DynamicProgramming_GenerateCombinations(AdjacencyMatrix* matrix, int k, DP_CombinationInfo** calculatedValues, int startPoint, int endPoint, bool verbose = false, std::vector<int> combination = std::vector<int>(), int offset = 0);
	static void DynamicProgramming_CheckCombination(AdjacencyMatrix* matrix, DP_CombinationInfo** calculatedValues, int startPoint, int endPoint, bool verbose = false, std::vector<int> combination = std::vector<int>());
	static int DynamicProgramming_D(AdjacencyMatrix* matrix, DP_CombinationInfo** calculatedValues, int startPoint, int endPoint, int destPointIndexInMatrix, bool verbose = false, std::vector<int> combination = std::vector<int>());
};

