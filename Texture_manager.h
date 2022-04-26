#pragma once
#include "Game.h"

//class used for easier loading of game objects textures and map.
class TextureManager {

public:
	static SDL_Texture* load_texture(const char* texturefile);
	static void Draw(SDL_Texture* tex, SDL_Rect src_rect, SDL_Rect dest_rect);
};