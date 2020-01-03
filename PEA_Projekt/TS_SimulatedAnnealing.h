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
		double t0,
		double tmin,
		double T_change_param1,
		double T_change_param2,
		int maxNumOfIterations, 
		tempDropFunctions tempDropType, 
		changeTypes changeType , 
		int verbose = 0);

private:
	static void swapElementsInPath(Path* path);
};

