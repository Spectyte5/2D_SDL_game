#include "Map.h"
#include "Texture_manager.h"


//level 1 map array, when we put 0 is grass, 1 is dirt, 2 is water, 3 is rock
int lvl_1[20][25] = {
{ 0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,3,3,0 },
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,3,3,0 },
{ 2,2,2,2,2,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,3,3,3 },
{ 2,2,2,2,2,2,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,3,3 },
{ 2,2,2,2,2,2,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,3,3 },
{ 2,2,2,2,2,2,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,3,3 },
{ 2,2,2,2,2,2,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,3,3 },
{ 2,2,2,2,2,2,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,3,3 },
{ 2,2,2,2,2,2,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,3,3 },
{ 2,2,2,2,2,2,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,3,3 },
{ 2,2,2,2,2,2,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,3,3 },
{ 2,2,2,2,2,2,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,3,3 },
{ 2,2,2,2,2,2,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,3,3 },
{ 2,2,2,2,2,2,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,3,3 },
{ 2,2,2,2,2,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,3,3 },
{ 0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,3,3,0 },
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,3,3,0 },
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,3,3,0 },
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,3,3,0 },
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,3,3,0 }
};

Map::Map(){

	//load map textures
	grass = TextureManager::load_texture("assets/grass.png");
	dirt = TextureManager::load_texture("assets/dirt.png");
	water = TextureManager::load_texture("assets/water2.png");
	rock = TextureManager::load_texture("assets/rock2.png");

	loadMap(lvl_1);
}

Map::~Map() {}

//load our map array
void Map::loadMap(int array_m[20][25]) {

	//multidiamensional array assigning values:
	for (int row = 0; row < 20; row++) {

		for (int col = 0; col < 25; col++) {

			map[row][col]=array_m[row][col];
		}
	}

	//assing map position and size of our source and destination rectangles
	source_r.x = source_r.y = 0;
	source_r.h = source_r.w = 32;
	dest_r.x = dest_r.y = 0;
	dest_r.h = dest_r.w = 32;
}

void Map::drawMap() {

	int type = 0;
	for (int row = 0; row < 20; row++) {

		for (int col = 0; col < 25; col++) {

			type = map[row][col];

			//destination assigning, when row and col 0, we start drawing in the top left
			//1 in each of them means moving 32 pixels in corresponding direction
			dest_r.x = col * 32;
			dest_r.y = row * 32;

			//switch texture type
			switch (type) {
			case 0:
				TextureManager::Draw(grass, source_r, dest_r);
				break;
			case 1:
				TextureManager::Draw(dirt, source_r, dest_r);
				break;
			case 2:
				TextureManager::Draw(water, source_r, dest_r);
				break;
			case 3:
				TextureManager::Draw(rock, source_r, dest_r);
				break;
			default:
				break;
			}
		}
	}
}
