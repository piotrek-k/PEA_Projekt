#include "Path.h"
#include<vector>

int Path::CalculateCost()
{
	int totalCost = 0;
	for (int i = 0; i < this->path.size; i++) {
		totalCost += this->path[i].weight;
	}
	return totalCost;
}

int Path::CalculateCost(std::vector<Edge> path)
{
	int totalCost = 0;
	for (int i = 0; i < path.size; i++) {
		totalCost += path[i].weight;
	}
	return totalCost;
}

void Path::InsertEdge(Edge edge)
{
	this->path.push_back(edge);
}
