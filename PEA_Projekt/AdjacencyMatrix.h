#pragma once
#include <string>
#include <iostream>
#include "MatrixEdge.h"
class AdjacencyMatrix
{
private:
	MatrixEdge*** matrix = nullptr;
	int size;
public:
	std::string name;
	
	AdjacencyMatrix();
	AdjacencyMatrix(const std::string& fileName);

	void LoadDataFromStream(std::istream& stream, std::ostream* output);
	void LoadDataFromFile(const std::string& fileName);
	void RebuildMatrix();
	void BuildRandomly(int size, int min, int max);
	void Display(std::ostream& output);

	int GetWeightOfEdge(int from, int to);
	int GetSize();
};

