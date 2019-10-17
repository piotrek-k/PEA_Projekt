#include "Edge.h"

Edge::Edge()
{
}

Edge::Edge(int from, int to, int weight)
{
	this->from = from;
	this->to = to;
	this->weight = weight;
	this->initialized = true;
}

Edge::~Edge()
{

}
