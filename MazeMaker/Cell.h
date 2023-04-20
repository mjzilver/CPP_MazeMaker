#pragma once

class Cell
{
public:
	Cell();
	// Debug variabel om te laten zien in de console
	char cellType;

	bool hasAllWalls();

	// x en y coördinaten
	int x, y;

	// muren van de cell
	struct strWalls
	{
		bool north;
		bool west;
		bool east;
		bool south;	
	};
	// toekennen aan de cell
	strWalls walls;

	void setCell(int newX, int newY);
};

