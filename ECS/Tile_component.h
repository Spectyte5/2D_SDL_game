#pragma once
#include "Entity_component_sys.h"
#include <SDL.h>
#include "../vector_2D.h"
#include "../Game.h"
#include "../Texture_manager.h"

class Tile_component : public Component {

public:
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
	//tile position in game:
	Vector2D position;

	Tile_component() = default;

	~Tile_component() {

		//destroy texture when out of scope
		SDL_DestroyTexture(texture);
	}


	Tile_component(int srcX, int srcY, int xpos, int ypos, std::string id, int t_size, int t_scale) {

		//load pixeledit tileset
		texture = Game::assets->Get_Texture(id);
		
		//position and source values 
		position.x = xpos;
		position.y = ypos;

		srcRect.x = srcX;
		srcRect.y = srcY;
		srcRect.w = srcRect.h = t_size;

		//destination values to change size, change scale:
		destRect.x = xpos;
		destRect.y = ypos;
		destRect.w = destRect.h = t_size * t_scale;
	}

	void Update() override {

		//update tile position
		destRect.x = position.x - Game::camera.x;
		destRect.y = position.y - Game::camera.y;
		
	}

	//draw tiles
	void Draw() override {
		TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
	}
};