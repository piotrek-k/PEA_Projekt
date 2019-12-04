#include "TS_TabuSearch.h"

using namespace std;

Path* TS_TabuSearch::TS_UseTabuSearch(AdjacencyMatrix* matrix, int maxIterations, int tabuListSize, bool verbose)
{
	Path* bestPath = new Path(matrix);
	bestPath->GenerateGreedySolution(1);
	Path* currentPath = new Path(matrix);
	currentPath->ReplaceWithOtherInstance(*bestPath);

	vector<tuple<int, int>> tabu_list;

	for (int iterationsCount = 0; iterationsCount < maxIterations; iterationsCount++) {

		//if (verbose) {
		//	cout << "iteration " << iterationsCount << endl;
		//}

		int currentPathCost = currentPath->CalculateCost();

		/*if (verbose) {
			cout << "currentPath: " << endl;
			currentPath->DisplayCompact(cout);
			cout << endl;
		}*/

		/*
		 * Sprawdzenie s¹siedztwa
		 */
		Path* bestNeighbour = new Path(matrix);
		int bestNeighbourCost = -1;
		tuple<int, int> bestNeighbour_tabuListEntry;

		for (int i = 1; i < matrix->GetSize() - 1; i++) { // pominiêcie wêz³a 0
			for (int j = i + 1; j < matrix->GetSize(); j++) { // pominiêcie wêz³ów poprzednich
				// i, j - kandydaci do zamiany

				bool inTabuList = false;
				for (int tl = 0; tl < tabu_list.size(); tl++) {
					int t = get<0>(tabu_list[tl]);
					if ((get<0>(tabu_list[tl]) == i && get<1>(tabu_list[tl]) == j) ||
						(get<0>(tabu_list[tl]) == j && get<1>(tabu_list[tl]) == i)) {
						// propozycja znajduje siê w tabu list, pomiñ
						inTabuList = true;
					}
				}

				if (inTabuList) {
					continue;
				}

				Path* tempPath = new Path(matrix);
				tempPath->ReplaceWithOtherInstance(*currentPath);
				tempPath->SwapNodes(i, j);

				int tempPathCost = tempPath->CalculateCost();

				if (bestNeighbourCost == -1 || tempPathCost < bestNeighbourCost) {
					bestNeighbourCost = tempPathCost;
					bestNeighbour->ReplaceWithOtherInstance(*tempPath);
					bestNeighbour_tabuListEntry = tuple<int, int>(i, j);
				}
			}
		}

		if (verbose) {
			cout << "Najlepszy sasiad: (" <<
				get<0>(bestNeighbour_tabuListEntry) << ", " <<
				get<1>(bestNeighbour_tabuListEntry) << ")" << endl;
			bestNeighbour->DisplayCompact(cout);
			cout << endl;
		}

		currentPath->ReplaceWithOtherInstance(*bestNeighbour);

		/*
		 * SprawdŸ czy najlepszy s¹siad nie jest wartoœcia optymaln¹
		 */
		if (bestNeighbourCost < bestPath->CalculateCost()) {
			bestPath->ReplaceWithOtherInstance(*bestNeighbour);
			if (verbose) {
				cout << "Sasiad ma wartosc optymalna" << endl;
			}
		}

		/*
		 * Aktualizuj tabu_list
		 */
		if (tabu_list.size() > tabuListSize) {
			tabu_list.erase(tabu_list.begin()); // usuñ pierwszy element
		}
		tabu_list.push_back(bestNeighbour_tabuListEntry); // dodaj now¹ wartoœæ na koniec
	}

	return bestPath;
}
