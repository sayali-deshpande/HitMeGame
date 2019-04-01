#include "SpriteComponent.h"
//#include "PositionCompponent.h"
#include "ComponentTypes.h"
#include "TextureManager.h"

SpriteComponent::~SpriteComponent()
{
	
}

void SpriteComponent::init() 
{
	TestComponent();

	box.x = box.y = 0;
	srcRect.x = srcRect.y = 0;
	srcRect.w = srcRect.h = 0;
}


void SpriteComponent::update()
{
	//Only static object will be drawn in sprite Component
		if (!m_animated)
		{
			srcRect.x = srcRect.y = 0;
			int srcH, srcW;
			SDL_QueryTexture(GetParent()->tex, NULL, NULL, &srcW, &srcH);
			/*srcRect.h = height;
			srcRect.w = width;*/
			srcRect.h = srcH;
			srcRect.w = srcW;
			box.h = height;
			box.w = width;
		}
	b2Vec2 pos = GetParent()->GetBodyPositions();	
	
	box.x = (pos.x   * meterToPixel) - width / 2  /*- Camera.x*/;
	box.y = (pos.y  * -meterToPixel) - height / 2/* - Camera.y*/;

}
void SpriteComponent::render()
{
		m_texture = GetParent()->tex;
		float angle = 0.0f;
		SDL_RenderCopyEx(renderer, m_texture, &srcRect, &box, angle, NULL, m_Flip);
}

void SpriteComponent::LoadTexture(std::string filename)
{
	tempTexture = texMgr->LoadTexture(filename, *renderer);
	GetParent()->tex = tempTexture.tex;
	//texMgr->UnloadTexture(&tempTexture);
}

void SpriteComponent::TestComponent()
{
	if (renderer == NULL)
	{
		renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
		SDL_SetRenderDrawColor(renderer, /*105,105,105*/0,0,0, 0);
	}
}

void SpriteComponent::SetRenderFlip(SDL_RendererFlip setFlip)
{
	m_Flip = setFlip;
}

void SpriteComponent::UnloadTexture()
{
	//SDL_DestroyTexture(tempTexture.tex);
	texMgr->UnloadTexture(&tempTexture);
	
}

b2Body * SpriteComponent::GetBody()
{
	return Body;
}

SDL_Rect SpriteComponent::GetBox()
{
	return box;
}




