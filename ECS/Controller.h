#pragma once
#include "..\Game.h"
#include "Entity_component_sys.h"
#include "Components.h"

class Controller : public Component{

	public:
		TransformComponent* transform;

		void Init() override {

			transform = &entity->getComponent<TransformComponent>();
		}
		
		//check which keys we have:
		void Update() override {

			//key pressed
			if (Game::event.type == SDL_KEYDOWN) {

				//switch keyboard keys: W,S,A,D
				switch (Game::event.key.keysym.sym) {
				case SDLK_w:
					//it moves player up: position.y += velocity.y * speed;
					transform->velocity.y = -1;
					break;
				case SDLK_s:
					transform->velocity.y = 1;
					break;
				case SDLK_a:
					transform->velocity.x = -1;
					break;
				case SDLK_d:
					transform->velocity.x = 1;
					break;
				default:
					break;
				}
			}
			//key released
			if (Game::event.type == SDL_KEYUP){
				//stop moving:
				switch (Game::event.key.keysym.sym) {
				case SDLK_w:
					transform->velocity.y = 0;
					break;
				case SDLK_s:
					transform->velocity.y = 0;
					break;
				case SDLK_a:
					transform->velocity.x = 0;
					break;
				case SDLK_d:
					transform->velocity.x = 0;
					break;
				default:
					break;
				}
			}
		}
};