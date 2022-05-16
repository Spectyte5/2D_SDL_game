#include "Map.h"
#include "Game.h"
#include <fstream>


Map::Map(){

}

Map::~Map() {

}

//load our map from external file
void Map::loadMap(std::string path, int sizeX, int sizeY) {

	char tile;
	std::fstream mapfile;
	//open file
	mapfile.open(path);

	//loop through all tile positions
	for (int y = 0; y < sizeY; y++) {

		for (int x = 0; x < sizeX; x++) {

			//get character from external file
			mapfile.get(tile);

			//call method adding a tile to draw
			Game::addTile(atoi(&tile),x * 32,y * 32);

			//ignore the ',' character between elements:
			mapfile.ignore();
		}
	}

	//close file
	mapfile.close();
}
