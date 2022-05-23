#include "Collisition.h"
#include "ECS/Collider_component.h"

bool Collistion::AABB(const SDL_Rect& rectA, const SDL_Rect& rectB) {

	//check if it is a collistion:
	if (rectA.x + rectA.w >= rectB.x 
		&& rectB.x + rectB.w >= rectA.x 
		&& rectA.y + rectA.h >= rectB.y  //if all true return true:
		&& rectB.y + rectB.h >= rectA.y) return true;
	//if not return false
	else return false;
}

bool Collistion::AABB(const Collider_component& colA, const Collider_component& colB) {

	// display what object hit what
	if (AABB(colA.collider, colB.collider)){

		//std::cout << colA.tag << " hit: " << colB.tag << std::endl;

		// we have a collistion
		return true;
	}
	else {

		//no collistion
		return false;
	}
}