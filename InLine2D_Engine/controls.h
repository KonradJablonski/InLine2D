#pragma once
#include <SDL2/SDL.h>

// add  ""  when exporting as dll
class __declspec( dllexport ) controls
{
public:
	//event is passed down from the engine class
	controls(SDL_Event* theEvent);
	~controls(void);

	//possible key states
enum KeyState
{
    KEY_NONE = -1,
    KEY_PRESSED = 0,
    KEY_RELEASED = 1,
    KEY_HOLDING = 2
};

	//returns true key was pressed
	bool isKeyDown(int SDLK_ID);
	//returns true key is being held
	bool isKeyHeld(int SDLK_ID);
	//returns true key was released
	bool isKeyUp(int SDLK_ID);

	//returns true if Mouse button was pressed
	bool isMouseDown(int MouseButton);
	//returns true if Mouse button is being held
	bool isMouseHeld(int MouseButton);
	//returns true if Mouse button was released
	bool isMouseUp(int MouseButton);

	//Gets SDL event
	SDL_Event* GetEvent();

	//this runs every frame
	void Update();
private:
	SDL_Event* events; //Pointer to an SDL events system

	//Holds Current Mouse states
	int LeftMouseState;
	int RightMouseState;
	int LeftMouseHeld;
	int RightMouseHeld;

	//Press and Release Key States
	int KEYS_HELD_STATES[322];  // 322 is the number of SDLK_DOWN events
	//Held Key States
	int KEYS_PRESSED_STATES[322];
};

