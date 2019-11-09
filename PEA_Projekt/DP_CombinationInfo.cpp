#include "DP_CombinationInfo.h"

DP_CombinationInfo::DP_CombinationInfo(int size)
{
	costsByDirection = new int[size];
	stepsToMinimumByEnding = new int[size];
	valuesOfStepToMinimum = new int[size];
	for (int a = 0; a < size; a++) {
		costsByDirection[a] = 0;
		stepsToMinimumByEnding[a] = -1;
		valuesOfStepToMinimum[a] = INT_MAX;
	}
}

DP_CombinationInfo::~DP_CombinationInfo()
{
	delete[] costsByDirection;
}

void DP_CombinationInfo::SetCombinationCostToDirection(int directionIndex, int cost)
{
	costsByDirection[directionIndex] = cost;
}

int DP_CombinationInfo::GetCostToDirection(int nodeIndex)
{
	return costsByDirection[nodeIndex];
}

int DP_CombinationInfo::GetMinimumStepForDirection(int direction)
{
	return stepsToMinimumByEnding[direction];
}

void DP_CombinationInfo::TrySetMinimumStep(int direction, int possibleNextStep, int possibleMinValue)
{
	if (possibleMinValue < valuesOfStepToMinimum[direction]) {
		valuesOfStepToMinimum[direction] = possibleMinValue;
		stepsToMinimumByEnding[direction] = possibleNextStep;
	}
}
