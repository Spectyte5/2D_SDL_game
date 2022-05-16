#include <iostream>
#include <SDL.h>
#include "Game.h"
#include "Texture_manager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "vector_2D.h"
#include "Collisition.h"

//event appears
SDL_Event Game::event;

//Create a map objects
Map* map;

//create components manager
Manager manager;

//create player
auto& player(manager.addEntity());

//create wall 
auto& wall(manager.addEntity());

//colliders vector
std::vector <Collider_component*> Game::colliders;

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
			window = SDL_CreateWindow("RAV2022", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, flags);

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
			map = new Map();

			//load .map file
			Map::loadMap("assets/maps/test.map",16,16);

			//Entity & Component system implementaion:
			player.addComponent<TransformComponent>(2);
			player.addComponent<SpriteComponent>("assets/max.png");
			player.addComponent<Collider_component>("player");
			player.addComponent<Controller>();

			//create a wall
			wall.addComponent<TransformComponent>(300.0f, 300.0f, 300, 20, 1);
			wall.addComponent<SpriteComponent>("assets/wall.png");
			wall.addComponent<Collider_component>("wall");
		}

		// if Sth went wrong quit game
		else {
			isRunning = false;
		}

	}

	void Game::handle_events() {
		
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
		manager.Refresh();
		manager.Update();

		//check collisitions
		for (auto c : colliders) {

			Collistion::AABB(player.getComponent<Collider_component>(), *c);
		}
	}

	void Game::render() {
	
		SDL_RenderClear(renderer);

		manager.Draw();
		//This where we would add stuff to render
		SDL_RenderPresent(renderer);

	}
	void Game::clean() {

		//destroy window and renderer.
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);

		std::cout << "Game Cleaned!" << std::endl;
	}

	//add tiles
	void Game::addTile(int ID, int x, int y) {

		auto& mtile(manager.addEntity());
		mtile.addComponent<Tile_component>(x,y, 32, 32, ID);
	}

	//get running value of true or false
	bool Game::running() { return isRunning; }
