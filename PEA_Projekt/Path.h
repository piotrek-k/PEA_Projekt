#pragma once
#include "MatrixEdge.h"
#include <vector>
#include "AdjacencyMatrix.h"
#include "PathEdge.h"

class Path
{
private:
	// potrzebne dla œcie¿ki jednoelementowej
	int startingPoint = -1;

	std::vector<PathEdge> path;
	AdjacencyMatrix* baseMatrix;

public:
	Path(AdjacencyMatrix* baseMatrix);
	~Path();

	int CalculateCost();
	static int CalculateCost(std::vector<PathEdge> path, AdjacencyMatrix* baseMatrix);

	/// <summary>
	/// Sprawdza czy w œcie¿ce istnieje podana krawêdŸ
	/// </summary>
	bool ContainsValue(int from, int to);
	/// <summary>
	/// Sprawdza czy wêze³ `value` zosta³ ju¿ u¿yty jako wêze³ docelowy
	/// </summary>
	bool ValueCanBeConnectedToEnd(int value);

	bool ValueCanBeAddedAndWontMakeACycle(int value);

	void SetStartingPoint(int pointIndex);
	int GetStartingPoint();

	void InsertEdge(PathEdge edge);
	int RemoveLastEdge();
	/// <summary>
	/// Dopisuje wêze³ na koniec œcie¿ki
	/// </summary>
	/// <param name="value"></param>
	void InsertNodeAtTheEnd(int value);
	/// <summary>
	/// Odwraca kolejnoœæ wêz³ów w œcie¿ce
	/// </summary>
	void Reverse();

	int GetNumberOfNodes();

	int GetLastNode();

	void ReplaceWithOtherInstance(const Path& otherInstance);

	void SwapNodes(int i1, int i2);
	void ReplaceNode(int position, int value);

	void GenerateRandom();
	void GenerateRandom(int size);
	void GenerateGreedySolution(int greedyStartPoint);
	void Display(std::ostream& stream);
	void DisplayCompact(std::ostream& stream);

	int GetStartingNodeAt(int x);
	int GetPathLength();
	AdjacencyMatrix* GetBaseMatrix();

	/// <summary>
	/// 1. SprawdŸ poprawnoœæ startingPoint
	/// 2. SprawdŸ czy wêz³y nie powtarzaj¹ siê 
	/// 3. SprawdŸ czy wartoœci from odpowiadaj¹ wartoœciom to
	/// 4. SprawdŸ czy ostatni element to startingPoint
	/// </summary>
	/// <returns></returns>
	bool Validate();
};

