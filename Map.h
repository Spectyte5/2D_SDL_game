#pragma once
#include "Game.h"

class Map {

	std::string textureid;
	int mapscale;
	int tilesize;
	int scaledsize;
	const char* mapfile = "assets/maps/map_1.png";

public: 

	//Create and destroy map
	Map(std::string tile_id, int mapscale, int tilesize);
	~Map();

	//Load map to renderer
	void loadMap(std::string path, int sizeX, int sizeY);
	//add tile map
	void addTile(int Srcx, int Srcy, int xpos, int ypos);
};