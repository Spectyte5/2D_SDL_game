#include "Texture_manager.h"

SDL_Texture* TextureManager::load_texture(const char* texturefile) {

	SDL_Surface* tmpSurface = IMG_Load(texturefile); //load and image as a surface
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface); // create our texture from surface
	SDL_FreeSurface(tmpSurface);     //when done, free the surface

	return tex;
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src_rect, SDL_Rect dest_rect, SDL_RendererFlip sprite_flip) {

	SDL_RenderCopyEx(Game::renderer, tex, &src_rect, &dest_rect, NULL, NULL, sprite_flip);
}