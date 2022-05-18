#include "Map.h"
#include "Game.h"
#include <fstream>


Map::Map(){

}

Map::~Map() {

}

//load our map from external file
void Map::loadMap(std::string path, int sizeX, int sizeY) {

	char c;
	std::fstream mapfile;
	//open file
	mapfile.open(path);

	//character from the file cordinates
	int SrcX, SrcY;

	//loop through all tile positions
	for (int y = 0; y < sizeY; y++) {

		for (int x = 0; x < sizeX; x++) {

			//get char from external file
			mapfile.get(c);

			//get X and Y values:
			SrcY = atoi(&c) * 32;
			mapfile.get(c);
			SrcX = atoi(&c) * 32;

			//call method adding a tile to draw
			Game::addTile(SrcX,SrcY,x * 64,y * 64);

			//ignore the ',' char between elements:
			mapfile.ignore();
		}
	}

	//close file
	mapfile.close();
}
