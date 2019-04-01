#pragma once
//#ifndef _LISTNER_H
//#define _LISTNER_H

#include "InputKey.h"
class Event; 

class Listener
{
public:
	Listener() {}
	virtual void OnEvent(InputKey key) = 0;
	virtual void PassMessage(std::string str) = 0;
};

//#endif