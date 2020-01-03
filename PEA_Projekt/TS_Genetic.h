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
	static Path* TS_UseGenetic(
		AdjacencyMatrix* matrix,
		int maxIterations,
		SelectionType selectionType,
		CrossingStrategy crossingStrategy,
		float mutationProbability,
		int verbose);

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
	/// Losuj k1 i k2 oznaczaj�ce granice sekcji dopasowania. 
	/// Zostaw sekcj� niezmienion�, a pozosta�e w�z�y dopisuj w kolejno�ci z drugiego osobnika.
	/// </summary>
	/// <returns></returns>
	Path* crossPaths_OX();
	/// <summary>
	/// Dla ka�dego osobnika populacji, dla ka�dego jego genu, z podanym prawdopodobie�stwem zamie� (swap)
	/// miejscami gen z jego nast�pnikiem.
	/// </summary>
	/// <param name="probability"></param>
	void randomlySwapMutatePopulation(float probability);
};

