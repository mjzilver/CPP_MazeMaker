#include "cell.h"

Cell::Cell()
{
	walls.north = true;
	walls.west = true;
	walls.east = true;
	walls.south = true;

	cellType = '#';
}

bool Cell::hasAllWalls()
{
	// als alle muren bestaan (true zijn) hasAllWalls = true
	if(walls.north == true
		&& walls.west == true
		&& walls.east == true
		&& walls.south == true)
	{
		return true;
	}
	// anders hasAllWalls = false
	else
	{
		return false;
	}
}

void Cell::setCell(int newX, int newY)
{
	x = newX;
	y = newY;
	
	walls.north = true;
	walls.west = true;
	walls.east = true;
	walls.south = true;

	cellType = '#';
}
