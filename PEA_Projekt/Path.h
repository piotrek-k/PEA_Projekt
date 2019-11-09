#pragma once
#include "MatrixEdge.h"
#include <vector>
#include "AdjacencyMatrix.h"
#include "PathEdge.h"

class Path
{
private:
	// potrzebne dla �cie�ki jednoelementowej
	int startingPoint = -1;

	std::vector<PathEdge> path;
	AdjacencyMatrix* baseMatrix;

public:
	Path(AdjacencyMatrix* baseMatrix);
	~Path();

	int CalculateCost();
	static int CalculateCost(std::vector<PathEdge> path, AdjacencyMatrix* baseMatrix);

	/// <summary>
	/// Sprawdza czy w �cie�ce istnieje podana kraw�d�
	/// </summary>
	bool ContainsValue(int from, int to);
	/// <summary>
	/// Sprawdza czy w�ze� `value` zosta� ju� u�yty jako w�ze� docelowy
	/// </summary>
	bool ValueCanBeConnectedToEnd(int value);

	void SetStartingPoint(int pointIndex);
	int GetStartingPoint();

	void InsertEdge(PathEdge edge);
	int RemoveLastEdge();
	/// <summary>
	/// Dopisuje w�ze� na koniec �cie�ki
	/// </summary>
	/// <param name="value"></param>
	void InsertNodeAtTheEnd(int value);
	/// <summary>
	/// Odwraca kolejno�� w�z��w w �cie�ce
	/// </summary>
	void Reverse();

	int GetNumberOfNodes();

	int GetLastNode();

	void ReplaceWithOtherInstance(const Path& otherInstance);

	void GenerateRandom(int size);
	void Display(std::ostream& stream);
};

