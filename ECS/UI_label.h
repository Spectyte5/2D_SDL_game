#pragma once
#include "Entity_component_sys.h"
#include "../Asset_Manager.h"
#include "../Game.h"
#include "../Texture_manager.h"
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>


class UIlabel : public Component{

	SDL_Rect position;
	std::string labeltext;
	std::string labelfont;
	SDL_Color textcolour;
	SDL_Texture *labeltexture;

public:
	UIlabel(int xpos, int ypos, std::string text, std::string font, SDL_Color& colour) {

		labeltext = text;
		labelfont = font;
		textcolour = colour;
		position.x = xpos;
		position.y = ypos;

		Set_labelText(labeltext, labelfont);
	}
	~UIlabel(){}
	
	//set the text and font, allows us to update text every frame
	void Set_labelText(std::string text, std::string font) {

		SDL_Surface* surf = TTF_RenderText_Blended(Game::assets->Get_Font(font), text.c_str(), textcolour);
		labeltexture = SDL_CreateTextureFromSurface(Game::renderer, surf);
		SDL_FreeSurface(surf);
		SDL_QueryTexture(labeltexture, nullptr, nullptr, &position.w, &position.h);
	}
	void Draw() override {

		//draw the text on screen
		SDL_RenderCopy(Game::renderer, labeltexture, nullptr, &position);
	}
};