#pragma once
#include "Components.h"
#include "../vector_2D.h"

class TransformComponent : public Component {

public:

	//position and velocity values
	Vector2D position;
	Vector2D velocity;

	//character speed
	int speed = 4;

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

		//put player in the middle of the screen
		position.x = 612;
		position.y = 612;
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

	//initialize velocity to 0
	void Init() override {

		velocity.Zero();
	}

	//update character position
	void Update() override {

		float x_change = velocity.x * speed;;
		float y_change = velocity.y * speed;

		//normalize velocity on diagonals
		if (x_change && y_change) {
			x_change /= sqrt(2);
			y_change /= sqrt(2);
		}

		position.x += x_change;
		position.y += y_change;
	}
};