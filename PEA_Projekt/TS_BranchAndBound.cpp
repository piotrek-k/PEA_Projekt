#include "TS_BranchAndBound.h"
#include <queue>

using namespace std;

Path* TS_BranchAndBound::UseBranchAndBound(AdjacencyMatrix* matrix, int startingPoint)
{
	Path* tempPath = new Path(matrix);
	tempPath->SetStartingPoint(startingPoint);
	Path* bestPath = new Path(matrix);
	int globalBestCost = INT_MAX;

	SearchTree(matrix, tempPath, bestPath, startingPoint, &globalBestCost);

	//bestPath->Reverse();

	return bestPath;
}

int TS_BranchAndBound::LowerBound(AdjacencyMatrix* matrix, Path* currentlyCheckedPath)
{
	vector<int> possibleTargetNodes = vector<int>();
	for (int a = 0; a < matrix->GetSize(); a++) {
		if (currentlyCheckedPath->ValueCanBeConnectedToEnd(a)) { //a != currentlyCheckedPath->GetStartingPoint() && 
			possibleTargetNodes.push_back(a);
		}
	}
	int sumOfLowerBound = currentlyCheckedPath->CalculateCost();
	int possibleTargetsNumber = possibleTargetNodes.size();
	for (int a = -1; a < possibleTargetsNumber; a++) {

		int sourceIndex = 0;
		if (a == -1) {
			// uwzglêdnienie wêz³a koñcowego œcie¿ki
			sourceIndex = currentlyCheckedPath->GetLastNode();
		}
		else {
			sourceIndex = possibleTargetNodes[a];
		}

		if (sourceIndex != currentlyCheckedPath->GetStartingPoint()) {
			int min = INT_MAX;
			for (int b = 0; b < possibleTargetNodes.size(); b++) {

				int destinationIndex = possibleTargetNodes[b];

				if (sourceIndex == destinationIndex) {
					continue;
				}
				int candidate = matrix->GetWeightOfEdge(sourceIndex, destinationIndex);
				if (candidate < min) {
					min = candidate;
				}
			}

			sumOfLowerBound += min;
		}
	}

	return sumOfLowerBound;
}

void TS_BranchAndBound::SearchTree(AdjacencyMatrix* matrix, Path* currentlyCheckedPath, Path* bestPath, int startAndEndPoint, int* globalUpperBound)
{
	if (currentlyCheckedPath->GetNumberOfNodes() == matrix->GetSize()) {
		currentlyCheckedPath->InsertNodeAtTheEnd(startAndEndPoint);
		int result = currentlyCheckedPath->CalculateCost();

		if (result < *globalUpperBound) {
			*globalUpperBound = result;
			bestPath->ReplaceWithOtherInstance(*currentlyCheckedPath);
		}
		currentlyCheckedPath->RemoveLastEdge();
		return;
	}

	int lowerBound = LowerBound(matrix, currentlyCheckedPath);
	if (lowerBound < *globalUpperBound) { // jest mo¿liwe, ¿e ta œcie¿ka bêdzie lepsza
		for (int a = 0; a < matrix->GetSize(); a++) {
			if (a == startAndEndPoint || !currentlyCheckedPath->ValueCanBeConnectedToEnd(a)) {
				continue;
			}
			currentlyCheckedPath->InsertNodeAtTheEnd(a);
			SearchTree(matrix, currentlyCheckedPath, bestPath, startAndEndPoint, globalUpperBound);
			currentlyCheckedPath->RemoveLastEdge();
		}
	}
}
