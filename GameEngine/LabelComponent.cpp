#include "LabelComponent.h"

LabelComponent::~LabelComponent()
{
}

void LabelComponent::AddFont(std::string id, std::string path, int fontsize)
{
	fonts.emplace(id, TTF_OpenFont(path.c_str(),fontsize));
	SetLabelText(labelText, labelFont);
}

TTF_Font * LabelComponent::GetFont(std::string id)
{
	return fonts[id];
}

void LabelComponent::SetLabelText(std::string text, std::string font)
{
	SDL_Surface* surf = TTF_RenderText_Blended(GetFont(font), text.c_str(), textColour);
	labelTexture = SDL_CreateTextureFromSurface(renderer,surf);
	SDL_FreeSurface(surf);

	SDL_QueryTexture(labelTexture, nullptr, nullptr, &position.w, &position.h);
}

void LabelComponent::render()
{
	SDL_RenderCopy(renderer, labelTexture, nullptr, &position);
}
