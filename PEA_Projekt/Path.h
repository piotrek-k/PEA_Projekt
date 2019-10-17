#pragma once
#include "Edge.h"
#include <vector>

class Path
{
private:
	std::vector<Edge> path;
	int pathSize = 0;

public:
	int CalculateCost();
	static int CalculateCost(std::vector<Edge> path);

	void InsertEdge(Edge edge);
};

