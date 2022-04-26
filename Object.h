#pragma once
#include "Game.h"


class Object{
	
	//object's position on screen
	int x_pos;
	int y_pos;
	//object's texture
	SDL_Texture* texture;
	//object's source and destination rectangles
	SDL_Rect src_rect, dest_rect;

public:
	//create object with a texture
	Object(const char* texuresheet, int x, int y);
	~Object();
	//upadate object's position 
	void Update();
	//display the object
	void Render();
};