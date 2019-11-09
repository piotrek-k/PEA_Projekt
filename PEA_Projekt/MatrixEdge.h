#pragma once
class MatrixEdge
{
public:
	int weight = 0;
	bool initialized = false;

	MatrixEdge();
	MatrixEdge(int weight);
	~MatrixEdge();
};

