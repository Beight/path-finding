#pragma once
#include <queue>
#include "Node.h"

//Struct used by the priority queue to calculate the priority of the nodes which is based on their estimated distance to target.
struct Compare
{
	bool operator() (const std::pair<float, unsigned int>& lhs, const std::pair<float, unsigned int>& rhs) const
	{
		return lhs.first > rhs.first;
	}
};

class Graph
{

public:
	typedef std::priority_queue<std::pair<float, unsigned int>, std::vector<std::pair<float, unsigned int>>, Compare> VisitList;

	//Constructor
	//param graphRows: Number of rows in the graph.
	//param graphHeigth: Number of columns in the graph.
	//param outBufferSize: Size of the buffer that will be filled with nodes representing the shortest path. Can also be seen as the max length of the path. Used to calculate p-value.
	Graph(const unsigned int graphRows, const unsigned int graphColumns, const unsigned int outBufferSize);

	//Destructor
	~Graph();

	//Adds a node to the graph.
	//param nodeIndex: index of the node to be added.
	//param nodePosition: nodes position in the graph.
	//param passable: Set if node is passable or not.
	void AddNode(const int nodeIndex, const Position nodePosition, const bool passable);

	//Searches for the shortest path from a start position in the graph to a target target position.
	//param start: Starting position of the search.
	//param target: Target position of the search.
	//Returns the shortest number of steps to the target. Returns -1 if no path was found.
	int FindShortestPath(const Position& start, const Position& target);

	//Constructs a path from the result of the FindShortestPath function.
	//param node: The target node from FindShortestPath function.
	//param pOutBuffer: pointer to the out buffer where the constructed path will be stored.
	//param nOutBufferSize: Size of the out buffer.
	void ConstructPath(const Node& node, int* outBuffer, const int outBufferSize);

	//Get a specific node in the graph.
	//param nodeIndex: Index of the node to get.
	const Node& GetNode(const unsigned int nodeIndex) const;

private:
	void AddVisitList(Node& node, const unsigned int currentIndex, const int currentSteps);
	
	std::vector<Node> m_nodes;
	VisitList m_visitList;
	unsigned int m_graphRows;
	unsigned int m_graphColumns;
	float m_pValue;
	Position m_currentTarget;
};