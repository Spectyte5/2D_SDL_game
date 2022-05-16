#pragma once
#include "Game.h"
#include <string>;

class Map {

public: 

	//Create and destroy map
	Map();
	~Map();

	//Load map to renderer
	static void loadMap(std::string path, int sizeX, int sizeY);

};