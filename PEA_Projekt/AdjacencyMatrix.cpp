#include "AdjacencyMatrix.h"
#include <fstream>
#include <sstream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

AdjacencyMatrix::AdjacencyMatrix()
{
}

AdjacencyMatrix::AdjacencyMatrix(const std::string& fileName)
{
	LoadDataFromFile(fileName);
}

void AdjacencyMatrix::LoadDataFromStream(std::istream& myfile, std::ostream* output)
{
	string line;

	// linia 1.: nazwa:
	if (output != nullptr) {
		*output << "Podaj nazwe" << endl;
	}
	getline(myfile, line);
	this->name = line;

	// linia 2.: wielkoœæ
	if (output != nullptr) {
		*output << "Podaj wielkosc" << endl;
	}
	getline(myfile, line);
	this->size = stoi(line);
	this->RebuildMatrix();

	if (output != nullptr) {
		*output << "Podaj kolejne linie:" << endl;
	}
	// kolejne linie:
	int row = 0;
	while (getline(myfile, line))
	{
		if (line == "") {
			break;
		}

		//std::cout << "row " << row << std::endl;

		int col = 0;

		stringstream stream(line);
		string extractedPart = "";
		int extractedWeight = 0;
		while (!stream.eof()) {
			try {
				if (stream >> extractedWeight) {
					//std::cout << col << " ";

					this->matrix[row][col] = new MatrixEdge(extractedWeight);

					col++;
				}
			}
			catch (const exception & e) {
				if (output != nullptr) {
					*output << "Konwersja string -> int nie powiodla sie" << endl;
				}
			}
		}

		row++;
	}
}

void AdjacencyMatrix::LoadDataFromFile(const std::string& fileName)
{

	ifstream myfile(fileName);
	try {
		if (myfile.is_open())
		{
			this->LoadDataFromStream(myfile, nullptr);
		}
	}
	catch (const exception & e) {
		throw exception("Wystapil problem z wczytaniem danych z pliku");
	}

}

void AdjacencyMatrix::RebuildMatrix()
{
	this->matrix = new MatrixEdge ** [this->size];
	for (int a = 0; a < this->size; a++) {
		this->matrix[a] = new MatrixEdge *[this->size];
	}
}

void AdjacencyMatrix::BuildRandomly(int size, int min, int max)
{
	/* initialize random seed: */
	srand(time(NULL));
	this->size = size;
	RebuildMatrix();

	for (int col = 0; col < size; col++) {
		for (int row = 0; row < size; row++) {
			/* generate number between 1 and 10: */
			int number = 0;
			if (col != row) {
				number = rand() % max + min;
			}
			else {
				number = -1;
			}
			this->matrix[col][row] = new MatrixEdge(number);
		}
	}
}

void AdjacencyMatrix::Display(std::ostream& output)
{
	output << "Nazwa: " << this->name << endl;
	output << "Wielkosc: " << this->size << endl;

	for (int row = 0; row < this->size; row++) {
		for (int col = 0; col < this->size; col++) {
			output << this->matrix[row][col]->weight << " ";
		}
		output << std::endl;
	}
}

void AdjacencyMatrix::DisplayDetails(std::ostream& output)
{
	std::tuple<double, double, double, double> result = AvgAndVarianceOfAll();
	double avgAvg = std::get<0>(result);
	double avgVar = std::get<1>(result);
	output << "Average: " << avgAvg << std::endl <<
		" Avg variance: " << avgVar << std::endl <<
		" Avg overall distance: " << std::get<2>(result) << std::endl <<
		" Expected deviation: " << std::get<3>(result) <<
		std::endl;
}

int AdjacencyMatrix::GetWeightOfEdge(int from, int to)
{
	return matrix[from][to]->weight;
}

int AdjacencyMatrix::GetSize()
{
	return this->size;
}

std::tuple<double, double> AdjacencyMatrix::AvgAndVarianceOfNode(int nodeIndex)
{
	int sumOfWeights = 0;
	int sumOfElems = 0;
	for (int i = 0; i < size; i++) {
		if (i == nodeIndex) continue;
		sumOfWeights += matrix[nodeIndex][i]->weight;
		sumOfElems++;
	}
	double average = (double) sumOfWeights / (double)sumOfElems;

	double sumOfDeviations = 0;
	int numOfDeviations = 0;
	for (int i = 0; i < size; i++) {
		if (i == nodeIndex) continue;
		sumOfDeviations += pow(matrix[nodeIndex][i]->weight - average, 2);
		numOfDeviations++;
	}
	double variance = (double)sumOfDeviations / (double)numOfDeviations;

	return std::tuple<double, double>(average, variance);
}

std::tuple<double, double, double, double> AdjacencyMatrix::AvgAndVarianceOfAll()
{
	double avgAvgSum = 0;
	double avgVarSum = 0;
	double avgDeviation = 0;
	for (int i = 0; i < size; i++) {
		std::tuple<double, double> result = AvgAndVarianceOfNode(i);
		avgAvgSum += std::get<0>(result);
		avgVarSum += std::get<1>(result);
		avgDeviation += sqrt(std::get<1>(result));
	}
	return std::tuple<double, double, double, double>(
		avgAvgSum/(double)size, 
		avgVarSum/(double)size, 
		avgAvgSum / (double)size * (size-1),
		avgDeviation / (double)size);
}
