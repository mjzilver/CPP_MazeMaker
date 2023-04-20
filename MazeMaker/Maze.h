#pragma once

#include "cell.h"
#include "globals.h"
#include "Output.h"

#include <SDL.h>
#undef main

#include <string>
#include <map>

class Maze
{
public:
	// maak het doolhof aan
	Maze();

	Maze(int width, int height, int cellSize, int screenBorder);

	// print het doolhof op het scherm
	void ShowMaze(Output &output);

	// genereer het doolhof
	void GenerateMaze();

	int stairX, stairY;

	int width, height, cellSize, screenBorder;

	//map[x][y] // [width][height]
	std::map< int, std::map<int, Cell>> cells;

private:
	// globale functies (nu alleen willekeurignummergenerator)
	Globals globals;

	// tekent elke cell, waarschijnlijk moet dit naar cell
	void drawCell(int x, int y, Output &output);
};

