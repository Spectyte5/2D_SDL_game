#pragma once
#include "Game.h"

class Map {

	//rectangles for displaying in the right place
	SDL_Rect dest_r, source_r;
	//textures for the map
	SDL_Texture* grass;
	SDL_Texture* dirt;
	SDL_Texture* water;
	SDL_Texture* rock;
	//map array
	int map[20][25];

public: 

	//Create and destroy map
	Map();
	~Map();

	//Load map to renderer
	void loadMap(int array_m [20][25]);
	//display Map
	void drawMap();
};