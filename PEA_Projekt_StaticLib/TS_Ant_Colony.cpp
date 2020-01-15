#include "TS_Ant_Colony.h"

TS_Ant_Colony::TS_Ant_Colony(AdjacencyMatrix* matrix,
	int numberOfAnts,
	float collectiveMemoryPower,
	float greedyChoicePower,
	float evaporationRate,
	float pheromoneStartValue)
{
	this->numberOfAnts = numberOfAnts;
	this->collectiveMemoryPower = collectiveMemoryPower;
	this->greedyChoicePower = greedyChoicePower;
	this->evaporationRate = evaporationRate;
	this->pheromoneStartValue = pheromoneStartValue;

	srand(time(NULL));

	this->graphSize = matrix->GetSize();

	pheromoneValues = new float* [graphSize];
	for (int x = 0; x < graphSize; x++) {
		pheromoneValues[x] = new float[graphSize];
	}
}

void TS_Ant_Colony::SeedAnts(int numberOfAnts)
{
	for (int a = 0; a < numberOfAnts; a++) {
		Path p = Path(this->baseMatrix);
		p.SetStartingPoint(rand() % graphSize);
		ants.push_back(p);
	}
}

void TS_Ant_Colony::EvaporatePheromone(float speed)
{
	for (int x = 0; x < graphSize; x++) {
		for (int y = 0; y < graphSize; y++) {
			pheromoneValues[x][y] *= evaporationRate;
		}
	}
}

void TS_Ant_Colony::MoveAntLeavePheromone(Path* ant)
{
	vector<float> wayStrength(this->graphSize);
	float sumOfWayStrengths = 0;

	for (int v = 0; v < this->graphSize; v++) {
		int lastNode = ant->GetLastNode();

		if (ant->ValueCanBeConnectedToEnd(v)) {
			wayStrength[v] =
				pow(pheromoneValues[lastNode][v], this->collectiveMemoryPower) *
				pow(1/(float)baseMatrix->GetWeightOfEdge(lastNode, v), this->greedyChoicePower);
		}
		else {
			wayStrength[v] = 0;
		}

		sumOfWayStrengths += wayStrength[v];
	}

	if (sumOfWayStrengths == 0) {
		throw std::exception("Brak mozliwych krokow do wykonania");
	}

	double randomValue = ((double)rand() / (RAND_MAX));

	for (int v = 0; v < this->graphSize; v++) {
		if (randomValue <= wayStrength[v] / sumOfWayStrengths) {
			ant->InsertNodeAtTheEnd(v);

			return;
		}
	}

	throw std::exception("Nie wybrano nastepnego kroku");
}
