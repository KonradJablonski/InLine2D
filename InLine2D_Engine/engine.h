#pragma once
#include "stdafx.h"
#include "Sprite.h"
#include "Physics.h"
#include "Bridge.h"
//#include "Background.h"
#include "controls.h"

class DllExport engine 
{
public:
	engine(int Screen_Width, int Screen_Height,  std::string TitleOfGame, bool FullScreen);
	~engine(void);

	bool gameLoop(); //Game Loop
	 virtual void OnUpdate(); //Updates the game (Constantly Runing)
	 virtual void OnDraw(); //Draws Objects into the Game (Constantly Runing)
	virtual void OnDrawStaticFront(); //Draws Objects to screen that are not affected by the camera at FRONT
	virtual void OnDrawStaticBack(); //Draws Objects to screen that are not affected by the camera at BACK

	 void Quit();
	 void Run();
	//will need to move this somewhere else!
	int GetFrameRate(); //returns currentFPS

	CPhysics* GetPhysics();

	  // Create an OpenGL context associated with the window.
  SDL_GLContext glcontext;

	float GetCameraX() { return CameraX; }
	float GetCameraY() { return CameraY; }
	void SetCameraPosition(float CamX, float CamY) { CameraX = CamX; CameraY = CamY; }
	void SetCameraX(float CamX) { CameraX = CamX; }
	void SetCameraY(float CamY) { CameraY = CamY; }
	int GetScreenWidth() { return ScreenWidth; }
	int GetScreenHeight() { return ScreenWidth; }

	SDL_Event* GetEvent() { return events; }
	controls* GetControls() { return theControls; }

private:
	std::string Title;
	controls* theControls;
	//Uint8 *SDL_Key; //key handler
	SDL_Event* events; //Pointer to an SDL events system!

	 void OnIniEngine(); //runs once at begining of the game
	int current_FPS; //holds Currents FPS 
	
	//SDL_Surface* screen; //Pointer to SDL Surface that holds Screen Information
	 SDL_Window *window; 

	int ScreenWidth; //Width and Height of the screen size
	int ScreenHeight;
	Uint32 screenFlag;

	//CSprite* sprite;
	//physics 
	CPhysics *Physics;

	//Text Class
//	GLText *Text;

	float CameraX;
	float CameraY;

	bool fullScreen;

	bool endGame;

};