#include "TS_BruteForce.h"

Path* TS_BruteForce::UseBruteForce(AdjacencyMatrix* matrix, int startingPoint, int endPoint)
{
	Path* tempPath = new Path(matrix);
	tempPath->SetStartingPoint(startingPoint);

	int bestValue = -1;

	Path* bestPath = new Path(matrix);

	SearchTree(matrix, tempPath, &bestValue, bestPath, startingPoint);

	return bestPath;
}

void TS_BruteForce::SearchTree(AdjacencyMatrix* matrix,
	Path* currentlyCheckedPath,
	int* bestValue,
	Path* bestPath,
	int startPoint)
{
	if (currentlyCheckedPath->GetNumberOfNodes() == matrix->GetSize()) {
		currentlyCheckedPath->InsertNodeAtTheEnd(startPoint);
		int result = currentlyCheckedPath->CalculateCost();

		if (*bestValue == -1 || result < *bestValue) {
			*bestValue = result;
			bestPath->ReplaceWithOtherInstance(*currentlyCheckedPath);
		}
		currentlyCheckedPath->RemoveLastEdge();
		return;
	}

	for (int a = 0; a < matrix->GetSize(); a++) {
		if (a == startPoint) {
			continue;
		}
		if (currentlyCheckedPath->ValueCanBeConnectedToEnd(a)) {
			currentlyCheckedPath->InsertNodeAtTheEnd(a);
			SearchTree(matrix, currentlyCheckedPath, bestValue, bestPath, startPoint);
			currentlyCheckedPath->RemoveLastEdge();
		}
	}
}