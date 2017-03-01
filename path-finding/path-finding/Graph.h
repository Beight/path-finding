#pragma once
#include <set>
#include "Node.h"

struct Compare
{
	bool operator() (const std::pair<float, unsigned int> & lhs, const std::pair<float, unsigned int> & rhs) const
	{
		return lhs.first < rhs.first;
	}
};

class Graph
{

public:
	Graph(unsigned int graphWidth, unsigned int graphHeight);
	~Graph();

	void AddNode(Node node);

	int FindShortestPath(const Position &start, const Position& target);

	void ConstructPath(Node node, int *pOutBuffer, const int nOutBufferSize);

	Node GetNode(unsigned int nodeIndex);

	void AddVisitList(Node& n, const unsigned int currentIndex, const int currentSteps, std::set<std::pair<float, unsigned int>, Compare> &nodesToVisit, const Position &start, const Position &target);

private:
	std::vector<Node> m_nodes;
	unsigned int m_graphWidth;
	unsigned int m_graphHeight;
};