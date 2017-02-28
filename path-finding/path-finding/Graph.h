#pragma once
#include <queue>
#include "Node.h"

struct Compare
{
	bool operator() (const std::pair<unsigned int, unsigned int> & lhs, const std::pair<unsigned int, unsigned int> & rhs) const
	{
		return lhs.first > rhs.first;
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

	void AddVisitList(Node& n, const unsigned int currentIndex, const int currentSteps, std::priority_queue<std::pair<unsigned int, unsigned int>, std::vector<std::pair<unsigned int, unsigned int>>, Compare> &nodesToVisit, const Position &start, const Position &target);

private:
	std::vector<Node> m_nodes;
	unsigned int m_graphWidth;
	unsigned int m_graphHeight;
};