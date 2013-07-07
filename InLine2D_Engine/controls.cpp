#include "controls.h"


controls::controls(SDL_Event* theEvents)
{
	events = theEvents;

	for(int i = 0; i < 322; i++) { // init them all to false
		KEYS_HELD_STATES[i] = KEY_NONE;
		KEYS_PRESSED_STATES[i] = KEY_NONE;
	}

	LeftMouseState = 0;
	RightMouseState = 0;
	LeftMouseHeld = 0;
	RightMouseHeld = 0;
}


controls::~controls(void)
{
}

bool controls::isMouseDown(int MouseButton)
{

	if (MouseButton == SDL_BUTTON_LEFT)
	{
		if (LeftMouseState == KEY_PRESSED)
			return true;
	}
	else if (MouseButton == SDL_BUTTON_RIGHT)
	{
		if (RightMouseState == KEY_PRESSED)
			return true;
	}

	return false;
}

bool controls::isMouseHeld(int MouseButton)
{

	if (MouseButton == SDL_BUTTON_LEFT)
	{
		if (LeftMouseState == KEY_HOLDING) 
			return true;
	}
	else if (MouseButton == SDL_BUTTON_RIGHT)
	{
		if (RightMouseState == KEY_HOLDING)
			return true;
	}

	return false;
}

bool controls::isMouseUp(int MouseButton)
{

	if (MouseButton == SDL_BUTTON_LEFT)
	{
		if (LeftMouseState == KEY_RELEASED) 
			return true;
	}
	else if (MouseButton == SDL_BUTTON_RIGHT)
	{
		if (RightMouseState == KEY_RELEASED)
			return true;
	}

	return false;
}

void controls::Update()
{
	SDL_PumpEvents();
	const Uint8 *keystate = SDL_GetKeyboardState(NULL);

	switch (events->type) 
	{
	case SDL_KEYUP:
	case SDL_KEYDOWN:
		if (keystate)
		KEYS_PRESSED_STATES[events->key.keysym.sym] = KEY_PRESSED;
		if (!keystate)
		KEYS_PRESSED_STATES[events->key.keysym.sym] = KEY_RELEASED;
	
		break; 
	default:

		break;

	}
}

bool controls::isKeyDown(int SDLK_ID)
{

	if (KEYS_PRESSED_STATES[SDLK_ID] == KEY_PRESSED)
	{
		KEYS_PRESSED_STATES[SDLK_ID] == KEY_NONE;
		return true;
	}
	else 
		return false;
}

bool controls::isKeyHeld(int SDLK_ID)
{


	if (KEYS_PRESSED_STATES[SDLK_ID] == KEY_HOLDING)
	{
		KEYS_PRESSED_STATES[SDLK_ID] == KEY_HOLDING;
		return true;
	}
	else 
		return false;
}


bool controls::isKeyUp(int SDLK_ID)
{

	if (KEYS_PRESSED_STATES[SDLK_ID] == KEY_RELEASED)
	{
		KEYS_PRESSED_STATES[SDLK_ID] == KEY_NONE;
		return true;
	}
	else 
		return false;
}


SDL_Event* controls::GetEvent() { return events; }