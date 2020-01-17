#include "TS_Ant_Colony.h"
#include<algorithm>

TS_Ant_Colony::TS_Ant_Colony(AdjacencyMatrix* matrix,
	int numberOfAnts,
	float collectiveMemoryPower,
	float greedyChoicePower,
	float evaporationRate,
	float pheromoneStartValue)
{
	this->baseMatrix = matrix;
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
		for (int y = 0; y < graphSize; y++) {
			pheromoneValues[x][y] = this->pheromoneStartValue;
		}
	}
}

Path TS_Ant_Colony::TS_UseAntColony(AdjacencyMatrix* matrix, int maxNumOfIterations, int numberOfAnts, float collectiveMemoryPower, float greedyChoicePower, float evaporationRate, float pheromoneStartValue, bool verbose)
{
	TS_Ant_Colony environment = TS_Ant_Colony(matrix, numberOfAnts, collectiveMemoryPower, greedyChoicePower, evaporationRate, pheromoneStartValue);
	Path* bestPath = new Path(matrix);
	int costOfBestPath = INT_MAX;

	for (int i = 0; i < maxNumOfIterations; i++) {
		environment.SeedAnts(numberOfAnts);

		for (int step = 0; step < matrix->GetSize(); step++) {
			for (int ant = 0; ant < numberOfAnts; ant++) {
				environment.MoveAntLeavePheromone(&environment.ants[ant]);
			}
		}

		environment.EvaporatePheromone(evaporationRate);

		int prevAntValue = -1;
		bool valuesAreTheSame = true;
		for (int ant = 0; ant < numberOfAnts; ant++) {
			int proposedBest = environment.ants[ant].CalculateCost();

			if (prevAntValue != proposedBest && prevAntValue != -1) {
				valuesAreTheSame = false;
			}
			prevAntValue = proposedBest;

			if (costOfBestPath > proposedBest) {
				if (environment.ants[ant].Validate()) {
					costOfBestPath = proposedBest;
					bestPath = new Path(matrix);
					bestPath->ReplaceWithOtherInstance(environment.ants[ant]);
				}
				else {
					std::cout << "Found best but is invalid" << std::endl;
				}
			}
		}

		// usuñ populacjê
		environment.ants = vector<Path>();

		if (verbose) {
			std::cout << "Iter. " << i << ": " << costOfBestPath << std::endl;
		}

		if (valuesAreTheSame) {
			// wszystkie mrówki znalaz³y tê sam¹ drogê, mo¿na przerwaæ algorytm
			break;
		}
	}

	return *bestPath;
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
	vector<int> possibleCandidatesWithNoPheromone; // w sytuacji gdy wszystkie potencjalne drogi maj¹ feromon = 0
	float sumOfWayStrengths = 0;

	for (int v = 0; v < this->graphSize; v++) {
		int lastNode = ant->GetLastNode();

		if (ant->ValueCanBeAddedAndWontMakeACycle(v) && lastNode != v) {
			wayStrength[v] =
				pow(pheromoneValues[lastNode][v], this->collectiveMemoryPower) *
				pow(1 / (float)baseMatrix->GetWeightOfEdge(lastNode, v), this->greedyChoicePower);
			if (wayStrength[v] == 0) {
				possibleCandidatesWithNoPheromone.push_back(v);
			}
		}
		else {
			wayStrength[v] = 0;
		}

		sumOfWayStrengths += wayStrength[v];
	}

	if (sumOfWayStrengths == 0) {
		if (ant->GetPathLength() == baseMatrix->GetSize() - 1) {
			pheromoneValues[ant->GetLastNode()][ant->GetStartingPoint()] += baseMatrix->GetWeightOfEdge(ant->GetLastNode(), ant->GetStartingPoint());
			ant->InsertNodeAtTheEnd(ant->GetStartingPoint());
			return;
		}
		else {
			//throw std::exception("Brak mozliwych krokow do wykonania");
			wayStrength[possibleCandidatesWithNoPheromone[rand() % possibleCandidatesWithNoPheromone.size()]] = 1.0;
			sumOfWayStrengths = 1.0;
		}
	}

	double randomValue = ((double)rand() / (RAND_MAX));
	randomValue *= sumOfWayStrengths; // mapowanie na przestrzeñ wartoœci

	double sumOfPastValues = 0.0;
	for (int v = 0; v < this->graphSize; v++) {
		sumOfPastValues = sumOfPastValues + wayStrength[v];
		if (randomValue <= sumOfPastValues || (v == this->graphSize - 1 && wayStrength[v] > 0)) {
			pheromoneValues[ant->GetLastNode()][v] += baseMatrix->GetWeightOfEdge(ant->GetLastNode(), v);
			ant->InsertNodeAtTheEnd(v);

			return;
		}
	}

	//throw std::exception("Nie wybrano nastepnego kroku");
	int largest_element = *max_element(wayStrength.begin(), wayStrength.end());
	pheromoneValues[ant->GetLastNode()][largest_element] += baseMatrix->GetWeightOfEdge(ant->GetLastNode(), largest_element);
	ant->InsertNodeAtTheEnd(largest_element);
}
