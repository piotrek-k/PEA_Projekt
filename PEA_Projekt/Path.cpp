#include "Path.h"
#include<vector>
#include "AdjacencyMatrix.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */


Path::Path(AdjacencyMatrix* baseMatrix)
{
	this->baseMatrix = baseMatrix;
}

Path::~Path()
{
}

int Path::CalculateCost()
{
	return this->CalculateCost(this->path, this->baseMatrix);
}

int Path::CalculateCost(std::vector<PathEdge> path, AdjacencyMatrix* baseMatrix)
{
	int totalCost = 0;
	for (int i = 0; i < path.size(); i++) {
		totalCost += baseMatrix->GetWeightOfEdge(path[i].from, path[i].to);
	}
	return totalCost;
}

bool Path::ContainsValue(int from, int to)
{
	for (int a = 0; a < path.size(); a++) {
		if (path[a].from == from && path[a].to == to) {
			return true;
		}
	}
	return false;
}

bool Path::ValueCanBeConnectedToEnd(int value)
{
	for (int a = 0; a < path.size(); a++) {
		if (path[a].to == value) {
			return false;
		}
	}
	return true;
}

void Path::SetStartingPoint(int pointIndex)
{
	if (path.size() > 0) {
		throw "Cannot insert starting point to existing path";
	}
	startingPoint = pointIndex;
}

int Path::GetStartingPoint()
{
	return startingPoint;
}

void Path::InsertEdge(PathEdge edge)
{
	if (path.size() == 0 && this->startingPoint == -1) {
		this->startingPoint = edge.from;
	}
	this->path.push_back(edge);
}

int Path::RemoveLastEdge()
{
	if (path.size() == 0) {
		return GetLastNode();
	}

	int lastNode = GetLastNode();

	path.pop_back();

	return lastNode;
}

void Path::InsertNodeAtTheEnd(int value)
{
	if (startingPoint == -1) {
		startingPoint = value;
		return;
	}

	PathEdge e = PathEdge(this->GetLastNode(), value);
	InsertEdge(e);
}

void Path::Reverse()
{
	std::vector<PathEdge> reversed;

	for (int a = this->path.size() - 1; a >= 0; a--) {
		reversed.push_back(PathEdge(this->path[a].to, this->path[a].from));
	}

	this->path = reversed;
}

int Path::GetNumberOfNodes()
{
	if (this->path.size() == 0) {
		if (this->startingPoint != -1) {
			return 1;
		}
		else {
			return 0;
		}
	}
	else {
		return this->path.size() + 1;
	}
}

int Path::GetLastNode()
{
	if (this->path.size() > 0) {
		return this->path[this->path.size() - 1].to;
	}
	else {
		return startingPoint;
	}
}

void Path::ReplaceWithOtherInstance(const Path& otherInstance)
{
	this->startingPoint = otherInstance.startingPoint;
	this->path = otherInstance.path;
	this->baseMatrix = otherInstance.baseMatrix;
}

void Path::SwapNodes(int positionInPath1, int positionInPath2)
{
	if (positionInPath1 >= baseMatrix->GetSize() || positionInPath2 >= baseMatrix->GetSize()) {
		throw new std::exception("Incorrect path positions");
	}

	int firstNodeIndex = 0;
	int secondNodeIndex = 0;
	if (positionInPath1 == 0) {
		firstNodeIndex = startingPoint;
	}
	else if (positionInPath1 == baseMatrix->GetSize() - 1) {
		firstNodeIndex = GetLastNode();
	}
	else {
		firstNodeIndex = path[positionInPath1 - 1].to;
	}
	if (positionInPath2 == 0) {
		secondNodeIndex = startingPoint;
	}
	else if (positionInPath2 == baseMatrix->GetSize() - 1) {
		secondNodeIndex = GetLastNode();
	}
	else {
		secondNodeIndex = path[positionInPath2 - 1].to;
	}

	ReplaceNode(positionInPath1, secondNodeIndex);
	ReplaceNode(positionInPath2, firstNodeIndex);
}

void Path::ReplaceNode(int position, int value)
{
	if (position == 0 || position == path.size() - 1) {
		startingPoint = value;
		path[0].from = value;
		path[path.size() - 1].to = value;
	}
	else {
		path[position - 1].to = value;
		path[position].from = value;
	}
}

void Path::GenerateRandom()
{
	GenerateRandom(this->baseMatrix->GetSize());
}

void Path::GenerateRandom(int size)
{
	path.clear();
	srand(time(NULL));

	std::vector<int> tempVec;
	for (int a = 0; a < size; a++) {
		tempVec.push_back(a);
	}

	int prevNodeIndex = -1;
	int firstIndex = -1;
	int currentNodeIndex = -1;
	for (int x = 0; x < size; x++) {
		int vecSize = tempVec.size();
		int positionInTempVector;
		do {
			positionInTempVector = rand() % vecSize;
			currentNodeIndex = tempVec[positionInTempVector];
		} while (currentNodeIndex == prevNodeIndex || (currentNodeIndex == firstIndex));

		if (firstIndex == -1) {
			firstIndex = currentNodeIndex;
			startingPoint = firstIndex;
		}

		if (prevNodeIndex != -1) {
			path.push_back(
				PathEdge(prevNodeIndex,
					currentNodeIndex));
			tempVec.erase(tempVec.begin() + positionInTempVector);
		}

		prevNodeIndex = currentNodeIndex;
	}

	path.push_back(
		PathEdge(currentNodeIndex,
			firstIndex)
	);
}

void Path::GenerateGreedySolution(int greedyStartPoint)
{
	path.clear();
	srand(time(NULL));

	startingPoint = greedyStartPoint;

	std::vector<int> tempVec;
	for (int a = 0; a < this->baseMatrix->GetSize(); a++) {
		if (a == greedyStartPoint) {
			continue;
		}
		tempVec.push_back(a);
	}

	int prevNodeIndex = greedyStartPoint;
	for (int x = 0; x < this->baseMatrix->GetSize()-1; x++) {
		int minimalStepCost = INT_MAX;
		int minimalStepIndex = -1;
		int positionOfStepInTempVec = -1;
		for (int tV = 0; tV < tempVec.size(); tV++) {
			int stepConstCandidate = this->baseMatrix->GetWeightOfEdge(prevNodeIndex, tempVec[tV]);
			if (minimalStepCost > stepConstCandidate) {
				minimalStepCost = stepConstCandidate;
				minimalStepIndex = tempVec[tV];
				positionOfStepInTempVec = tV;
			}
		}

		if (minimalStepIndex != -1 && positionOfStepInTempVec != -1) {
			tempVec.erase(tempVec.begin() + positionOfStepInTempVec);
			path.push_back(PathEdge(prevNodeIndex, minimalStepIndex));

			prevNodeIndex = minimalStepIndex;
		}
		else {
			throw std::exception("Nie znaleziono minimalnego kroku.");
		}
	}

	path.push_back(PathEdge(prevNodeIndex, greedyStartPoint));
}

void Path::Display(std::ostream& stream)
{
	stream << "Wygenerowana sciezka: " << std::endl;
	for (int a = 0; a < path.size(); a++) {
		stream << path[a].from << "->" << path[a].to << "(" << this->baseMatrix->GetWeightOfEdge(path[a].from, path[a].to) << ") ";
	}
	stream << "Koszt: " << CalculateCost() << std::endl;
}

void Path::DisplayCompact(std::ostream& stream)
{
	for (int a = 0; a < path.size(); a++) {
		stream << path[a].from << "->" << path[a].to << "(" << this->baseMatrix->GetWeightOfEdge(path[a].from, path[a].to) << ") ";
	}
	stream << "Koszt: " << CalculateCost();
}
