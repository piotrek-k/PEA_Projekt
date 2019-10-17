#include "AdjacencyMatrix.h"
#include <fstream>
#include <sstream>

using namespace std;

AdjacencyMatrix::AdjacencyMatrix(const std::string& fileName)
{
	LoadDataFromFile(fileName);
}

void AdjacencyMatrix::LoadDataFromFile(const std::string& fileName)
{
	string line;
	ifstream myfile(fileName);
	try {
		if (myfile.is_open())
		{
			// linia 1.: nazwa:
			getline(myfile, line);
			this->name = line;

			// linia 2.: wielkoœæ
			getline(myfile, line);
			this->size = stoi(line);
			this->RebuildMatrix();

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
					stream >> extractedWeight;

					if (stream.good()) {
						// extracting integer went without problems

						this->matrix[row][col] = Edge(row, col, extractedWeight);

						col++;
					}
				}

				row++;
			}
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

void AdjacencyMatrix::Display()
{
	for (int row = 0; row < this->size; row++) {
		for (int col = 0; col < this->size; col++) {
			std::cout << this->matrix[row][col].weight << " ";
		}
		cout << std::endl;
	}
}
