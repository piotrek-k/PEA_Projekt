#pragma once
#include "Path.h"
class AlgorithmResultContainer
{
public:
	Path* path;
	int memoryUsed;
	AlgorithmResultContainer(Path* path, int memoryUsed);
};

