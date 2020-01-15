#pragma once
#include "AdjacencyMatrix.h"
#include "Path.h"
using namespace std;

class TS_Genetic
{
public:
	TS_Genetic(AdjacencyMatrix* baseMatrix, int targetPopulationSize);

	enum class SelectionType { rank };
	enum class CrossingStrategy { OX };
	static Path TS_UseGenetic(
		AdjacencyMatrix* matrix,
		int maxIterations, int populationSize,
		SelectionType selectionType,
		CrossingStrategy crossingStrategy,
		float mutationProbability,
		int crossesPerGeneration,
		int verbose);

	/// <summary>
	/// Losuj k1 i k2 oznaczaj¹ce granice sekcji dopasowania. 
	/// Zostaw sekcjê niezmienion¹, a pozosta³e wêz³y dopisuj w kolejnoœci z drugiego osobnika.
	/// </summary>
	/// <returns></returns>
	static std::tuple<Path, Path> crossPaths_OX(Path* p1, Path* p2);

	static bool comparePaths(Path p1, Path p2);

private:
	vector<Path> population;
	int generation = 1;
	int targetPopulationSize = 0;
	AdjacencyMatrix* baseMatrix;

	/// <summary>
	/// Losowo generuje populacjê o wielkoœci targetPopulationSize
	/// </summary>
	/// <param name="size"></param>
	void generateRandomPopulation();
	/// <summary>
	/// Usuwa z populacji najs³absze osobniki aby jej wielkoœæ by³a równa targetPopulationSize
	/// </summary>
	void makeSelection_rank();
	/// <summary>
	/// Spoœród `populationToCross` osobników, dokonaj `numberOfCrosses` losowych krzy¿owañ.
	/// </summary>
	/// <param name="populationToCross"></param>
	void newGeneration_crossBestRandomly(int populationToCross, int numberOfCrosses, CrossingStrategy crossingStrategy);

	/// <summary>
	/// Dla ka¿dego osobnika populacji, dla ka¿dego jego genu, z podanym prawdopodobieñstwem zamieñ (swap)
	/// miejscami gen z jego nastêpnikiem.
	/// </summary>
	/// <param name="probability"></param>
	void randomlySwapMutatePopulation(float probability);

	void sortPopulationByPathCost();
};

