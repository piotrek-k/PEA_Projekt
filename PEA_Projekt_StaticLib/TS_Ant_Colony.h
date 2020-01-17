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
	1. Rozmieœæ mrówki
	2. Powtarzaj m (il. mrówek) razy
	- 2a. Przemieœæ mrówkê
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
	float** pheromoneValues; //[a][b] reprezentuje wartoœæ feromonu na drodze z a do b

	int numberOfAnts;
	float collectiveMemoryPower; // si³a wp³ywu feromonu na decyzjê o nastêpnym kroku
	float greedyChoicePower; // si³a algorytmu zach³annego na decyzjê o nastêpnym kroku
	float evaporationRate; // prêdkoœæ parowania
	float pheromoneStartValue; // pocz¹tkowa wartoœæ feromonu
	

	void SeedAnts(int numberOfAnts);
	void EvaporatePheromone(float speed);
	void MoveAntLeavePheromone(Path* ant);
};

