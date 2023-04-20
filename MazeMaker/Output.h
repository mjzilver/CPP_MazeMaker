#pragma once

#include <string>

struct SDL_Window;
struct SDL_Renderer;

class Output
{
public:
	Output(int screenWidth, int screenHeight);
	/* void drawWall
	* Draws the wall of a cell (cell is made in maze)
	*/
	void drawWall(int x, int y, std::string wall, int cellSize);

	void drawCircle(int x, int y, int screenBorder, int cellSize);

	void drawStair(int x, int y, int screenBorder, int cellSize);

	void drawText(int x, int y, int fontSize, char* text);

	void drawPixel(int x, int y);

	/* void render
	 * Renders everything to the screen
	 */
	void render();

	/* void clear
	 * Clears the screen
	 */
	void clear();
private:
	SDL_Window* _window;
	SDL_Renderer* _renderer;
};

