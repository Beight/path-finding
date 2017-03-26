#include "Graph.h"
#include <algorithm>
#include <deque>


Graph::Graph(unsigned int graphWidth, unsigned int graphHeight, unsigned int outBufferSize)
	: m_graphWidth(graphWidth), m_graphHeight(graphHeight), m_pValue(0.001f)
{
	if (outBufferSize > 1000)
		m_pValue = 1.0f / static_cast<float>(outBufferSize);

	m_nodes.reserve(m_graphWidth * m_graphHeight);
}

Graph::~Graph()
{

}

void Graph::AddNode(Node node)
{
	m_nodes.push_back(node);
}

int Graph::FindShortestPath(const Position& start, const Position& target)
{
	VisitList nodesToVisit;
	for (unsigned int i = 0; i < m_nodes.size(); i++)
	{
		if (m_nodes.at(i).GetPos() == start)
		{
			m_nodes.at(i).SetAddedToVisitList(true);
			nodesToVisit.push(std::make_pair(0.0f, m_nodes.at(i).GetIndex()));
			break;
		}
	}
	int targetFound = -1;
	while (!nodesToVisit.empty())
	{
		//Get next node to visit
		bool nextNodeFound = false;
		while (!nextNodeFound)
		{
			//duplicates are allowed in openlist but are removed if they have already been visited.
			//This is comprimise since we can't erase entries from the priority queue when we find duplicates.
			if (m_nodes.at(nodesToVisit.top().second).GetVisited())
				nodesToVisit.pop();
			else
				nextNodeFound = true;
		}

		Node& currentNode = m_nodes.at(nodesToVisit.top().second);
		//Check if this node is our target
		if (currentNode.GetPos() == target)
		{
			targetFound = currentNode.GetIndex();
			break;
		}
		currentNode.SetVisited(true);
		//Remove node from visit list.
		nodesToVisit.pop();

		//Add above neighbour to visit list, if one exists
		if (currentNode.GetPos().m_nX != 0)
			AddVisitList(m_nodes.at(currentNode.GetIndex() - 1), currentNode.GetIndex(), currentNode.GetSteps(), nodesToVisit, start, target);
		//Add right neighbour to visit list, if one 
		if (currentNode.GetPos().m_nY != (m_graphHeight - 1))
			AddVisitList(m_nodes.at(currentNode.GetIndex() + m_graphWidth), currentNode.GetIndex(), currentNode.GetSteps(), nodesToVisit, start, target);
		//Add under neighbour to visit list, if one exists
		if (currentNode.GetPos().m_nX != (m_graphWidth - 1))
			AddVisitList(m_nodes.at(currentNode.GetIndex() + 1), currentNode.GetIndex(), currentNode.GetSteps(), nodesToVisit, start, target);
		//Add left neighbour to visit list, if one exists
		if (currentNode.GetPos().m_nY != 0)
			AddVisitList(m_nodes.at(currentNode.GetIndex() - m_graphWidth), currentNode.GetIndex(), currentNode.GetSteps(), nodesToVisit, start, target);
	}

	return targetFound;
}

void Graph::AddVisitList(Node& n, const unsigned int currentIndex, const int currentSteps, VisitList &nodesToVisit, const Position &start, const Position &target)
{
	if (n.GetPassable() && !n.GetVisited())
	{
		float estimatedDistance = static_cast<float>(currentSteps + 1) + (n.GetPos().GetDistance(target) * (1.0f + m_pValue));

		//Check if node has not been added to the visit list
		if (!n.GetAddedToVisitList())
		{
			n.SetFromIndex(currentIndex);
			n.SetEstimatedDistance(estimatedDistance);
			n.SetSteps(currentSteps + 1);
			nodesToVisit.push(std::make_pair(estimatedDistance, n.GetIndex()));
			n.SetAddedToVisitList(true);
			return;
		}
		//node already in visit list with lower distance
		else if ((currentSteps + 1) >= n.GetSteps())
			return;

		//This is a shorter path to this node than before.
		n.SetFromIndex(currentIndex);
		n.SetSteps(currentSteps + 1);
		n.SetEstimatedDistance(estimatedDistance);
		nodesToVisit.push(std::make_pair(estimatedDistance, n.GetIndex()));
	}
}

void Graph::ConstructPath(Node node, int *pOutBuffer, const int nOutBufferSize)
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
		if (static_cast<int>(i) < nOutBufferSize)
			pOutBuffer[i] = path.at(i);
		else
			break;
	}
}

Node Graph::GetNode(unsigned int nodeIndex)
{
	return m_nodes.at(nodeIndex);
}