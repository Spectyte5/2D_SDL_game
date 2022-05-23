#pragma once

#include <map>
#include <string>
#include "Texture_manager.h"
#include "vector_2D.h"
#include "ECS/Entity_component_sys.h"


class Asset_Manager {

	//map holding textures with a string key
	std::map <std::string, SDL_Texture*> textures;
	//manager object for constructor
	Manager* manager;
public:

	Asset_Manager(Manager* man);
	~Asset_Manager();

	//add our textures
	void Add_Texture(std::string id, const char* path);
	//get texture from the map
	SDL_Texture* Get_Texture(std::string id);
};