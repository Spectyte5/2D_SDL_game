#pragma once
#include "Components.h"
#include <SDL.h>
#include "../Texture_manager.h"

class SpriteComponent : public Component{

	//define member variables
	TransformComponent *transform;
	SDL_Texture* texture;
	SDL_Rect src_rect, dest_rect;

public:

	//new default constructor
	SpriteComponent() = default;
	//constructor taking a path for texture to load
	SpriteComponent(const char* path){
		
		setTex(path);
	};

	//destructor for textures:
	~SpriteComponent() {
		
		SDL_DestroyTexture(texture);
	}

	void Init() override {

		//get position:
		transform = &entity->getComponent<TransformComponent>();
		//staring position 0,0;
		src_rect.x = src_rect.y = 0;
		//size of the source rectangle:
		src_rect.h = transform->height;
		src_rect.w = transform->width;
	}

	void Update() override {

		//update the position from the x and y functions
		dest_rect.x = static_cast<int>(transform->position.x);
		dest_rect.y = static_cast<int>(transform->position.y);
		//size of the destination rectangle
		dest_rect.h = transform->height*transform->scale;
		dest_rect.w = transform->width * transform->scale;
	}

	void Draw() override {

		//draw the texture
		TextureManager::Draw(texture, src_rect, dest_rect);
	}

	void setTex(const char *path) {

		texture = TextureManager::load_texture(path);
	}
};