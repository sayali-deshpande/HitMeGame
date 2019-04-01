//#ifndef _INPUTKEY_H
//#define _INPUTKEY_H

#pragma once

#define KEYBOARD_KEY_SIZE KEYBOARD_KEY_MAX
enum InputKey
{
	KEYBOARD_KEY_LEFT,
	KEYBOARD_KEY_RIGHT,
	KEYBOARD_KEY_UP,
	KEYBOARD_KEY_DOWN,
	KEYBOARD_KEY_SPACE,
	KEYBOARD_KEY_ENTER,
	KEYBOARD_KEY_ESCAPE,
	MOUSE_BUTTON_LEFT,
	INPUTKEY_MAX,
	MOUSEBUTTONDOWN,
	KEYBOARD_KEY_MAX,

	BUTTON_KEY_DOWN,
	BUTTON_KEY_UP,
};

enum MouseButton
{
	MOUSE_LEFT,
	MOUSE_RIGHT,

	MOUSE_MAX   // No button, just to define max
				// array size.
};


//#endif