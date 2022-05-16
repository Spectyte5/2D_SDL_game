#pragma once
#include "Components.h"
#include "..\vector_2D.h"

class TransformComponent : public Component {

public:

	//position and velocity values
	Vector2D position;
	Vector2D velocity;

	//character speed
	int speed = 3;

	//area for colitions
	int height = 32;
	int width = 32;
	int scale = 1;

	//default position of (0,0)
	TransformComponent() {

		position.Zero();

	}

	//Constructor with given positon
	TransformComponent(float x, float y) {
		
		position.x = x;
		position.y = y; 

	}

	//default postion, custom scale constructor:
	TransformComponent(int s) {

		position.Zero();
		scale = s;
	}

	//Constructor with both size and position:
	TransformComponent(float x, float y, int h, int w, int s) {

		position.x = x;
		position.y = y;
		width = w;
		height = h;
		scale = s;
	}

	void Init() override {

		velocity.Zero();
	}

	void Update() override {

		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}
};