#pragma once

#include <map>
#include <string>
#include "Texture_manager.h"
#include "vector_2D.h"
#include "ECS/Entity_component_sys.h"
#include <SDL_ttf.h>

class Asset_Manager {

	//map holding textures with a string key
	std::map <std::string, SDL_Texture*> textures;
	//map fonts textures with a string key
	std::map <std::string, TTF_Font* > fonts;
	//manager object for constructor
	Manager* manager;

public:

	Asset_Manager(Manager* man);
	~Asset_Manager();

	//GAME OBJECTS:
	void Create_Projectile(Vector2D pos, Vector2D vel, int range, int speed, std::string id);

	//TEXTURE MANAGMENT:
	//add our textures
	void Add_Texture(std::string id, const char* path);
	//get texture from the map
	SDL_Texture* Get_Texture(std::string id);
	//add font to the map
	void Add_Font(std::string id, std::string path, int fontsize);
	//get font from the map
	TTF_Font* Get_Font(std::string id);
};

