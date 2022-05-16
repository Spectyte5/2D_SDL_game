#pragma once
#include "Entity_component_sys.h"
#include <SDL.h>
#include "TransformComponent.h"
#include "SpriteComponent.h"


class Tile_component : public Component {

public:
	TransformComponent* transform;
	SpriteComponent* sprite;

	SDL_Rect tileRect;
	int tileID;
	const char* path;

	Tile_component() = default;
	Tile_component(int x, int y, int h, int w, int id) {

		tileRect.x = x;
		tileRect.y = y;
		tileRect.w = w;
		tileRect.h = h;
		tileID = id;

		//path = texture, depending on id:
		switch (tileID) {
		case 0:
			path = "assets/grass.png";
			break;
		case 1:
			path = "assets/dirt.png";
			break;
		case 2:
			path = "assets/water2.png";
			break;
		case 3:
			path = "assets/road.png";
			break;
		case 4:
			path = "assets/sand.png";
			break;
		default:
			break;
		}
	}

	void Init() override {

		//add position and velocity component
		entity->addComponent<TransformComponent>((float)tileRect.x, (float)tileRect.y, tileRect.w, tileRect.h, 1);
		transform = &entity->getComponent<TransformComponent>();
		//add display component
		entity->addComponent<SpriteComponent>(path);
		sprite = &entity->getComponent<SpriteComponent>();

	}
};