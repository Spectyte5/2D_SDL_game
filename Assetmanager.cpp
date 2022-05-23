#pragma once
#include "Assetmanager.h"
#include "ECS/Components.h"


Asset_Manager::Asset_Manager(Manager* man){

	manager = man;
}

Asset_Manager::~Asset_Manager(){
}


void Asset_Manager::Add_Texture(std::string id, const char* path) {

	//put texture in the map
	textures.emplace(id,TextureManager::load_texture(path));
}

SDL_Texture* Asset_Manager::Get_Texture(std::string id){
	//get texture from id
	return textures[id];
}
