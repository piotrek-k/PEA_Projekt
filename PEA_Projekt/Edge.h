#pragma once
class Edge
{
public:
	int from = 0;
	int to = 0;
	int weight = 0;
	bool initialized = false;

	Edge();
	Edge(int from, int to, int weight);
	~Edge();
};

