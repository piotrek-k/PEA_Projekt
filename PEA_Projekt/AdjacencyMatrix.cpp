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

int AdjacencyMatrix::GetWeightOfEdge(int from, int to)
{
	return matrix[from][to]->weight;
}

int AdjacencyMatrix::GetSize()
{
	return this->size;
}
