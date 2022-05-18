#pragma once

//struct for different animations
struct Animation {

	int index;
	int speed;
	int frames;

	//default constructor
	Animation() {

	}
	//constructor with member values
	Animation(int i, int f, int s) {
		
		index = i;
		speed = s;
		frames = f;
	}

};