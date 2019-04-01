//#ifndef _GLOBALDECLARATIONS_H
//#define _GLOBALDECLARATIONS_H
#pragma once

#include "SDL2-2.0.8\SDL.h"
#include "Box2D\Box2D.h"
#include "CollisionListener.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

#define FRAME_RATE 60.0f
#define DEGTORAD 0.0174532925199432957f

extern b2World* world;
extern SDL_Surface *surface;
//extern SDL_Surface *surface;
extern SDL_Window *g_window;
extern SDL_Renderer* renderer;
extern SDL_Renderer* staticRenderer;
extern float M2P;
extern float P2M; 
extern float meterToPixel;
extern float offsetX;
extern float offsetY;

extern CollisionListener collisionlistener;
extern bool DelPlayer;
static const int SCREEN_WIDTH = 1000;
static const int SCREEN_HEIGHT =1000;

extern int DelbodyUserData;
extern int DelDiamondId;

extern SDL_Rect Camera;
extern size_t GameTime;

extern SDL_RendererFlip PlayerFaceDirection;

//#endif