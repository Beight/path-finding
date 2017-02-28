#include "Node.h"

Node::Node(unsigned int index, Position pos, bool passable)
	: m_index(index), m_pos(pos), m_passable(passable), m_isVisited(false), m_steps(0), m_fromIndex(0), m_estimatedDistance(0), m_addedToVisitList(false)
{

}

Node::~Node()
{
	
}

unsigned int Node::GetIndex() const
{
	return m_index;
}

Position Node::GetPos() const
{
	return m_pos;
}

bool Node::GetPassable() const
{
	return m_passable;
}

void Node::SetVisited(bool isVisited)
{
	m_isVisited = isVisited;
}

bool Node::GetVisited() const
{
	return m_isVisited;
}

void Node::SetSteps(int steps)
{
	m_steps = steps;
}

int Node::GetSteps() const
{
	return m_steps;
}

void Node::SetFromIndex(unsigned int fromIndex)
{
	m_fromIndex = fromIndex;
}

unsigned int Node::GetFromIndex() const
{
	return m_fromIndex;
}

void Node::SetEstimatedDistance(int estimatedDistance)
{
	m_estimatedDistance = estimatedDistance;
}

int Node::GetEstimatedDistance() const
{
	return m_estimatedDistance;
}

void Node::SetAddedToVisitList(bool added)
{
	m_addedToVisitList = added;
}

bool Node::GetAddedToVisitList() const 
{
	return m_addedToVisitList;
}