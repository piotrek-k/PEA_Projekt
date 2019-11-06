#pragma once
class DP_CombinationInfo
{
private:
	int* costsByDirection;
	int stepToMinimum = -1;
public:
	DP_CombinationInfo(int size);
	~DP_CombinationInfo();
	void SetCost(int nodeIndex, int value);
	void SetStepToMinimum(int nodeIndex);
	int GetValue(int nodeIndex);
	int GetStepToMinimum();
};

