#pragma once

#include "Maze.h"
#include "Output.h"

class Player
{
public:
	Player();
	Player(int x, int y, int mazeCellSize, int screenBorder);

	// movement in the maze
	void moveDown(Maze &doolfhof);
	void moveUp(Maze &doolfhof);
	void moveRight(Maze &doolfhof);
	void moveLeft(Maze &doolfhof);

	void draw(Output &output);
	// placement variables
	int x, y, mazeCellSize, radius, screenBorder;
};

