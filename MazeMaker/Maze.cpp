#include "Maze.h"

#include <windows.h>
#include <iostream>
#include <time.h>
#include <vector>
#include <stack>

Maze::Maze() :
width(10), height(10), cellSize(20), screenBorder(50)
{
}

Maze::Maze(int width, int height, int cellSize, int screenBorder) : 
width(width), height(height), cellSize(cellSize), screenBorder(screenBorder)
{
}

void Maze::ShowMaze(Output &output){
	for(int x = 0; x < width; x++)
	{
		for(int y = 0; y < height; y++)
		{
			drawCell(x, y, output);
		}
	}

	if(stairX >= 0 && stairY >= 0)
	{
		//output.drawStair(stairX, stairY, screenBorder, cellSize);
	}
}

void Maze::drawCell(int x, int y, Output &output)
{
	// To-do: make into a switch with enums or something
	if(cells[x][y].walls.north == true)
	{
		output.drawWall(screenBorder + (x * cellSize), (y * cellSize) + (screenBorder + cellSize), "north", cellSize);
	}
	if(cells[x][y].walls.south == true)
	{
		output.drawWall(screenBorder + (x * cellSize), (y * cellSize) + (screenBorder + cellSize), "south", cellSize);
	}
	if(cells[x][y].walls.east == true)
	{
		output.drawWall(screenBorder + (x * cellSize), (y * cellSize) + (screenBorder + cellSize), "east", cellSize);
	}
	if(cells[x][y].walls.west == true)
	{
		output.drawWall(screenBorder + (x * cellSize), (y * cellSize) + (screenBorder + cellSize), "west", cellSize);
	}
}

void Maze::GenerateMaze()
{
	//  Initialiseer de cellen
	for(int x = 0; x < width; x++)
	{
		for(int y = 0; y < height; y++)
		{
			// zet de X en de Y in cells zelf
			cells[x][y].setCell(x,y);
		}
	}

	//creat a cellStack to hold a list of cell locations
	std::stack<Cell*> cellStack;

	// set totalCells = nume rof cells in grid
	int totalCells =  height * width;

	stairX = globals.randomgen(0,width-1);
	stairY = globals.randomgen(0,height-1);

	// choose a cell at random and call it currentCell
	int currentX = globals.randomgen(0,width-1);
	int currentY = globals.randomgen(0,height-1);

	Cell *currentCell = &cells[currentX][currentY];

	// maak map<enum, Cell*> hiervan
	std::vector<Cell*> intactNeighboursVector;

	// set visitedCells = 1 (the one being the first randomly picked cell)
	int visitedCells = 1;
	while (visitedCells < totalCells)
	{
		currentCell->cellType = 'X';
		currentX = currentCell->x;
		currentY = currentCell->y;

		intactNeighboursVector.clear();

		// find all neighbours of the current cell with all walls intact
		// NORTH
		if(cells[currentX][currentY-1].hasAllWalls() && currentY != 0)
		{
			intactNeighboursVector.push_back(&cells[currentX][currentY-1]);
		}
		// WEST
		if(cells[currentX+1][currentY].hasAllWalls() && currentX != width-1)
		{
			intactNeighboursVector.push_back(&cells[currentX+1][currentY]);
		}
		// SOUTH
		if(cells[currentX][currentY+1].hasAllWalls() && currentY != height-1)
		{
			intactNeighboursVector.push_back(&cells[currentX][currentY+1]);
		}
		// EAST
		if(cells[currentX-1][currentY].hasAllWalls() && currentCell->x != 0)
		{
			intactNeighboursVector.push_back(&cells[currentX-1][currentY]);
		}

		// if one or more is found
		if(intactNeighboursVector.size() != 0)
		{
			// choose one at random
			int randomIndex = rand() % intactNeighboursVector.size(); 

			intactNeighboursVector[randomIndex]->cellType = '$';

			//knock down the walls between this cell and currentCell
			// the new cell is north of the current cell
			if(&cells[currentX][currentY-1] == intactNeighboursVector[randomIndex])
			{
				currentCell->walls.north = false;
				intactNeighboursVector[randomIndex]->walls.south = false;
			}
			// the new cell is west of the current cell
			if(&cells[currentX+1][currentY] == intactNeighboursVector[randomIndex])
			{
				currentCell->walls.west = false;
				intactNeighboursVector[randomIndex]->walls.east = false;
			}
			// the new cell is south of the current cell
			if(&cells[currentX][currentY+1] == intactNeighboursVector[randomIndex])
			{
				currentCell->walls.south = false;
				intactNeighboursVector[randomIndex]->walls.north = false;
			}
			// the new cell is east of the current cell
			if(&cells[currentX-1][currentY] == intactNeighboursVector[randomIndex])
			{
				currentCell->walls.east = false;
				intactNeighboursVector[randomIndex]->walls.west = false;
			}

			//push currentcell location to the cellStack
			cellStack.push(currentCell);

			//make the new cell currentCell
			currentCell = intactNeighboursVector[randomIndex];

			if(currentCell->x == width-1 && currentCell->y == height-1) {
				currentCell->walls.south = false;
			}

			// add 1 to visitedCells;
			visitedCells++;
		}
		// if none is found
		else
		{
			if (!cellStack.empty())
			{
				//make it currentCell
				currentCell = cellStack.top();
				//pop the most recent cell entry of the cellstack
				cellStack.pop();
			}
		}
	}
}
