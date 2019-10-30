#include "TS_ProblemSolver.h"

Path* TS_ProblemSolver::UseBruteForce(AdjacencyMatrix* matrix, int startingPoint, int endPoint)
{
	Path* tempPath = new Path();
	tempPath->SetStartingPoint(startingPoint);

	int bestValue = -1;

	Path* bestPath = new Path();

	BruteForce_SearchTree(matrix, tempPath, &bestValue, bestPath, startingPoint, endPoint);

	return bestPath;
}

void TS_ProblemSolver::BruteForce_SearchTree(AdjacencyMatrix* matrix, Path* currentlyCheckedPath, int* bestValue, Path* bestPath, int startPoint, int endPoint)
{
	if (currentlyCheckedPath->GetNumberOfNodes() == matrix->GetSize() - 1) {
		currentlyCheckedPath->InsertNodeAtTheEnd(matrix, endPoint);
		int result = currentlyCheckedPath->CalculateCost();
		
		if (*bestValue == -1 || result < *bestValue) {
			*bestValue = result;
			bestPath->ReplaceWithOtherInstance(*currentlyCheckedPath);
		}
		currentlyCheckedPath->RemoveLastEdge();
		return;
	}

	for (int a = 0; a < matrix->GetSize(); a++) {
		if (a == startPoint || a == endPoint) {
			continue;
		}
		if (currentlyCheckedPath->ValueCanBeConnectedToEnd(a)) {
			currentlyCheckedPath->InsertNodeAtTheEnd(matrix, a);
			BruteForce_SearchTree(matrix, currentlyCheckedPath, bestValue, bestPath, startPoint, endPoint);
			currentlyCheckedPath->RemoveLastEdge();
		}
	}
}
