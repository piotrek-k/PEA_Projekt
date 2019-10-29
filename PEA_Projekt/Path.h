#pragma once
#include "Edge.h"
#include <vector>
#include "AdjacencyMatrix.h"

class Path
{
private:
	int startingPoint = -1;
	int lastPoint = -1;
	std::vector<Edge> path;

public:
	int CalculateCost();
	static int CalculateCost(std::vector<Edge> path);

	bool ContainsValue(int from, int to);
	bool ValueCanBeConnectedToEnd(int value);

	void InsertStartingPoint(int pointIndex);

	void InsertEdge(Edge edge);
	void RemoveLastEdge();
	void InsertNodeAtTheEnd(AdjacencyMatrix*matrix, int value);

	int GetNumberOfNodes();

	void GenerateRandom(AdjacencyMatrix* matrix, int size);
	void Display(std::ostream& stream);
};

