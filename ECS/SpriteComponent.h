#pragma once
#include "Components.h"
#include <SDL.h>
#include "../Texture_manager.h"
#include "Animation.h"
#include <map>

class SpriteComponent : public Component{

	//define member variables
	TransformComponent *transform;
	SDL_Texture* texture;
	SDL_Rect src_rect, dest_rect;

	//check if object has animations
	bool animated = false;
	int frames = 0;
	int a_speed = 100;

public:
	
	//flip animation 
	SDL_RendererFlip sprite_flip = SDL_FLIP_NONE;

	//for setting the y position we need animation index
	int animIndex = 0;
	//map holding animations
	std::map<const char*, Animation> animations;

	//new default constructor
	SpriteComponent() = default;
	//constructor taking a path for texture to load
	SpriteComponent(const char* path){
		
		setTex(path);
	};

	//animated object consturctor
	SpriteComponent(const char* path, bool isAnimated) {
		
		animated = isAnimated;

		//create animation objects
		Animation idle = Animation(0, 6, 200);
		Animation walk = Animation(1, 9, 75);

		//add animations to vector
		animations.emplace("idle", idle);
		animations.emplace("walk", walk);

		Play("idle");

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

		//check if object is animated
		if (animated) {

			//what this does is every frame it moves the source rectangle 32pixels to the right
			src_rect.x = src_rect.w * static_cast<int>((SDL_GetTicks() / a_speed) % frames);
		}

		//when animIndex is changed to walk, then move 32pixels down:
		src_rect.y = animIndex * transform->height;

		//update the position from the x and y functions - the camera
		dest_rect.x = static_cast<int>(transform->position.x - Game::camera.x);
		dest_rect.y = static_cast<int>(transform->position.y - Game::camera.y) ;
		//size of the destination rectangle
		dest_rect.h = transform->height * transform->scale;
		dest_rect.w = transform->width * transform->scale;
	}

	void Draw() override {

		//draw the texture
		TextureManager::Draw(texture, src_rect, dest_rect, sprite_flip);
	}

	void setTex(const char *path) {

		texture = TextureManager::load_texture(path);
	}

	void Play(const char* a_name) {

		frames = animations[a_name].frames;
		animIndex = animations[a_name].index;
		a_speed = animations[a_name].speed;
	}
};