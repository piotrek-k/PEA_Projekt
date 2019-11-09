#pragma once
#include <climits>
class DP_CombinationInfo
{
private:
	int* costsByDirection;
	int* stepsToMinimumByEnding;
	int* valuesOfStepToMinimum;
public:
	DP_CombinationInfo(int size);
	~DP_CombinationInfo();
	void SetCombinationCostToDirection(int directionIndex, int cost);
	int GetCostToDirection(int nodeIndex);
	/// <summary>
	/// Zwraca kt�ra warto�� ze zbioru powinna by� "przedostatnia", �eby optymalnie doj�� do w�z�a `direction`.
	/// </summary>
	/// <param name="direction"></param>
	/// <returns></returns>
	int GetMinimumStepForDirection(int direction);
	void TrySetMinimumStep(int direction, int possibleNextStep, int possibleMinValue);
};

