#include "TS_Genetic.h"
#include <algorithm> 
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

TS_Genetic::TS_Genetic(AdjacencyMatrix* baseMatrix, int targetPopulationSize)
{
	this->baseMatrix = baseMatrix;
	this->targetPopulationSize = targetPopulationSize;
}

void TS_Genetic::generateRandomPopulation()
{
	population = vector<Path>();

	for (int a = 0; a < targetPopulationSize; a++) {
		Path newPath = Path(this->baseMatrix);
		newPath.GenerateRandom();
		population.push_back(newPath);
	}
}

bool TS_Genetic::comparePaths(Path p1, Path p2)
{
	return (p1.CalculateCost() < p2.CalculateCost());
}

void TS_Genetic::makeSelection_rank()
{
	// sortuj wed³ug funkcji dopasowania
	std::sort(population.begin(), population.end(), &TS_Genetic::comparePaths);

	// usuñ ostatnie elementy
	population.erase(population.begin() + this->targetPopulationSize, population.end());
}

std::tuple<Path, Path> TS_Genetic::crossPaths_OX(Path* p1, Path* p2)
{
	srand(time(NULL));

	// tworzenie nowych instancji
	Path* newPath1 = new Path(p1->GetBaseMatrix());
	newPath1->ReplaceWithOtherInstance(*p1);
	Path* newPath2 = new Path(p1->GetBaseMatrix());
	newPath2->ReplaceWithOtherInstance(*p2);

	// losowanie sekcji dopasowania
	int k1 = rand() % newPath1->GetPathLength() + 1;
	int k2 = rand() % (newPath1->GetPathLength() - k1 - 1) + k1;

	vector<int> leftFromP = vector<int>(); // zawartoœæ œcie¿ki P bez sekcji dopasowania Q zaczynaj¹c od pozycji k2
	vector<int> leftFromQ = vector<int>(); // zawartoœæ œcie¿ki Q bez sekcji dopasowania P zaczynaj¹c od pozycji k2

	if (newPath1->GetPathLength() != newPath2->GetPathLength())
		throw "Sciezki musza byc rownej dlugosci";

	// Tworzenie tablic leftFromP i leftFromQ
	int x = k2;
	while (true) {
		int candidateP = newPath1->GetStartingNodeAt(x);
		bool validCandidateP = true;
		for (int y = k1; y < k2; y++) {
			if (candidateP == newPath2->GetStartingNodeAt(y)) {
				validCandidateP = false;
				break;
			}
		}
		if (validCandidateP) leftFromP.push_back(candidateP);


		int candidateQ = newPath2->GetStartingNodeAt(x);
		bool validCandidateQ = true;
		for (int y = k1; y < k2; y++) {
			if (candidateQ == newPath1->GetStartingNodeAt(y)) {
				validCandidateQ = false;
				break;
			}
		}
		if (validCandidateQ) leftFromQ.push_back(candidateQ);

		x++;
		if (x >= newPath1->GetPathLength()) {
			x = 0;
		}
		if (x == k2) {
			break;
		}
	}

	// Podmiana elementów niebêd¹cych w sekcji dopasowania
	int leftPointsPos = 0;
	int z = k2;
	while (true) {
		if (z < k1 || z >= k2) {
			newPath1->ReplaceNode(z, leftFromQ[leftPointsPos]);
			newPath2->ReplaceNode(z, leftFromP[leftPointsPos]);
			leftPointsPos++;
		}

		z++;
		if (z >= newPath1->GetPathLength()) {
			z = 0;
		}
		if (z == k2) {
			break;
		}
	}

	if (!newPath1->Validate() || !newPath2->Validate())
		throw "Jedna ze sciezek jest nieprawidlowa";

	return std::make_tuple(*newPath1, *newPath2);
}


