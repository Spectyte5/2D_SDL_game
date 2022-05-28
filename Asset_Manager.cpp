#pragma once
#include "Asset_manager.h"
#include "ECS/Components.h"


Asset_Manager::Asset_Manager(Manager* man) {

	manager = man;
}

Asset_Manager::~Asset_Manager() {

}


void Asset_Manager::Add_Texture(std::string id, const char* path) {

	//put texture in the map
	textures.emplace(id, TextureManager::load_texture(path));
}

SDL_Texture* Asset_Manager::Get_Texture(std::string id) {

	//get texture from id
	return textures[id];
}

void Asset_Manager::Create_Projectile(Vector2D pos, Vector2D vel, int range, int speed, std::string id){
//create projectile
auto& projectile(manager->addEntity());
//add components
projectile.addComponent<TransformComponent>(pos.x, pos.y, 32, 32, 1);
projectile.addComponent<SpriteComponent>(id, false);
projectile.addComponent<Projectile_Component>(range, speed, vel);
projectile.addComponent<Collider_component>("projectile");
//add to the group
projectile.addGroup(Game::groupProjectiles);
}


void Asset_Manager::Add_Font(std::string id, std::string path, int fontsize) {

	//put font ttf file from path to the map with id key
	fonts.emplace(id, TTF_OpenFont(path.c_str(), fontsize));
}

TTF_Font* Asset_Manager::Get_Font(std::string id) {

	//return map element with given key
	return fonts[id];
}