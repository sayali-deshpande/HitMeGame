#include "InputManager.h"
#include "SDL2-2.0.8\SDL.h"

InputManager* InputManager::s_IpMgr = nullptr;

InputManager* InputManager::Instance()
{
	if (s_IpMgr == nullptr)
		s_IpMgr = new InputManager();

	

	return s_IpMgr;
}

void InputManager::Release()
{
	delete s_IpMgr;
	s_IpMgr = NULL;
}

bool InputManager::CheckIfAlreadyExist(SDL_Keycode key)
{
	CommandMapItr itr = m_commandMap.find(key);
	if (itr != m_commandMap.end())
	{
		return true;
	}
	else
		return false;
}

InputManager * InputManager::Get()
{
	return Instance();
}

InputManager::~InputManager()
{
	Release();
}

void InputManager::update()
{
	while (SDL_PollEvent(&m_Events) != 0)
	{
		switch (m_Events.type)
		{
		case SDL_KEYDOWN:
				cmapItr = m_commandMap.begin();
				
				cmapItr = m_commandMap.find(m_Events.key.keysym.sym);
				if (cmapItr != m_commandMap.end())
				{
					this->keyboard = SDL_GetKeyboardState(nullptr);
					for (int i = 0; i < KEYBOARD_KEY_MAX;i++)
					{
						this->keyDown[i] = false;
					}
					keyDown[cmapItr->second] = true;
					SetPressedKey(cmapItr->second);
					BroadCaster::Get()->SendEvents(cmapItr->second);
				}
				break;
		case SDL_KEYUP:
		{
			this->keyboard = SDL_GetKeyboardState(nullptr);
			cmapItr = m_commandMap.begin();

			cmapItr = m_commandMap.find(m_Events.key.keysym.sym);
			if(cmapItr!=m_commandMap.end())
				keyUp[cmapItr->second] = false;
		}
		break;
		case SDL_MOUSEBUTTONDOWN:
		{
			mouseX = m_Events.motion.x;
			mouseY = m_Events.motion.y;
			
			if(m_Events.button.button == SDL_BUTTON_LEFT)
				BroadCaster::Get()->SendEvents(MOUSE_BUTTON_LEFT);
			SetPressedKey(MOUSEBUTTONDOWN);
		}
		default: break;
		}
	}
}

InputManager::InputManager()
{
	for (int i = 0; i < KEYBOARD_KEY_SIZE; i++)
	{
		this->keyDown[i] = false;
		this->keyUp[i] = false;
	}
}
void InputManager::AddCommand(SDL_Keycode keycode, InputKey key)
{
	if (!CheckIfAlreadyExist(keycode))
	{
		m_commandMap.insert(std::make_pair(keycode, key));
	}
}

InputKey InputManager::GetPressedKey()
{
	return pressedKey;
}

void InputManager::SetPressedKey(InputKey key)
{
	pressedKey = key;
}

bool InputManager::isKeyDown(InputKey key)
{
	cmapItr = m_commandMap.begin();
	
	while (cmapItr != m_commandMap.end())
	{
		if (cmapItr->second == key)
			break;
		else
			cmapItr++;
	}

	if (cmapItr != m_commandMap.end())
	{
		return keyDown[cmapItr->second];
	}
	else
		return false;
}

bool InputManager::isKeyUp(InputKey key)
{
	cmapItr = m_commandMap.begin();

	while (cmapItr != m_commandMap.end())
	{
		if (cmapItr->second == key)
			break;
		else
			cmapItr++;
	}
	if (cmapItr != m_commandMap.end())
	{
		return true;/*keyUp[cmapItr->second]*/;
	}
	else
		return false;
}

int InputManager::getMouseX()
{
	return this->mouseX;
}

int InputManager::getMouseY()
{
	return this->mouseY;
}