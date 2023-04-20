#pragma once

#include "Maze.h"
#include "Player.h"

class Output;

class Game
{
public:
	Game(void);
private:
	/* void gameLoop
	 * Initialize the gameLoop
	 */
	void gameLoop();
	/* void draw
	 * Calls the output to draw the game
	 */
	void draw(Output &output);
	/* void update
	 * nog niets
	 */
	void update(float elapsedTime);

	// Settings die nodig zijn om cellen op te bouwen
	int score;
	int mazeWidth, mazeHeight;
	int mazeCellSize;
	int screenBorder;
	int playerRadius;

	Maze _doolhof;
	Player _speler;
};

