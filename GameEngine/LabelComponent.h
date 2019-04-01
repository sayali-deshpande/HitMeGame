#pragma once
//#ifndef _LABELCOMPONENT_H
//#define _LABELCOMPONENT_H

#include "SDL2-2.0.8\SDL.h"
#include "SDL2-2.0.8\SDL_ttf.h"
#include <string>
#include <map>
#include "GlobalDeclarations.h"

class LabelComponent /*: public Component*/
{
public:
	LabelComponent(int xpos, int ypos, std::string text, std::string font, SDL_Color& colour)
		: labelText(text), labelFont(font), textColour(colour)
	{
		position.x = xpos;
		position.y = ypos;
	}
	~LabelComponent();

	void AddFont(std::string id, std::string path, int fontsize);
	TTF_Font* GetFont(std::string id);
	void SetLabelText(std::string text, std::string font);
	void render(); 
private:
	std::map<std::string, TTF_Font*> fonts;
	SDL_Rect position;
	std::string labelText;
	std::string labelFont;
	SDL_Color textColour;
	SDL_Texture* labelTexture = NULL;
};
//#endif