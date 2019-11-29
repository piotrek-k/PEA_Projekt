#pragma once
#include <string>
#include <iostream>
#include "MatrixEdge.h"
#include <tuple>
class AdjacencyMatrix
{
private:
	MatrixEdge*** matrix = nullptr;
	int size = 0;
public:
	std::string name;
	
	AdjacencyMatrix();
	AdjacencyMatrix(const std::string& fileName);

	void LoadDataFromStream(std::istream& stream, std::ostream* output);
	void LoadDataFromFile(const std::string& fileName);
	void RebuildMatrix();
	void BuildRandomly(int size, int min, int max);
	void Display(std::ostream& output);
	void DisplayDetails(std::ostream& output);

	int GetWeightOfEdge(int from, int to);
	int GetSize();

	std::tuple<double, double> AvgAndVarianceOfNode(int nodeIndex);
	std::tuple<double, double, double, double> AvgAndVarianceOfAll();
};

