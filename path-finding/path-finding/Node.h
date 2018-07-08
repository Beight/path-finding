#pragma once
#include <vector>
#include <cstdlib>

//Struct describing a position in the graph by x and y values.
struct Position
{
	int m_nX;
	int m_nY;

	Position(int nX, int nY)
		: m_nX(nX), m_nY(nY)
	{

	}

	Position()
		: m_nX(0), m_nY(0)
	{

	}
	//Get the the distance between this position and another.
	//param rhs: Position to calculate distance to.
	//Returns the distance between this position and the position provided. NOTE: Does not take impassable nodes into account.
	float GetDistance(const Position& rhs) const
	{
		return static_cast<float>(std::abs(m_nX - rhs.m_nX) + std::abs(m_nY - rhs.m_nY));
	}
};

inline bool operator==(const Position& lhs, const Position& rhs) { return lhs.m_nX == rhs.m_nX && lhs.m_nY == rhs.m_nY;  }

class Node
{
public:
	//Constructor
	//param index: Index of the node in the graph.
	//param pos: Position of the node in the graph.
	//param passable: Set if this node is passable or not.
	Node(unsigned int index, Position pos, bool passable);

	//Destructor
	~Node();

	//Get the index of the node.
	unsigned int GetIndex() const;

	//Get Position of the node.
	Position GetPos() const;

	//Check if the node is passable.
	bool GetPassable() const;

	//Set if this node has been visited or not.
	void SetVisited(bool isVisited);

	//Check if this node hase been visited.
	bool GetVisited() const;

	//Set the number of steps to this node from the start node during a search.
	void SetSteps(int steps);

	//Get the number of steps to this node from the start node during a search.
	int GetSteps() const;

	//Set the estimated distance from this node to the target node during a search.
	void SetEstimatedDistance(float estimatedDistance);

	//Get the estimated distance from this node to the target node during a search.
	float GetEstimatedDistance() const;

	//Set which node index this node was reached from.
	void SetFromIndex(unsigned int fromIndex);

	//Get which node index this node was reached from, used for constructing the shortest path if it has been found.
	unsigned int GetFromIndex() const;

	//Set if this node has been added to the visit list during a search.
	void SetAddedToVisitList(bool added);

	//Get if this node has been added to the visit list during a search.
	bool GetAddedToVisitList() const;

private:
	unsigned int m_index;
	Position m_pos;
	bool m_passable;
	bool m_isVisited;
	int m_steps;
	unsigned int m_fromIndex;
	float m_estimatedDistance;
	bool m_addedToVisitList;
};