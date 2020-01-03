#include "TS_Genetic.h"

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
