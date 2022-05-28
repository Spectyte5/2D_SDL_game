#include "Game.h"
#include "Texture_manager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "vector_2D.h"
#include "Collisition.h"
#include <sstream>
#include "Asset_Manager.h"
#include <sstream>

//event appears
SDL_Event Game::event;

//Create a map objects
Map* map;

//create components and assets managers
Manager manager;

//Create asset manager object
Asset_Manager* Game::assets = new Asset_Manager(&manager);

//create camera, Rect(x,y,h,w)
SDL_Rect Game::camera = { 0, 0, 1024, 1024};

//static is the game running declared to false, used for quitting the game with esc button
bool Game::isRunning = false;

//create player
auto& player(manager.addEntity());
//create label
auto& label(manager.addEntity());

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

			if (TTF_Init() == -1) {
				std::cout << "TTF_Init failed..." << std::endl;
			}

			//Use asset manager class to add textures
			assets->Add_Texture("terrain", "assets/maps/map_1.png");
			assets->Add_Texture("player", "assets/max_anim.png");
			assets->Add_Texture("projectile", "assets/proj_1.png");
			assets->Add_Font("arial", "assets/arial.ttf", 16);

			//Initialize Game object with Textures
			map = new Map("terrain", 2, 32);

			//load .map file
			map->loadMap("assets/maps/map_1.map",32,32);

			//Entity & Component system implementaion:
			player.addComponent<TransformComponent>(4);
			player.addComponent<SpriteComponent>("player", true);
			player.addComponent<Collider_component>("player");
			player.addComponent<Controller>();

			//create color for the font
			SDL_Colour white = { 255,255,255,255 };
			//add label component
			label.addComponent<UIlabel>(10,10, "", "arial", white);

			//add player to group;
			player.addGroup(groupPlayers);

			//create projectiles
			assets->Create_Projectile(Vector2D(300, 400), Vector2D(3, 0), 300, 3, "projectile");
			assets->Create_Projectile(Vector2D(320, 300), Vector2D(3, 0), 300, 3, "projectile");
			assets->Create_Projectile(Vector2D(340, 200), Vector2D(3, 0), 300, 3, "projectile");
			assets->Create_Projectile(Vector2D(330, 700), Vector2D(3, 0), 300, 3, "projectile");
			assets->Create_Projectile(Vector2D(330, 100), Vector2D(3, 0), 300, 3, "projectile");

		}

		// if Sth went wrong quit game
		else {
			isRunning = false;
		}

	}

	//get the groups
	auto& tiles(manager.getGroup(Game::groupMap));
	auto& players(manager.getGroup(Game::groupPlayers));
	auto& colliders(manager.getGroup(Game::groupColliders));
	auto& projectiles(manager.getGroup(Game::groupProjectiles));

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

		//get player's collider component
		SDL_Rect player_col = player.getComponent<Collider_component>().collider;
		Vector2D player_pos = player.getComponent<TransformComponent>().position;

		//string steam allows us to update text every frame
		std::stringstream ss;
		//input what you want to display
		ss << "Playerpos: " << player_pos;
		//update text to display
		label.getComponent<UIlabel>().Set_labelText(ss.str(), "arial");

		//update position of the game objects
		manager.Refresh();
		manager.Update();

		//check collistions
		for (auto c : colliders) {

			SDL_Rect c_Col = c->getComponent<Collider_component>().collider;
			
			if (Collistion::AABB(c_Col, player_col)) {
				
				//move player to previously stored position
				player.getComponent<TransformComponent>().position = player_pos;
			}
		}

		//check projectile collistions
		for (auto& p : projectiles) {
			
			if (Collistion::AABB(player.getComponent<Collider_component>().collider, p->getComponent<Collider_component>().collider)) {

				std::cout << "Hit the player" << std::endl;
				p->Destroy();
			}
		}

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
	}

	void Game::render() {
	
		SDL_RenderClear(renderer);
		
		//draw objects in groups:
		for (auto& t : tiles) {
			t->Draw();
		}
		
		/*
		draw colliders as yellow rectangles, used for checking if they render:
		
		for (auto& c : colliders) {
			c->Draw();
		}
		*/

		for (auto& p : players) {
			p->Draw();
		}

		for (auto& p : projectiles) {
			p->Draw();
		}

		//draw text on screen
		label.Draw();

		//This where we would add stuff to render
		SDL_RenderPresent(renderer);

	}
	void Game::clean() {

		//destroy window and renderer.
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);

		std::cout << "Game Cleaned!" << std::endl;
	}

	//get running value of true or false
	bool Game::running() { return isRunning; }
