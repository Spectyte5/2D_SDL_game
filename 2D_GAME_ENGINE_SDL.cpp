#include <iostream>
#include <SDL.h>
#include "Game.h"

Game* game = NULL;

int main(int argc, char* argv[]) { //these paramaters are neccessary co that SDL main is not confused with this main.

	const int FPS = 60;
	const int frameDelay = 1000/FPS;   //delay 1s / FPS
	Uint32 frameStart;                 //start of the frame
	int frameTime;                 //time between frames

	game = new Game();
	game->init("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 1024, false);

	while (game->running()) {
		//handle user input 
		frameStart = SDL_GetTicks();

		game->handle_events();
		//update all the objects (for example positions)
		game->update();
		//render changes to the display
		game->render();
		
		frameTime = SDL_GetTicks() - frameStart;
		
		//assign delay
		if (frameDelay > frameTime) {
			
			SDL_Delay(frameDelay - frameTime);
		}
	}
	//destroy window and rednerer
	game->clean();

	return 0;

}

