#pragma once
#include <string>
#include "AdjacencyMatrix.h"
#include "Path.h"
#include "AlgorithmResultContainer.h"
class BulkDataTester
{
private:
	std::vector<std::string> fileNames = std::vector<std::string>();
	std::vector<AdjacencyMatrix> matrices = std::vector < AdjacencyMatrix>();
public:
	std::string basePath;
	void LoadFileNames(std::string& fileNamesStoragePath, std::ostream& progressStream);
	void TestAlgorithm(AlgorithmResultContainer* algorithm(AdjacencyMatrix*, int), std::ostream& fileStream, std::ostream& consoleStream, int repetitions);
};

