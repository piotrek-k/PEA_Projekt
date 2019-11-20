#include "BulkDataTester.h"
#include <fstream>
#include "TimeCounter.h"
#include <filesystem>
using namespace std;

string GetDirectory(const string& str)
{
	size_t found;
	//cout << "Splitting: " << str << endl;
	found = str.find_last_of("/\\");
	//cout << " folder: " << str.substr(0, found) << endl;
	return str.substr(0, found);
	//cout << " file: " << str.substr(found + 1) << endl;
}

void BulkDataTester::LoadFileNames(std::string& fileNamesStoragePath, std::ostream& progressStream)
{
	fileNames.clear();
	matrices.clear();

	basePath = GetDirectory(fileNamesStoragePath);

	ifstream myfile(fileNamesStoragePath);
	try {
		if (myfile.is_open())
		{
			string line;
			while (getline(myfile, line))
			{
				if (line == "") {
					break;
				}

				auto fileName = line.substr(0, line.find(' '));

				string newEntry = basePath + "\\" + fileName + ".txt";
				fileNames.push_back(newEntry);
				AdjacencyMatrix newAM = AdjacencyMatrix(newEntry);
				matrices.push_back(newAM);
				progressStream << newEntry << endl;
				//newAM.Display(progressStream);
			}
		}
	}
	catch (const exception & e) {
		throw exception("Wystapil problem z wczytaniem danych z pliku");
	}
}

void BulkDataTester::TestAlgorithm(Path* algorithm(AdjacencyMatrix*, int), std::ostream& fileStream, std::ostream& consoleStream, int repetitions)
{
	for (int a = 0; a < fileNames.size(); a++) {
		TimeCounter* timeCounter = new TimeCounter();
		timeCounter->ResetCounter();

		consoleStream << "Testing: " << fileNames[a] << endl;
		for (int c = 0; c < repetitions; c++) {
			consoleStream << ".";
			timeCounter->StartNextMeasurement();
			Path* path = algorithm(&matrices[a], 0);
			timeCounter->EndSingleMeasurement();
		}

		auto timeMeasured = timeCounter->Summarize();
		fileStream << fileNames[a] << " " << repetitions << " " << timeMeasured << endl;
		consoleStream << "Sredni czas wykonania algorytmu: " << timeMeasured << "ms dla " << repetitions << "powtorzen." << std::endl;
	}
}
