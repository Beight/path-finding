#pragma once
#include <queue>
#include "Node.h"

struct Compare
{
	bool operator() (const std::pair<float, unsigned int> & lhs, const std::pair<float, unsigned int> & rhs) const
	{
		return lhs.first > rhs.first;
	}
};

class Graph
{

public:
	typedef std::priority_queue<std::pair<float, unsigned int>, std::vector<std::pair<float, unsigned int>>, Compare> VisitList;

	Graph(unsigned int graphWidth, unsigned int graphHeight, unsigned int outBufferSize);
	~Graph();

	void AddNode(Node node);

	int FindShortestPath(const Position &start, const Position& target);

	void ConstructPath(Node node, int *pOutBuffer, const int nOutBufferSize);

	Node GetNode(unsigned int nodeIndex);

	void AddVisitList(Node& n, const unsigned int currentIndex, const int currentSteps, VisitList &nodesToVisit, const Position &start, const Position &target);

private:
	std::vector<Node> m_nodes;
	unsigned int m_graphWidth;
	unsigned int m_graphHeight;
	float m_pValue;
};