#include "AdjacencyMatrix.h"
#include <fstream>
#include <sstream>

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

		int col = 0;

		stringstream stream(line);
		string extractedPart;
		int extractedWeight;
		while (!stream.eof()) {
			try {
				stream >> extractedWeight;

				this->matrix[row][col] = Edge(row, col, extractedWeight);

				col++;
			}
			catch (const exception & e) {
				*output << "Konwersja string -> int nie powiodla sie" << endl;
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
	this->matrix = new Edge * [this->size];
	for (int a = 0; a < this->size; a++) {
		this->matrix[a] = new Edge[this->size];
	}
}

void AdjacencyMatrix::Display(std::ostream& output)
{
	output << "Nazwa: " << this->name << endl;
	output << "Wielkosc: " << this->size << endl;

	for (int row = 0; row < this->size; row++) {
		for (int col = 0; col < this->size; col++) {
			output << this->matrix[row][col].weight << " ";
		}
		output << std::endl;
	}
}
