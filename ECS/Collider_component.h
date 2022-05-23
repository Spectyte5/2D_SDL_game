#pragma once
#include <SDL.h>
#include <string>
#include "Components.h"
#include "../Texture_manager.h"

//colider component
class Collider_component : public Component{

public:
	//collidable area: 
	SDL_Rect collider;
	//collisition tag for information what hit what:
	std::string tag;

	//collider texture
	SDL_Texture* texture;
	SDL_Rect src_rect, dest_rect;

	TransformComponent* transform;

	//constructor taking the tag:
	Collider_component(std::string t) {

		tag = t;
	}

	//costructor for map
	Collider_component(std::string t, int xpos, int ypos, int size) {

		tag = t;
		collider.x = xpos;
		collider.y = ypos;
		collider.h = collider.w = size;
	}

	void Init() override {

		//check if entity has a TransformComponent
		if (!entity->hasComponnent<TransformComponent>()) {
			
			//if not then add it:
			entity->addComponent<TransformComponent>();
		}
		//get the component and create a pointer to it in our class Colider:
		transform = &entity->getComponent<TransformComponent>();

		//load texture
		texture = TextureManager::load_texture("assets/collision.png");
		//rectangles for texture
		src_rect = { 0,0,32,32};
		dest_rect = {collider.x, collider.y, collider.w, collider.h};
	}

	void Update() override {
	
		if (tag != "terrain") {
			//update position of our collider so that top left is on the origin of the object:
			collider.x = static_cast<int>(transform->position.x);
			collider.y = static_cast<int>(transform->position.y);
			//update size of our collider
			collider.h = transform->height * transform->scale;
			collider.w = transform->width * transform->scale;
		}
			//update colliders position:
			dest_rect.x = collider.x - Game::camera.x;
			dest_rect.y = collider.y - Game::camera.y;
		
	}

	void Draw() override {
		
		//use texture manager class to draw texture on screen
		TextureManager::Draw(texture, src_rect, dest_rect, SDL_FLIP_NONE);
	}

};