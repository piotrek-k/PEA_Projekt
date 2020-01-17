#pragma once
#include "../PEA_Projekt/Path.h"
#include <time.h>
#include <stdlib.h> 
using namespace std;

class TS_Ant_Colony
{
public:
	TS_Ant_Colony(AdjacencyMatrix* matrix,
		int numberOfAnts,
		float collectiveMemoryPower,
		float greedyChoicePower,
		float evaporationRate,
		float pheromoneStartValue);

	/*
	1. Rozmie�� mr�wki
	2. Powtarzaj m (il. mr�wek) razy
	- 2a. Przemie�� mr�wk�
	3. Odparuj feromon
	*/
	static Path TS_UseAntColony(
		AdjacencyMatrix* matrix,
		int maxNumOfIterations,
		int numberOfAnts,
		float collectiveMemoryPower,
		float greedyChoicePower,
		float evaporationRate,
		float pheromoneStartValue,
		bool verbose
	);

	vector<Path> ants = vector<Path>();

private:
	
	AdjacencyMatrix* baseMatrix = new AdjacencyMatrix();
	int graphSize = -1;
	float** pheromoneValues; //[a][b] reprezentuje warto�� feromonu na drodze z a do b

	int numberOfAnts;
	float collectiveMemoryPower; // si�a wp�ywu feromonu na decyzj� o nast�pnym kroku
	float greedyChoicePower; // si�a algorytmu zach�annego na decyzj� o nast�pnym kroku
	float evaporationRate; // pr�dko�� parowania
	float pheromoneStartValue; // pocz�tkowa warto�� feromonu
	

	void SeedAnts(int numberOfAnts);
	void EvaporatePheromone(float speed);
	void MoveAntLeavePheromone(Path* ant);
};

