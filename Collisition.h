#pragma once
#include <SDL.h>

class Collider_component;

class Collistion {

public:
	//static method for detecting colistions using AABB(Axis allined Bounding box):
	static bool AABB(const SDL_Rect &rectA, const SDL_Rect& rectB);
	static bool AABB(const Collider_component& colA, const Collider_component& colB);
};