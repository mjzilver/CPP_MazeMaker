#include <iostream>
#include <algorithm>

#include <SDL.h>
#undef main

#include "game.h"
#include "output.h"
#include "input.h"
#include "globals.h"

namespace{
	const int FPS = 60;
    const int SKIP_TICKS = 1000 / FPS;
}

Game::Game() 
{
	SDL_Init(SDL_INIT_EVERYTHING);

	score = 0;
	mazeWidth = 30;
	mazeHeight = 30;
	mazeCellSize = 15;
	screenBorder = 20;
	playerRadius = mazeCellSize / 2;

	this->gameLoop();
}

void Game::gameLoop()
{
	Output output((screenBorder*2) + (mazeCellSize*mazeWidth), (screenBorder*2) + (mazeCellSize*mazeHeight));
	Input input;
	SDL_Event SDL_event;

	this->_speler = Player(0, 0, mazeCellSize, screenBorder);
	this->_doolhof = Maze(mazeWidth, mazeHeight, mazeCellSize, screenBorder);

	bool game_is_running = true;
	int LAST_UPDATE_TIME = SDL_GetTicks();

	std::cout << "Press Ctrl+G to generate a maze" << std::endl;
	std::cout << "Press Ctrl+E when on the stair to advance" << std::endl;
	std::cout << "Press the arrow keys or the wasd keys to move" << std::endl;

	// start the gameloop
	while(game_is_running)
	{
		// input gedeelte
		input.resetKeys();

		if(SDL_PollEvent(&SDL_event)){
			if(SDL_event.type == SDL_KEYDOWN)
			{
				input.keyDownEvent(SDL_event);
			}
			else if (SDL_event.type == SDL_KEYUP)
			{
				input.keyUpEvent(SDL_event);
			}
			else if(SDL_event.type == SDL_QUIT){
				game_is_running = false;
			}
		}
		if(input.wasKeyPressed(SDL_SCANCODE_ESCAPE) )
		{
			game_is_running = false;
		}
		if(input.isKeyHeld(SDL_SCANCODE_LCTRL) && input.wasKeyReleased(SDL_SCANCODE_G) )
		{
			// G FOR GENERATE
			int startTime = SDL_GetTicks();
			_doolhof.GenerateMaze();
			int endTime = SDL_GetTicks() - startTime;

			std::cout << "Milliseconds it took to generate: " << endTime << std::endl;
		}
		if(input.isKeyHeld(SDL_SCANCODE_LCTRL) && input.wasKeyReleased(SDL_SCANCODE_H) )
		{
			// H FOR HELP
			_speler.x = 0;
			_speler.y = 0;
		}
		if(input.wasKeyReleased(SDL_SCANCODE_DOWN) || input.wasKeyReleased(SDL_SCANCODE_S))
		{
			_speler.moveDown(_doolhof);
		}
		if(input.wasKeyReleased(SDL_SCANCODE_UP) || input.wasKeyReleased(SDL_SCANCODE_W))
		{
			_speler.moveUp(_doolhof);
		}
		if(input.wasKeyReleased(SDL_SCANCODE_RIGHT) || input.wasKeyReleased(SDL_SCANCODE_D))
		{
			_speler.moveRight(_doolhof);
		}
		if(input.wasKeyReleased(SDL_SCANCODE_LEFT) || input.wasKeyReleased(SDL_SCANCODE_A))
		{
			_speler.moveLeft(_doolhof);
		}
		if(_speler.x == _doolhof.stairX && _speler.y == _doolhof.stairY && input.wasKeyPressed(SDL_SCANCODE_E))
		{
			_doolhof.GenerateMaze();
			score++;
			std::cout << "You're on level: " << score << std::endl;
		}

		// berekent nodige informatie voor fps-limiet
		const int CURRENT_TIME = SDL_GetTicks();
		int ELAPSED_TIME = CURRENT_TIME - LAST_UPDATE_TIME;
		LAST_UPDATE_TIME = CURRENT_TIME;
		int TIME_TO_SLEEP = (1000 / FPS) - ELAPSED_TIME;

		this->draw(output);

		// zorgt voor een delay zodat het programma niet vaker als 60fps tekent
		if( TIME_TO_SLEEP >= 0 ) {
			SDL_Delay(TIME_TO_SLEEP);
        }
	}
}

void Game::draw(Output &output)
{
	output.clear();

	_doolhof.ShowMaze(output);
	
	_speler.draw(output);

	output.render();
}

void Game::update(float elpasedTime)
{
}