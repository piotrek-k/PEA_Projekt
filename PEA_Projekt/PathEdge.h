#pragma once
class PathEdge
{
public:
	int from = -1;
	int to = -1;

	PathEdge();
	PathEdge(int from, int to);
	~PathEdge();
};

