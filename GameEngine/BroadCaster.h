#pragma once
//#ifndef _BROADCASTER_H
//#define _BROADCASTER_H

#include <vector>
#include <memory>
#include "Listener.h"
#include "Event.h"
#include "SDL2-2.0.8\SDL.h"
#include "InputKey.h"

//class Event;

class BroadCaster
{
	std::vector<Listener*> eventListeners;
	static BroadCaster* s_BcMgr;
public:

	BroadCaster();
	~BroadCaster();

	static BroadCaster* Instance();
	static void Release();
	static BroadCaster* Get();

	void BroadCast(InputKey key/*const Event &es*/);
	void BroadCast(std::string message);

	void AddListner(Listener *listener);
	void RemoveListner(Listener *listener);
	void SendEvents(InputKey key/*SDL_Event &e*/);
	void SendEvent(std::string message);
};

//#endif