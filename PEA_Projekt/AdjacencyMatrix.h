#pragma once
#include <string>
#include <iostream>
#include "Edge.h"
class AdjacencyMatrix
{
private:
	Edge** matrix = nullptr;
public:
	std::string name;
	int size;
	AdjacencyMatrix();
	AdjacencyMatrix(const std::string& fileName);

	void LoadDataFromStream(std::istream& stream, std::ostream* output);
	void LoadDataFromFile(const std::string& fileName);
	void RebuildMatrix();
	void Display(std::ostream& output);
};

