#pragma once
#include <SDL.h>
#include <string>
#include "Components.h"

//colider component
class Collider_component : public Component{

public:
	//collidable area: 
	SDL_Rect collider;
	//collisition tag for information what hit what:
	std::string tag;

	TransformComponent* transform;

	//constructor taking the tag:
	Collider_component(std::string t) {

		tag = t;
	}

	void Init() override {

		//check if entity has a TransformComponent
		if (!entity->hasComponnent<TransformComponent>()) {
			
			//if not then add it:
			entity->addComponent<TransformComponent>();
		}
		//get the component and create a pointer to it in our class Colider:
		transform = &entity->getComponent<TransformComponent>();

		//put this collider inside colliders vector:
		Game::colliders.push_back(this);
	}

	void Update() override {
	
		//update position of our collider so that top left is on the origin of the object:
		collider.x = static_cast<int>(transform->position.x);
		collider.y = static_cast<int>(transform->position.y);
		//update size of our collider
		collider.h = transform->height * transform->scale;
		collider.w = transform->width * transform->scale;
	}

};