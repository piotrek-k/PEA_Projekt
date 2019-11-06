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
	void SetCost(int nodeIndex, int value);
	//void SetStepToMinimum(int nodeIndex);
	int GetValue(int nodeIndex);
	//int GetStepToMinimum();
	//int GetValueOfStepToMinimum();
	//void SetValueOfStepToMinimum(int value);
	int GetMinimumStepForDirection(int direction);
	void TrySetMinimumStep(int direction, int possibleNextStep, int possibleMinValue);
};

