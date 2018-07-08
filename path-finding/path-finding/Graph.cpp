#include "Graph.h"
#include <algorithm>
#include <deque>


Graph::Graph(unsigned int graphRows, unsigned int graphColumns, unsigned int outBufferSize)
	: m_graphRows(graphRows), m_graphColumns(graphColumns), m_pValue(0.001f)
{
	//pValue is used to avoid ties between nodes in their estimated distance.
	//We use 1/1000 as a standard value but if the max length of the path is longer we use that instead.
	if (outBufferSize > 1000)
		m_pValue = 1.0f / static_cast<float>(outBufferSize);

	m_nodes.reserve(m_graphRows * m_graphColumns);
}

Graph::~Graph()
{
	m_nodes.clear();
}

void Graph::AddNode(int nodeIndex, Position nodePosition, bool passable)
{
	m_nodes.emplace_back(Node(nodeIndex, nodePosition, passable));
}

int Graph::FindShortestPath(const Position& start, const Position& target)
{
	m_currentTarget = target;
	//Locate the start node and add it to the visit list.
	for (unsigned int i = 0; i < m_nodes.size(); i++)
	{
		if (m_nodes.at(i).GetPos() == start)
		{
			m_nodes.at(i).SetAddedToVisitList(true);
			m_visitList.push(std::make_pair(0.0f, m_nodes.at(i).GetIndex()));
			break;
		}
	}

	int targetFound = -1;
	//Begin the search
	while (!m_visitList.empty())
	{
		//Get next node to visit
		bool nextNodeFound = false;
		while (!nextNodeFound)
		{
			//Duplicates are allowed in visitlist but are removed if they have already been visited.
			//This is compromise since we can't erase entries from the priority queue when we
			//find an already added node but with a shorter path.
			if (m_nodes.at(m_visitList.top().second).GetVisited())
				m_visitList.pop();
			else
				nextNodeFound = true;
		}
		Node& currentNode = m_nodes.at(m_visitList.top().second);

		//Check if this node is our target
		if (currentNode.GetPos() == target)
		{
			targetFound = currentNode.GetIndex();
			break;
		}
		currentNode.SetVisited(true);
		//Remove node from visit list.
		m_visitList.pop();
		int currentIndex = currentNode.GetIndex();

		//Add above neighbour to visit list, if one exists
		if (currentNode.GetPos().m_nX != 0)
		{
			//Check if node is passable and not visited already.
			Node& node = m_nodes.at(currentNode.GetIndex() - 1);
			if (node.GetPassable() && !node.GetVisited())
				AddVisitList(node, currentIndex, currentNode.GetSteps());
		}
		//Add right neighbour to visit list, if one exists
		if (currentNode.GetPos().m_nY != (m_graphColumns - 1))
		{
			//Check if node is passable and not visited already.
			Node& node = m_nodes.at(currentNode.GetIndex() + m_graphRows);
			if (node.GetPassable() && !node.GetVisited())
				AddVisitList(node, currentIndex, currentNode.GetSteps());
		}
		//Add under neighbour to visit list, if one exists
		if (currentNode.GetPos().m_nX != (m_graphRows - 1))
		{
			//Check if node is passable and not visited already.
			Node& node = m_nodes.at(currentNode.GetIndex() + 1);
			if (node.GetPassable() && !node.GetVisited())
				AddVisitList(node, currentIndex, currentNode.GetSteps());
		}
		//Add left neighbour to visit list, if one exists
		if (currentNode.GetPos().m_nY != 0)
		{
			//Check if node is passable and not visited already.
			Node& node = m_nodes.at(currentNode.GetIndex() - m_graphRows);
			if (node.GetPassable() && node.GetVisited())
				AddVisitList(node, currentIndex, currentNode.GetSteps());
		}
	}

	return targetFound;
}

void Graph::AddVisitList(Node& node, const unsigned int currentIndex, const int currentSteps)
{
	//Check if node has not been added to the visit list
	if (!node.GetAddedToVisitList())
	{
		node.SetFromIndex(currentIndex);

		float estimatedDistance = static_cast<float>(currentSteps + 1) + (node.GetPos().GetDistance(m_currentTarget) * (1.0f + m_pValue));

		node.SetEstimatedDistance(estimatedDistance);
		node.SetSteps(currentSteps + 1);
		m_visitList.push(std::make_pair(estimatedDistance, node.GetIndex()));
		node.SetAddedToVisitList(true);
		return;
	}
	//node already in visit list with lower distance, don't add it to visit list.
	else if ((currentSteps + 1) >= node.GetSteps())
		return;

	//This is a shorter path to this node than before.
	node.SetFromIndex(currentIndex);
	node.SetSteps(currentSteps + 1);

	float estimatedDistance = static_cast<float>(currentSteps + 1) + (node.GetPos().GetDistance(m_currentTarget) * (1.0f + m_pValue));

	node.SetEstimatedDistance(estimatedDistance);
	m_visitList.push(std::make_pair(estimatedDistance, node.GetIndex()));
}

void Graph::ConstructPath(const Node& node, int* outBuffer, const int outBufferSize)
{
	std::deque<int> path;
	path.push_front(node.GetIndex());

	int nextNode = node.GetFromIndex();
	while (m_nodes.at(nextNode).GetSteps() != 0)
	{
		path.push_front(nextNode);
		nextNode = m_nodes.at(nextNode).GetFromIndex();
	}
	for (unsigned int i = 0; i < path.size(); i++)
	{
		if (static_cast<int>(i) < outBufferSize)
			outBuffer[i] = path.at(i);
		else
			break;
	}
}

const Node& Graph::GetNode(const unsigned int nodeIndex) const
{
	return m_nodes.at(nodeIndex);
}