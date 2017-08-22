#pragma once
#include <queue>
#include "Node.h"

//Struct used by the priority queue to calculate the priority of the nodes which is based on their estimated distance to target.
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

	//Constructor
	//param graphWidth: Width of the graph.
	//param graphHeigth: Height of the graph.
	//param outBufferSize: Size of the buffer that will be filled with nodes representing the shortest path. Can also be seen as the max length of the path. Used to calculate p-value.
	Graph(unsigned int graphWidth, unsigned int graphHeight, unsigned int outBufferSize);

	//Destructor
	~Graph();

	//Adds a node to the graph.
	//param node: Node to add.
	void AddNode(Node node);

	//Searches for the shortest path from a start position in the graph to a target target position.
	//param start: Starting position of the search.
	//param target: Target position of the search.
	//Returns the shortest number of steps to the target. Returns -1 if no path was found.
	int FindShortestPath(const Position &start, const Position& target);

	//Constructs a path from the result of the FindShortestPath function.
	//param node: The target node from FindShortestPath function.
	//param pOutBuffer: pointer to the out buffer where the constructed path will be stored.
	//param nOutBufferSize: Size of the out buffer.
	void ConstructPath(Node node, int *pOutBuffer, const int nOutBufferSize);

	//Get a specific node in the graph.
	//param nodeIndex: Index of the node to get.
	Node GetNode(unsigned int nodeIndex);

private:
	void AddVisitList(Node& n, const unsigned int currentIndex, const int currentSteps, VisitList &nodesToVisit, const Position &target);
	
	std::vector<Node> m_nodes;
	unsigned int m_graphWidth;
	unsigned int m_graphHeight;
	float m_pValue;
};