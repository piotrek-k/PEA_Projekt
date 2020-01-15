#include "TS_Genetic.h"
#include <algorithm> 
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

TS_Genetic::TS_Genetic(AdjacencyMatrix* baseMatrix, int targetPopulationSize)
{
	srand(time(NULL));
	this->baseMatrix = baseMatrix;
	this->targetPopulationSize = targetPopulationSize;
}

Path TS_Genetic::TS_UseGenetic(AdjacencyMatrix* matrix, int maxIterations, int populationSize, SelectionType selectionType, CrossingStrategy crossingStrategy, float mutationProbability, int verbose)
{
	TS_Genetic instance = TS_Genetic(matrix, populationSize);
	instance.generateRandomPopulation();

	for (int i = 0; i < maxIterations; i++) {
		// wygeneruj losowe mutacje
		instance.randomlySwapMutatePopulation(0.01);
		// utwórz nowe osobniki
		instance.newGeneration_crossBestRandomly(populationSize, 10, crossingStrategy);
		// wybierz osobniki do nastêpej iteracji
		switch (selectionType) {
		case SelectionType::rank:
			instance.makeSelection_rank();
			break;
		default:
			if (verbose) {
				std::cout << "Nie wybrano metody selekcji" << std::endl;
			}
		}
		// wyœwietl postêp
		instance.sortPopulationByPathCost();
		if (verbose) {
			std::cout << "Pokolenie "
				<< i << ". Wynik: ";
		}
		/*instance.population[0].CalculateCost() << "..." <<
		instance.population[1].CalculateCost() << "..." <<
		instance.population[2].CalculateCost() << std::endl;*/
		if (verbose) {
			for (int q = 0; q < populationSize; q++) {
				std::cout << instance.population[q].CalculateCost() << "...";
			}
			std::cout << std::endl;
		}
		
	}

	return instance.population[0];
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
	sortPopulationByPathCost();

	// usuñ ostatnie elementy
	population.erase(population.begin() + this->targetPopulationSize, population.end());
}

void TS_Genetic::newGeneration_crossBestRandomly(int populationToCross, int numberOfCrosses, CrossingStrategy crossingStrategy)
{
	sortPopulationByPathCost();

	if (populationToCross > population.size()) {
		throw "populationToCross too large";
	}
	if (populationToCross == 0) {
		throw "populationToCross cannot be 0";
	}

	for (int x = 0; x < numberOfCrosses; x++) {
		int cross1 = rand() % populationToCross;
		int cross2 = rand() % populationToCross;
		while (cross2 == cross1) {
			cross2 = rand() % populationToCross;
		}

		switch (crossingStrategy) {
		case (CrossingStrategy::OX):
		{
			std::tuple<Path, Path> result = crossPaths_OX(&population[cross1], &population[cross2]);
			population.push_back(get<0>(result));
			population.push_back(get<1>(result));
			break;
		}
		default:
			std::cout << "Brak CrossingStartegy" << std::endl;
		}
	}
}

void TS_Genetic::randomlySwapMutatePopulation(float probability)
{
	for (int indiv = 0; indiv < population.size(); indiv++) {
		for (int genePos = 0; genePos < population[indiv].GetPathLength() - 1; genePos++) {
			double x = ((double)rand() / (RAND_MAX));
			if (probability >= x) {
				Path p = Path(population[0].GetBaseMatrix());
				p.ReplaceWithOtherInstance(population[indiv]);
				population[indiv].SwapNodes(genePos, genePos + 1);
				//std::cout << "Random swap" << std::endl;
				if (population[indiv].Validate() == false) {
					std::cout << "PROBLEM";
				}
			}
		}
	}
}

void TS_Genetic::sortPopulationByPathCost()
{
	// sortuj wed³ug funkcji dopasowania
	std::sort(population.begin(), population.end(), &TS_Genetic::comparePaths);
}

std::tuple<Path, Path> TS_Genetic::crossPaths_OX(Path* p1, Path* p2)
{
	//srand(time(NULL));

	// tworzenie nowych instancji
	Path* newPath1 = new Path(p1->GetBaseMatrix());
	newPath1->ReplaceWithOtherInstance(*p1);
	Path* newPath2 = new Path(p1->GetBaseMatrix());
	newPath2->ReplaceWithOtherInstance(*p2);

	// losowanie sekcji dopasowania
	int k1 = rand() % (newPath1->GetPathLength() - 1);
	int k2 = rand() % (newPath1->GetPathLength() - k1 - 1) + k1;

	vector<int> leftFromP = vector<int>(); // zawartoœæ œcie¿ki P bez sekcji dopasowania Q zaczynaj¹c od pozycji k2
	vector<int> leftFromQ = vector<int>(); // zawartoœæ œcie¿ki Q bez sekcji dopasowania P zaczynaj¹c od pozycji k2

	if (newPath1->GetPathLength() != newPath2->GetPathLength())
		throw "Sciezki musza byc rownej dlugosci";

	// Tworzenie tablic leftFromP i leftFromQ
	int x = k2;
	while (true) {
		bool validCandidateP = true;
		{
			int candidateP = newPath1->GetStartingNodeAt(x);
			for (int y = k1; y < k2; y++) {
				if (candidateP == newPath2->GetStartingNodeAt(y)) {
					validCandidateP = false;
					break;
				}
			}
			if (validCandidateP) leftFromP.push_back(candidateP);
		}


		bool validCandidateQ = true;
		{
			int candidateQ = newPath2->GetStartingNodeAt(x);
			for (int y = k1; y < k2; y++) {
				if (candidateQ == newPath1->GetStartingNodeAt(y)) {
					validCandidateQ = false;
					break;
				}
			}
			if (validCandidateQ) leftFromQ.push_back(candidateQ);
		}

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
		throw std::exception("Jedna ze sciezek jest nieprawidlowa");

	return std::make_tuple(*newPath1, *newPath2);
}


