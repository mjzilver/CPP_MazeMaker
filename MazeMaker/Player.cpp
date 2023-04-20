#include "Player.h"

#include <SDL.h>
#undef main

#include <iostream>

Player::Player()
{
	x = 0;
	y = 0;
	mazeCellSize = 20;
	radius = 10;
	screenBorder = 50;
}

//screenBorder + (playerRadius/2)

Player::Player(int x, int y, int mazeCellSize, int screenBorder) :
	x(x), y(y), mazeCellSize(mazeCellSize), screenBorder(screenBorder)
{
}

void Player::draw(Output &output)
{
	// plaats de "player" in het doolhof
	output.drawCircle(x, y, screenBorder, mazeCellSize);
}

void Player::moveDown(Maze &doolfhof)
{
	if(doolfhof.cells[x][y].walls.south == false)
	{
		y++;
	}
}

void Player::moveUp(Maze &doolfhof)
{
	if(doolfhof.cells[x][y].walls.north == false)
	{
		y--;
	}
}

void Player::moveLeft(Maze &doolfhof)
{
	if(doolfhof.cells[x][y].walls.east == false)
	{
		x--;
	}
}

void Player::moveRight(Maze &doolfhof)
{
	if(doolfhof.cells[x][y].walls.west == false)
	{
		x++;
	}
}