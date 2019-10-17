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
	AdjacencyMatrix(const std::string& fileName);

	void LoadDataFromFile(const std::string& fileName);
	void RebuildMatrix();
	void Display();
};

