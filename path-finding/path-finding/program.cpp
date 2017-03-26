#include "Graph.h"
#include <iostream>

int FindPath(	const int nStartX, const int nStartY,
				const int nTargetX, const int nTargetY,
				const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
				int * pOutBuffer, const int nOutBufferSize);


int FindPath(const int nStartX, const int nStartY, const int nTargetX, const int nTargetY, const unsigned char *pMap, const int nMapWidth, const int nMapHeight, int * pOutBuffer, const int nOutBufferSize)
{
	unsigned int mapIterator = 0;
	Graph graph = Graph(nMapWidth, nMapHeight, nOutBufferSize);
	for (int i = 0; i < nMapHeight; i++)
	{
		for (int j = 0; j < nMapWidth; j++)
		{
			bool passable = false;
			if (pMap[mapIterator] == '\1')
				passable = true;

			graph.AddNode(Node(mapIterator, Position(j, i), passable));
			mapIterator++;
		}
	}

	int targetNodeIndex = graph.FindShortestPath(Position(nStartX, nStartY), Position(nTargetX, nTargetY));
	if (targetNodeIndex == -1)
		return -1;

	graph.ConstructPath(graph.GetNode(targetNodeIndex), pOutBuffer, nOutBufferSize);

	return graph.GetNode(targetNodeIndex).GetSteps();
}