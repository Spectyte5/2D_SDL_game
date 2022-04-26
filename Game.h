#pragma once
#ifndef GAME_H
#define GAME_H
#include <SDL.h>
#include <SDL_image.h>

class Game {

	//game seconds counter for now used to moving character, will be improved later.
	int cnt=0;
	//while loop parameter for game on or off 
	bool isRunning;
	//Window pointer
	SDL_Window* window;

public:
	//constructor and destructor
	Game();
	~Game();

	//SDL and objects initalization
	void init(const char* title, int xpos, int ypos, int height, int width, bool fullscreen);
	
	//Event handling
	void handle_events();
	//Updating objects position
	void update();
	//Rendering objects
	void render();
	//Clean up: destroy SDL objects
	void clean();
	//function for game running
	bool running();
	//static renderer to be used through all files
	static SDL_Renderer* renderer;
};

#endif 