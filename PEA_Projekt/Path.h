#pragma once
#include "Edge.h"
#include <vector>
#include "AdjacencyMatrix.h"

class Path
{
private:
	std::vector<Edge> path;
	int pathSize = 0;

public:
	int CalculateCost();
	static int CalculateCost(std::vector<Edge> path);

	void InsertEdge(Edge edge);

	void GenerateRandom(AdjacencyMatrix* matrix, int size);
	void Display(std::ostream& stream);
};

