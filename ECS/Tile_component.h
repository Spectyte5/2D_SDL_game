#pragma once
#include "Entity_component_sys.h"
#include <SDL.h>
#include "TransformComponent.h"
#include "SpriteComponent.h"


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


	Tile_component(int srcX, int srcY, int xpos, int ypos, const char * path) {

		//load pixeledit tileset
		texture = TextureManager::load_texture(path);
		
		//position and source values 
		position.x = xpos;
		position.y = ypos;

		srcRect.x = srcX;
		srcRect.y = srcY;
		srcRect.w = srcRect.h = 32;

		//increase tile size two times:
		destRect.x = xpos;
		destRect.y = ypos;
		destRect.w = destRect.h = 64;
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