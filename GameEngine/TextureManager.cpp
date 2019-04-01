#include "TextureManager.h"
#include "SDL2-2.0.8\SDL.h"
#include "SDL2-2.0.8\SDL_image.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>

#define _CRT_SECURE_NO_WARNINGS 0

TextureManager* TextureManager::sInstance = nullptr;
int TextureManager::m_texID = 0;

TextureManager::~TextureManager()
{
	Release();
}

TextureManager::TextureManager()
{

}
bool TextureManager::CheckIfAlreadyExist(std::string filename)
{
	TextureMapItr itr = m_textureMap.find(filename);
		if (itr != m_textureMap.end())
		{
			++(itr->second.refCount);
			return true;
		}
		else
			return false;
}

TextureManager * TextureManager::Instance()
{
	if (sInstance == nullptr)
		sInstance = new TextureManager();
	return sInstance;
}
void TextureManager::Release()
{
	delete sInstance;
	sInstance = NULL;
}

LoadedTexture TextureManager::LoadTexture(const std::string filename, SDL_Renderer &renderer)
{
	if (!CheckIfAlreadyExist(filename))
	{
		//If texture does not exist then create new one
		SDL_Texture* texture = NULL;
		SDL_Surface* tempSurface = IMG_Load(filename.c_str());
		texture = SDL_CreateTextureFromSurface(&renderer, tempSurface);
		if (texture == NULL)
			printf("Texture load failed");
		SDL_FreeSurface(tempSurface);

		loadedTex.filename = filename;
		loadedTex.id = ++m_texID;
		loadedTex.tex = texture;
		loadedTex.refCount = 1;

		m_textureMap.insert(std::make_pair(filename, loadedTex));
		return loadedTex;
	}
	else
	{
		TextureMapItr itr = m_textureMap.find(filename);
		return itr->second;
	}
}

void TextureManager::UnloadTexture(LoadedTexture *delTexture)
{
	TextureMapItr itr = m_textureMap.find(delTexture->filename);
	if (itr->second.refCount > 1)
		itr->second.refCount -= 1;
	else if(itr->second.refCount == 1)
	{
		SDL_DestroyTexture(delTexture->tex);
		delTexture = NULL;
		m_textureMap.erase(itr);
	}
}

void TextureManager::UpdateTextureCount(int textureID)
{
}

LoadedTexture::LoadedTexture() : refCount(1)
{

}