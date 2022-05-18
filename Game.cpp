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

//create camera, Rect(x,y,h,w)
SDL_Rect Game::camera = { 0, 0, 1024, 1024};

//static is the game running declared to false, used for quitting the game with esc button
bool Game::isRunning = false;

//create player
auto& player(manager.addEntity());

//path for map
const char* mapfile = "assets/maps/map_1.png";

//create Group
enum groupLabels : std::size_t {

	groupMap,
	groupPlayers,
	groupColliders,
	groupEnemies
};

//get the groups
auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));
auto& colliders(manager.getGroup(groupColliders));
auto& enemies(manager.getGroup(groupEnemies));

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
			
			//Create a Centered Window size: 1024x1024 
			window = SDL_CreateWindow("RAV2022", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 1024, flags);

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
			Map::loadMap("assets/maps/map_1.map",32,32);

			//Entity & Component system implementaion:
			player.addComponent<TransformComponent>(3);
			player.addComponent<SpriteComponent>("assets/rav_anim2.png", true);
			player.addComponent<Collider_component>("player");
			player.addComponent<Controller>();

			//add player to group;
			player.addGroup(groupPlayers);
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


		//keep player in the middle of the screen
		camera.x = player.getComponent<TransformComponent>().position.x - 612;
		camera.y = player.getComponent<TransformComponent>().position.y - 612;

		//keep camera in bound
		if (camera.x < 0) {
		
			camera.x = 0;
		}
		if (camera.y < 0) {

			camera.y = 0;
		}
		if (camera.x > camera.w) {

			camera.x = camera.w;
		}
		if (camera.y > camera.h) {

			camera.y = camera.h;
		}

		//check collisitions
		for (auto c : colliders) {

			Collistion::AABB(player.getComponent<Collider_component>(), *c);
		}

	}

	void Game::render() {
	
		SDL_RenderClear(renderer);
		
		//draw onjects in groups:
		for (auto& t : tiles) {
			t->Draw();
		}
		
		for (auto& p : players) {
			p->Draw();
		}

		for (auto& e :	enemies) {
			e->Draw();
		}

		for (auto& c : colliders) {
			c->Draw();
		}

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
	void Game::addTile(int Srcx, int Srcy, int xpos, int ypos) {

		auto& mtile(manager.addEntity());
		mtile.addComponent<Tile_component>(Srcx, Srcy, xpos, ypos, mapfile);
		//add tiles to group
		mtile.addGroup(groupMap);
	}

	//get running value of true or false
	bool Game::running() { return isRunning; }
