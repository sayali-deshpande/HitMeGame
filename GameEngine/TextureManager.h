//#ifndef _TEXTUREMANAGER_H
//#define _TEXTUREMANAGER_H

#pragma once

#include "SDL2-2.0.8\SDL.h"
#include <unordered_map>

using namespace std;

//structure to hold the texture and id together in map
struct LoadedTexture
{
	LoadedTexture();
	int id;
	std::string filename; // name of loaded texture
	SDL_Texture* tex;
	int refCount; // number of times the texture has been loaded
};

class TextureManager
{
private:
	static TextureManager *sInstance;
	
	~TextureManager();
	TextureManager();
	bool CheckIfAlreadyExist(std::string filename);
	//container to hold loaded textures
	typedef std::unordered_map<std::string, LoadedTexture> TextureMap;
	typedef TextureMap::iterator TextureMapItr;
	TextureMap m_textureMap;
	static  int m_texID;
	LoadedTexture loadedTex;

public:
	static TextureManager* Instance();
	static void Release();
	
	LoadedTexture LoadTexture(const std::string filename, SDL_Renderer &renderer);
	void UnloadTexture(LoadedTexture *delTexture);
	void UpdateTextureCount(int textureID);
private:
	

};


//#endif
