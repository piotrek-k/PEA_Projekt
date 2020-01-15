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
	/// Losuj k1 i k2 oznaczaj�ce granice sekcji dopasowania. 
	/// Zostaw sekcj� niezmienion�, a pozosta�e w�z�y dopisuj w kolejno�ci z drugiego osobnika.
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
	/// Losowo generuje populacj� o wielko�ci targetPopulationSize
	/// </summary>
	/// <param name="size"></param>
	void generateRandomPopulation();
	/// <summary>
	/// Usuwa z populacji najs�absze osobniki aby jej wielko�� by�a r�wna targetPopulationSize
	/// </summary>
	void makeSelection_rank();
	/// <summary>
	/// Spo�r�d `populationToCross` osobnik�w, dokonaj `numberOfCrosses` losowych krzy�owa�.
	/// </summary>
	/// <param name="populationToCross"></param>
	void newGeneration_crossBestRandomly(int populationToCross, int numberOfCrosses, CrossingStrategy crossingStrategy);

	/// <summary>
	/// Dla ka�dego osobnika populacji, dla ka�dego jego genu, z podanym prawdopodobie�stwem zamie� (swap)
	/// miejscami gen z jego nast�pnikiem.
	/// </summary>
	/// <param name="probability"></param>
	void randomlySwapMutatePopulation(float probability);

	void sortPopulationByPathCost();
};

