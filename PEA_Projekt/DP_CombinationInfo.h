#pragma once
#include <climits>

/// <summary>
/// Klasa powi¹za z algorytmem Helda-Karpa. Przechowuje informacje na temat jednej z kombinacji wêz³ów
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
	/// Zapisuje minimalny koszt trasy poprzez wêz³y w kombinacji, jeœli ostatnim punktem jest `directionIndex`.
	/// </summary>
	void SetCombinationCostToDirection(int directionIndex, int cost);
	/// <summary>
	/// Zwraca koszt dojœcia do podanego punktu docelowego, jeœli ostatnim punktem bêdzie nodeIndex
	/// </summary>
	int GetCostToDirection(int nodeIndex);
	/// <summary>
	/// Zwraca która wartoœæ ze zbioru powinna byæ "przedostatnia", ¿eby optymalnie dojœæ do wêz³a `direction`.
	/// </summary>
	int GetMinimumStepForDirection(int direction);
	/// <summary>
	/// Ustaw "minimum step" tylko jeœli koszt jest mniejszy ni¿ obecny "minimum step"
	/// </summary>
	void TrySetMinimumStep(int direction, int possibleNextStep, int possibleMinValue);
};

