//#ifndef _SPRITECOMPONENT_H
//#define _SPRITECOMPONENT_H

#pragma once

#include "Component.h"
#include "ComponentTypes.h"
#include "GameObject.h"
#include "SDL2-2.0.8\SDL.h"
#include "SDL2-2.0.8\SDL_image.h"
#include "TextureManager.h"
#include "PositionCompponent.h"
#include "PhysicsComponent.h"
#include "Box2D\Box2D.h"
#include "GlobalDeclarations.h"
#include "Animation.h"
#include <map>

using namespace std;
struct LoadedTexture;

class SpriteComponent : public Component
{
public:
	SpriteComponent(void): Component(CT_SpriteComponent),
		m_textureID(0)
	{
	}

	SpriteComponent(bool isAnimated) : Component(CT_SpriteComponent),
		m_textureID(0)
	{
		m_animated = isAnimated;
		m_Flip = SDL_FLIP_NONE;

		//Play("Idle");
	}

	~SpriteComponent();

	void init()   override;
	void update() override;
	void render() override;

	void LoadTexture(std::string filename);
	void TestComponent();
	//void Play(const char* animName);
	void SetRenderFlip(SDL_RendererFlip setFlip = SDL_FLIP_NONE);
	void UnloadTexture();
     
	SDL_Surface *screen;
	
	b2Body* GetBody();
	SDL_Rect GetBox();
	
	//std::map<const char*, Animation> animations;
	int height, width;
	SDL_Rect srcRect;
	SDL_Rect box;
	bool m_animated = false;
private:
	int m_textureID;
	
	SDL_RendererFlip m_Flip;
	SDL_Texture *m_texture;
	SDL_Point center;
	
	b2Body* Body;
	
	LoadedTexture tempTexture;
	TextureManager *texMgr = TextureManager::Instance();
};
//#endif
