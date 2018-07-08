#include "Graph.h"
#include <iostream>
#include <fstream>
#include <string>

int FindPath(	const int startX, const int startY,
				const int targetX, const int targetY,
				const char* map, const int mapRows, const int mapColumns,
				int* outBuffer, const int outBufferSize);

int main()
{
	int result = -1;
	int* outBuffer = nullptr;
	int outbufferSize = 0;
	std::cout << "Enter Filename:\n";
	std::string filename;
	std::cin >> filename;
	std::ifstream inFile;
	inFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		inFile.open(filename);

		//Read start position
		int startX, startY;
		inFile >> startX >> startY;
		//Read target position
		int targetX, targetY;
		inFile >> targetX >> targetY;
		//Read size of graph
		int mapRows, mapColumns;
		inFile >> mapRows >> mapColumns;
		//Read output buffer size
		inFile >> outbufferSize;
		//Create out buffer.
		outBuffer = new int[outbufferSize];

		char* map = new char[mapRows * mapColumns];

		//Read map/grid
		int iterator = 0;
		//We call ignore here to move the pointer the next line where the map starts. 
		inFile.ignore();
		//Read each line and add it to the map.
		while (!inFile.eof())
		{
			char* line = new char[mapColumns];
			inFile.getline(line, mapColumns + 1); // We add +1 to mapColumns to include the \n delimiter.

			for (int i = 0; i < mapColumns; i++)
			{
				map[iterator] = line[i];
				iterator++;
			}
		}

		result = FindPath(startX, startY, targetX, targetY, map, mapRows, mapColumns, outBuffer, outbufferSize);
		
	}
	catch (std::ifstream::failure e)
	{
		std::cerr << "Exception opening/reading/closing file\n";
	}

	std::cout << result << std::endl;
	//print out result if we find a path
	if (result != -1)
	{
		if (result > outbufferSize)
			for (int i = 0; i < outbufferSize; i++)
				std::cout << outBuffer[i] << " ";
		else
			for (int i = 0; i < result; i++)
				std::cout << outBuffer[i] << " ";
	}

	system("pause");

	return 0;
}


int FindPath(const int startX, const int startY, const int targetX, const int targetY, const char* map, const int mapRows, const int mapColumns, int* outBuffer, const int outBufferSize)
{
	unsigned int mapIterator = 0;
	unsigned int nodeIndex = 0;

	//Create graph
	Graph graph(mapRows, mapColumns, outBufferSize);
	for (int i = 0; i < mapColumns; i++)
	{
		mapIterator = i;
		for (int j = 0; j < mapRows; j++)
		{
			bool passable = false;
			if (map[mapIterator] == '1')
				passable = true;

			graph.AddNode(nodeIndex, Position(j, i), passable);
			//The map is read and stored row by row but we create the graph column by column
			//which is why we iterate with mapColumns. 
			//The reason we do this is because the FindShortestPath() relies on the indexes of the nodes to be built up this way. Row-major
			mapIterator += mapColumns;
			nodeIndex++;
		}
	}
	//Try to find a path
	int targetNodeIndex = graph.FindShortestPath(Position(startX, startY), Position(targetX, targetY));
	//If no path was found return
	if (targetNodeIndex == -1)
		return -1;

	//If a path was found build it and store it in the outbuffer
	graph.ConstructPath(graph.GetNode(targetNodeIndex), outBuffer, outBufferSize);

	//Return the number of steps taken to reach the target.
	return graph.GetNode(targetNodeIndex).GetSteps();
}