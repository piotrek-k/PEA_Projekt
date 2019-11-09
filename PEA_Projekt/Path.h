#pragma once
#include "Edge.h"
#include <vector>
#include "AdjacencyMatrix.h"
#include "PathEdge.h"

class Path
{
private:
	int startingPoint = -1;
	int lastPoint = -1;
	std::vector<PathEdge> path;
	AdjacencyMatrix* baseMatrix;

public:
	Path();
	Path(AdjacencyMatrix* baseMatrix);
	//Path(const Path& otherInstance);
	~Path();

	int CalculateCost();
	static int CalculateCost(std::vector<PathEdge> path, AdjacencyMatrix* baseMatrix);

	bool ContainsValue(int from, int to);
	bool ValueCanBeConnectedToEnd(int value);

	void SetStartingPoint(int pointIndex);

	void InsertEdge(PathEdge edge);
	void RemoveLastEdge();
	void InsertNodeAtTheEnd(AdjacencyMatrix*matrix, int value);
	void Reverse();

	int GetNumberOfNodes();

	void ReplaceWithOtherInstance(const Path& otherInstance);

	void GenerateRandom(AdjacencyMatrix* matrix, int size);
	void Display(std::ostream& stream);
};

