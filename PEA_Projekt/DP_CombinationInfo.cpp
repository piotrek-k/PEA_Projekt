#include "DP_CombinationInfo.h"

DP_CombinationInfo::DP_CombinationInfo(int size)
{
	costsByDirection = new int[size];
	for (int a = 0; a < size; a++) {
		costsByDirection[a] = 0;
	}
	stepToMinimum = -1;
}

void DP_CombinationInfo::SetCost(int nodeIndex, int value)
{
	costsByDirection[nodeIndex] = value;
}

void DP_CombinationInfo::SetStepToMinimum(int nodeIndex)
{
	stepToMinimum = nodeIndex;
}

int DP_CombinationInfo::GetValue(int nodeIndex)
{
	return costsByDirection[nodeIndex];
}

int DP_CombinationInfo::GetStepToMinimum()
{
	return stepToMinimum;
}
