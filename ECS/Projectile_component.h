#pragma once
#include "Entity_component_sys.h"
#include "Components.h"
#include "../vector_2D.h"

class Projectile_Component : public Component {

	TransformComponent* transform;
	int speed=0;
	int range=0;
	int distance=0;
	Vector2D velocity;
	 
public:

	Projectile_Component(int r, int s, Vector2D vel) {

		speed = s;
		range = r;
		velocity = vel;
	}
	~Projectile_Component(){};

	void Init() override {

		//get transform component for the projectile
		transform = &entity->getComponent<TransformComponent>();
		transform->velocity = velocity;
	}

	void Update() override {

		//update distance flew by the projectile, from the speed
		distance += speed;


		//if projectile reaches it's range, destroy it
		if (distance > range) {

			std::cout << "Out of range" << std::endl;
			entity->Destroy();
		}
		// or if it is outside of the camera
		else if (transform->position.x > Game::camera.x + Game::camera.w 
			|| transform->position.x < Game::camera.x 
			|| transform->position.y > Game::camera.y + Game::camera.h 
			|| transform->position.y < Game::camera.y) {

			std::cout << "Out of bounds" << std::endl;
			entity->Destroy();
		}
	}
};