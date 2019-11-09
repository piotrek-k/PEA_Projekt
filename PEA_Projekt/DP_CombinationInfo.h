#pragma once
#include <climits>

/// <summary>
/// Klasa powi�za z algorytmem Helda-Karpa. Przechowuje informacje na temat jednej z kombinacji w�z��w
/// </summary>
class DP_CombinationInfo
{
private:
	int* costsByDirection;
	int* stepsToMinimumByEnding;
	int* valuesOfStepToMinimum;
public:
	DP_CombinationInfo(int size);
	~DP_CombinationInfo();
	/// <summary>
	/// Zapisuje minimalny koszt trasy poprzez w�z�y w kombinacji, je�li ostatnim punktem jest `directionIndex`.
	/// </summary>
	void SetCombinationCostToDirection(int directionIndex, int cost);
	/// <summary>
	/// Zwraca koszt doj�cia do podanego punktu docelowego, je�li ostatnim punktem b�dzie nodeIndex
	/// </summary>
	int GetCostToDirection(int nodeIndex);
	/// <summary>
	/// Zwraca kt�ra warto�� ze zbioru powinna by� "przedostatnia", �eby optymalnie doj�� do w�z�a `direction`.
	/// </summary>
	int GetMinimumStepForDirection(int direction);
	/// <summary>
	/// Ustaw "minimum step" tylko je�li koszt jest mniejszy ni� obecny "minimum step"
	/// </summary>
	void TrySetMinimumStep(int direction, int possibleNextStep, int possibleMinValue);
};

