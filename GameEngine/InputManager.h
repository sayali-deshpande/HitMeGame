//#ifndef _INPUTMANAGER_H
//#define _INPUTMANAGER_H

#pragma once

#include <iostream>
#include <unordered_map>
#include "BroadCaster.h"
#include "InputKey.h"
#include "SDL2-2.0.8\SDL.h"

using namespace std;
class InputManager
{
private:
	static InputManager* s_IpMgr;
	typedef std::unordered_map<SDL_Keycode,InputKey> CommandMap;
	typedef CommandMap::iterator CommandMapItr;
	CommandMap m_commandMap;
	CommandMapItr cmapItr;
	SDL_Event m_Events;

	bool keyDown[KEYBOARD_KEY_SIZE];
	bool keyUp[KEYBOARD_KEY_SIZE];

	const uint8_t* keyboard; //saves the SDL internal keyboard state
	int mouseX; /// Current mouse X position.
	/// Current mouse Y position.
	int mouseY;
	InputKey pressedKey;
public:
	static InputManager* Instance();
	static void Release();
	bool CheckIfAlreadyExist(SDL_Keycode key);
	bool isPressed(int key);

	void ReleaseKey(int key);
	bool OnKeyDown();
	bool OnKeyUp();

	// Tells if the keyboard `key` was released just now.
	bool isKeyDown(InputKey key);

	// Tells if the keyboard `key` was pressed just now.
	bool isKeyUp(InputKey key);

	/// Tells if the mouse `button` was released just now.
	bool isMouseDown(MouseButton button);

	/// Tells if the mouse *button* was pressed just now.
	bool isMouseUp(MouseButton button);

	/// Tells if the `key` is currently being pressed.
	bool isKeyPressed(InputKey key);

	/// Tells if the mouse `button` is currently being pressed.
	bool isMousePressed(MouseButton button);

	/// Tells if the user asked the game to quit.
	bool quitRequested();

	/// Returns the current mouse X position.
	int getMouseX();

	/// Returns the current mouse Y position.
	int getMouseY();

	static InputManager* Get();

	void update();
	InputManager();
	~InputManager();

	void AddCommand(SDL_Keycode keycode,InputKey);
	InputKey GetPressedKey();
	void SetPressedKey(InputKey key);

};

//#endif