#pragma once
#include "AdjacencyMatrix.h"
#include "AlgorithmResultContainer.h"
class TS_SimulatedAnnealing
{
public:
	enum class tempDropFunctions {linear, geometric, logarythmic};
	enum class changeTypes {swap};
	static AlgorithmResultContainer* UseSimulatedAnnealing(
		AdjacencyMatrix* matrix, 
		float t0,
		float tmin, 
		float T_change_param1,
		float T_change_param2,
		int maxNumOfIterations, 
		tempDropFunctions tempDropType, 
		changeTypes changeType , 
		bool verbose = false);

private:
	static void swapElementsInPath(Path* path);
};

