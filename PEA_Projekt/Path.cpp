#include "Path.h"
#include<vector>
#include "AdjacencyMatrix.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

int Path::CalculateCost()
{
	int totalCost = 0;
	for (int i = 0; i < this->path.size(); i++) {
		totalCost += this->path[i].weight;
	}
	return totalCost;
}

int Path::CalculateCost(std::vector<Edge> path)
{
	int totalCost = 0;
	for (int i = 0; i < path.size(); i++) {
		totalCost += path[i].weight;
	}
	return totalCost;
}

void Path::InsertEdge(Edge edge)
{
	this->path.push_back(edge);
}

void Path::GenerateRandom(AdjacencyMatrix* am, int size)
{
	path.clear();
	srand(time(NULL));

	std::vector<int> tempVec;
	for (int a = 0; a < size; a++) {
		tempVec.push_back(a);
	}

	int prevNodeIndex = -1;
	int firstIndex = -1;
	int currentNodeIndex;
	for (int x = 0; x < size; x++) {
		int vecSize = tempVec.size();
		int positionInTempVector;
		do {
			positionInTempVector = rand() % vecSize;
			currentNodeIndex = tempVec[positionInTempVector];
		} while (currentNodeIndex == prevNodeIndex || (currentNodeIndex == firstIndex));

		if (firstIndex == -1) {
			firstIndex = currentNodeIndex;
		}

		if (prevNodeIndex != -1) {
			path.push_back(
				Edge(prevNodeIndex,
					currentNodeIndex,
					am->GetWeightOfEdge(prevNodeIndex, currentNodeIndex))
			);
			tempVec.erase(tempVec.begin() + positionInTempVector);
		}

		prevNodeIndex = currentNodeIndex;
	}

	path.push_back(
		Edge(currentNodeIndex,
			firstIndex,
			am->GetWeightOfEdge(currentNodeIndex, firstIndex))
	);
}

void Path::Display(std::ostream& stream)
{
	stream << "Wygenerowana sciezka: " << std::endl;
	for (int a = 0; a < path.size(); a++) {
		stream << path[a].from << "->" << path[a].to << "(" << path[a].weight << ") ";
	}
	stream << "Koszt: " << CalculateCost() << std::endl;
}
