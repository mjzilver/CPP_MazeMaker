#include "Output.h"

#include <SDL.h>
#undef main
#include <SDL_ttf.h>
#include <iostream>

// graphics
//1024 × 768
const int _screenHeight = 768;
const int _screenWidth = 1024;
const int _screenBorder = 50;

Output::Output(int screenWidth, int screenHeight)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_CreateWindowAndRenderer(screenWidth, screenHeight, 0, &this->_window, &this->_renderer);
	SDL_SetWindowTitle(this->_window, "Maze");
	SDL_Event Event;
	
	TTF_Init();
}

void Output::drawWall(int x1, int y1, std::string wall, int cellSize)
{
	// use the white color
	SDL_SetRenderDrawColor(this->_renderer,47,79,79,0);

	int x2 = x1;
	int y2 = y1;

	// To-do: make into a switch with enums or something
	if(wall == "south")
	{
		x2 += cellSize;
	}
	if(wall == "north")
	{
		x2 += cellSize;
		y2 -= cellSize;
		y1 -= cellSize;
	}
	if(wall == "east")
	{
		y2 -= cellSize;
	}
	if(wall == "west")
	{
		y2 -= cellSize;
		x1 += cellSize;
		x2 += cellSize;
	}

	SDL_RenderDrawLine(this->_renderer,x1,y1,x2,y2);
}

void Output::drawCircle(int x, int y, int screenBorder, int cellSize)
{
	// screenBorder = margin vanaf het scherm
	// (radius/2) = om het blokje te centreren
	// (x * mazeCellSize) = om de cell te kiezen waarin het blokje staat

	int radius = ((cellSize/5) * 3) / 2;

	SDL_SetRenderDrawColor(this->_renderer,47,79,79,0);

	SDL_Rect rect;

	rect.x = screenBorder + (cellSize/5) + (x * cellSize);
	rect.y = screenBorder + (cellSize/5) + (y * cellSize);
	rect.h = (cellSize/5) * 3;
	rect.w = (cellSize/5) * 3;

	SDL_RenderFillRect(this->_renderer, &rect);

	//SDL_RenderDrawLine(this->_renderer,x1,y1,x2,y2);
}

void Output::drawStair(int x, int y, int screenBorder, int cellSize)
{
	SDL_SetRenderDrawColor(this->_renderer,47,79,79,0);

	// teken de lijn aan de linkerkant
	int x1 = screenBorder + (x * cellSize) + (cellSize / 5);
	int y1 = screenBorder + (y * cellSize) + (cellSize / 5);
	int x2 = x1;
	int y2 = y1 + ((cellSize / 5) * 3);

	SDL_RenderDrawLine(this->_renderer,x1,y1,x2,y2);

	// Teken de onderste lijn
	x1 = x2;
	y1 = y2;
	x2 += (cellSize / 5) * 3;

	SDL_RenderDrawLine(this->_renderer,x1,y1,x2,y2);

	// drie tredes voor deze trap
	for(int i = 0; i < 3; i++)
	{
		// Vericale stuk van de trede
		x1 = x2;
		y1 = y2;
		y2 -= (cellSize / 5);

		SDL_RenderDrawLine(this->_renderer,x1,y1,x2,y2);

		// Horizontale stuk van de trede
		x1 = x2;
		y1 = y2;
		x2 -= (cellSize / 5);

		SDL_RenderDrawLine(this->_renderer,x1,y1,x2,y2);
	}
}

void Output::drawPixel(int x, int y)
{
	SDL_RenderDrawPoint(this->_renderer, x, y);
}

void Output::render(){
	SDL_RenderPresent(this->_renderer);
}

void Output::clear(){
	///237,229,210 gebroken wit
	SDL_SetRenderDrawColor(this->_renderer,237,229,210,0);
	SDL_RenderClear(this->_renderer);
}