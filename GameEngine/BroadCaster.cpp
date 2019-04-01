#include "BroadCaster.h"

BroadCaster* BroadCaster::s_BcMgr = nullptr;

BroadCaster::BroadCaster()
{
}

BroadCaster::~BroadCaster()
{
	Release();
}

BroadCaster * BroadCaster::Instance()
{
	if (s_BcMgr == NULL)
		s_BcMgr = new BroadCaster();
	return s_BcMgr;
}

void BroadCaster::Release()
{
	delete s_BcMgr;
	s_BcMgr = NULL;
}

BroadCaster * BroadCaster::Get()
{
	return Instance();
}

void BroadCaster::BroadCast(InputKey key/*const Event &e*/ )
{
	Event ev;
	ev.type = key/*e.type*/;
	//int listSize = eventListeners.size();
	std::vector<Listener*>::iterator vecItr = eventListeners.begin();
	//while (vecItr!=eventListeners.end())
	//{
	//	(**vecItr).OnEvent(key);
	//	if (listSize < eventListeners.size())
	//	{
	////		listSize = eventListeners.size();
	//		eventListeners.resize(listSize + 1);
	//		break;
	//	}
	//	else
	//		vecItr++;
	//}
	//for (; vecItr != eventListeners.end(); vecItr++)
	//	(**vecItr).OnEvent(key/*ev*/);
		//vecItr->OnEvent(ev);

	int endIndex =0;
	for (; endIndex < eventListeners.size(); ++endIndex)
	{
		eventListeners[endIndex]->OnEvent(key);
	}
	

}

void BroadCaster::BroadCast(std::string message)
{
	//int listSize = eventListeners.size();
	//std::vector<Listener*>::iterator vecItr = eventListeners.begin();
	//while (vecItr != eventListeners.end())
	//{
	//	(**vecItr).PassMessage(message);
	//	if (listSize > eventListeners.size())
	//	{
	//		//listSize = eventListeners.size();
	//		break;
	//	}
	//	else
	//	vecItr++;
	//}
	//for (vecItr = eventListeners.begin(); vecItr != eventListeners.end(); ++vecItr)
	//	(**vecItr).PassMessage(message);

	int endIndex =0;
	for (; endIndex < eventListeners.size(); ++endIndex)
	{
		eventListeners[endIndex]->PassMessage(message);
	}
}

void BroadCaster::AddListner(Listener *listener)
{
 	eventListeners.push_back(listener);
}

void BroadCaster::RemoveListner(Listener *listener)
{
	std::vector<Listener*>::iterator vecItr;
	vecItr = std::find(std::begin(eventListeners), std::end(eventListeners), listener);

	if (vecItr != eventListeners.end())
		eventListeners.erase(vecItr);
}

void BroadCaster::SendEvents(InputKey key/*SDL_Event &e*/)
{
	Event ev;
	//ev.type = e.key.keysym.sym;
	ev.type = key;
	BroadCast(key);
}

void BroadCaster::SendEvent(std::string message)
{
	BroadCast(message);
}

