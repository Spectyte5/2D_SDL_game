#include "Object.h"
#include "Texture_manager.h"

//constructor for creating an game object
Object::Object(const char* texuresheet, int x, int y) {

	//use texturemanager method to load the texture
	texture= TextureManager::load_texture(texuresheet);

	//assign start position
	x_pos = x;
	y_pos = y;
}

void Object::Update() {

	//for now just increase both x and y position, which results in objects moving diagonally 
	x_pos++;
	y_pos++;

	//source rectangle values initialization (size and placement of the object texture you want to take)
	src_rect.x = 0;
	src_rect.y = 0;
	src_rect.h = 32;
	src_rect.w = 32;

	//destination rectangle (size and position where destination rectangle will be put on screen) 
	dest_rect.x = x_pos;
	dest_rect.y = y_pos;
	dest_rect.h = 2 * src_rect.h;
	dest_rect.w = 2 * src_rect.w;
}

void Object::Render() {

	//Copy a selected portion of the texture (Source rect) to the current rendering target (Destination rect)
	//SDL_RenderCopy(renderer, texture, part of texture drawn, where you want to draw it on screen);
	SDL_RenderCopy(Game::renderer, texture, &src_rect, &dest_rect);
}