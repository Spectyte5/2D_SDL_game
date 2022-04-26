#include <iostream>
#include <SDL.h>
#include "Game.h"
#include "Texture_manager.h"
#include "Object.h"
#include "Map.h"

//create game objects
Object* player;
Object* spider;
Map* map;

//one static renderer used instead of copies
SDL_Renderer* Game::renderer = nullptr;

//constructor and destructor (unused for now)
	Game::Game(){}
	Game::~Game()
	{}

	//initialze SDL and objects
	void Game::init(const char *title, int xpos, int ypos, int height, int width, bool fullscreen) {
		
		//flags are additional information ex. FULL SCREEN:
		int flags = 0;

		if (fullscreen) {
			flags = SDL_WINDOW_FULLSCREEN;
		}

		//Initialize SDL:
		if (SDL_Init(SDL_INIT_EVERYTHING)== 0) {
			std::cout << "Systems initalized!" << std::endl;
			
			//Create a Centered Window size: 800x640 
			window = SDL_CreateWindow("Title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, flags);

			if (window) {
				std::cout << "Window Created!" << std::endl;
			}
			//Create a renderer:
			 renderer = SDL_CreateRenderer(window, -1, 0);

			if (renderer) {
				
				//background color for now white SDL_SetRenderDrawColor(Your renderer, R, G, B, oppacity):
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				std::cout << "Renderer Created!" << std::endl;
			}

			//Game set to started
			isRunning = true;

			//Initialize Game object with Textures
			player = new Object("assets/character3.png",0,0);
			spider = new Object("assets/spider.png", 50,50);
			map = new Map();
		}

		// if Sth went wrong quit game
		else {
			isRunning = false;
		}

	}

	void Game::handle_events() {
		
		//event appears
		SDL_Event event;
		//find event
		SDL_PollEvent(&event);
		//check what type of event:
		switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
		default:
			break;
		}
	}
	void Game::update() {
	
		//update position of the game objects
		player->Update();
		spider->Update();
	}

	void Game::render() {
	
		SDL_RenderClear(renderer);
		//Render a map:
		map->drawMap();
		//SDL_RenderCopy(renderer, texture, part of texture drawn, where you want to draw it on screen);
		player->Render();
		spider->Render();
		//This where we would add stuff to render
		SDL_RenderPresent(renderer);

	}
	void Game::clean() {

		//destroy window and renderer.
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);

		std::cout << "Game Cleaned!" << std::endl;
	}

	//function to get running value of true or false
	bool Game::running() { return isRunning; }
