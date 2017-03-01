#pragma once
#include <vector>
#include <cstdlib>

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

	float GetDistance(const Position &rhs) const
	{
		float dx = static_cast<float>(m_nX) - static_cast<float>(rhs.m_nX);
		float dy = static_cast<float>(m_nY) - static_cast<float>(rhs.m_nY);
		float distance = sqrt((dx * dx) + (dy * dy));

		return distance;
	}
};

inline bool operator==(const Position &lhs, const Position &rhs) { return lhs.m_nX == rhs.m_nX && lhs.m_nY == rhs.m_nY;  }

class Node
{
public:
	Node(unsigned int index, Position pos, bool passable);

	Node();
	
	~Node();

	unsigned int GetIndex() const;

	Position GetPos() const;

	bool GetPassable() const;

	void SetVisited(bool isVisited);

	bool GetVisited() const;

	void SetSteps(int steps);

	int GetSteps() const;

	void SetEstimatedDistance(float estimatedDistance);

	float GetEstimatedDistance() const;

	void SetFromIndex(unsigned int fromIndex);

	unsigned int GetFromIndex() const;

	void SetAddedToVisitList(bool added);

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