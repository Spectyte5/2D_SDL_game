#include "Map.h"
#include <fstream>
#include "ECS/Entity_component_sys.h"
#include "ECS/Components.h"

//object defined somewhere else
extern Manager manager;

Map::Map(std::string tile_id, int ms, int ts){

	//set variables
	textureid=tile_id;
	mapscale=ms;
	tilesize=ts;
	scaledsize = ms * ts;
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

	//loop through all tile positions to get the map
	for (int y = 0; y < sizeY; y++) {

		for (int x = 0; x < sizeX; x++) {

			//get char from external file
			mapfile.get(c);

			//get X and Y values:
			SrcY = atoi(&c) * tilesize;
			mapfile.get(c);
			SrcX = atoi(&c) * tilesize;

			//call method adding a tile to draw
			addTile(SrcX,SrcY,x * scaledsize, y * scaledsize);

			//ignore the ',' char between elements:
			mapfile.ignore();
		}
	}

	//ignore the empty line after first part of map loading
	mapfile.ignore();

	//loop through all tile positions to get the map collisitions
	for (int y = 0; y < sizeY; y++) {

		for (int x = 0; x < sizeX; x++) {

			//get char from external file
			mapfile.get(c);
				
			//check if tile has collistion: 
			if (c == '1') {

				//create collider
				auto& tcol(manager.addEntity());
				tcol.addComponent<Collider_component>("terrain", x * scaledsize, y * scaledsize, scaledsize);
				tcol.addGroup(Game::groupColliders);
			}
			//ignore the ',' char between elements:
			mapfile.ignore();
		}
	}

	//close file
	mapfile.close();
}

//add tiles
void Map::addTile(int Srcx, int Srcy, int xpos, int ypos) {

	auto& mtile(manager.addEntity());
	mtile.addComponent<Tile_component>(Srcx, Srcy, xpos, ypos, textureid, tilesize, mapscale);
	//add tiles to group
	mtile.addGroup(Game::groupMap);
}
