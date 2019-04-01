#include "GlobalDeclarations.h"
#include "SDL2-2.0.8\SDL.h"
#include "Box2D\Box2D.h"

SDL_Window *g_window = NULL;

float meterToPixel =50;//50.0; //50 pixels to a meter
float offsetX = 500.0f;//6.4f; //x offset in meters (320/50 = 6.4 This will put the 0 x-coordinate in the middle of the screen horizontally.
float offsetY = 500.0f;//4.8; //y offset in meters (240/50 = 4.8). This will put the 0 y-coordinate in the middle of the screen vertically.

b2Vec2 gravity(0,-9.8f); //normal earth gravity, 9.8 m/s/s straight down!
bool doSleep = true;

b2World* world = new b2World(gravity);
SDL_Surface* surface = NULL;
SDL_Renderer* renderer = NULL;
SDL_Renderer* staticRenderer = NULL;


CollisionListener collisionlistener;

int MaxPcCount;
int DelbodyUserData;
int DelDiamondId;

bool DelPlayer;

SDL_Rect Camera = {0,0,SCREEN_WIDTH, SCREEN_HEIGHT};

SDL_RendererFlip PlayerFaceDirection;

size_t GameTime = 30;
