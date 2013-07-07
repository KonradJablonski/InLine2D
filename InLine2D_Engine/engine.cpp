#include "stdafx.h"
#include "engine.h"
//#include "Background.h"


engine::engine(int Screen_Width, int Screen_Height, std::string TitleOfGame,  bool FullScreen) 
{
	srand ( time(NULL) );
	Title = TitleOfGame;
	fullScreen = FullScreen;
	ScreenWidth = Screen_Width;
	ScreenHeight = Screen_Height;
	OnIniEngine();
}



engine::~engine()
{

}


void engine::Quit()
{
	SDL_DestroyWindow(window); 
	endGame = true;
}


CPhysics *engine::GetPhysics() 
{ 
	return Physics; 
}

void engine::OnIniEngine(){ //Initilizes the Engine, Runs only once when game starts

	SDL_Init(SDL_INIT_EVERYTHING);

	if (fullScreen)
		window = SDL_CreateWindow(Title.c_str(),SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ScreenWidth, ScreenWidth, SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL|SDL_WINDOW_FULLSCREEN); 
	else
		window = SDL_CreateWindow(Title.c_str(),SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ScreenWidth, ScreenWidth, SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL); 

	glcontext = SDL_GL_CreateContext(window);

	glMatrixMode(GL_PROJECTION);

	events = new SDL_Event();
	SDL_PollEvent(events);  //Do an intial poll to prevent crashes

	theControls = new controls(events);

	//ini world
	Physics = new CPhysics();
	Physics->Init();

	endGame = false;

	//sprite = new CSprite(600,600,100,100,"data/character.bmp",Physics,DYNAMIC_SPRITE,1.0f);
}

void engine::OnDrawStaticFront()
{

}

void engine::OnDrawStaticBack()
{

}

void engine::OnDraw()
{

}



void engine::OnUpdate()
{

	//if (theControls->isKeyDown(SDLK_a))
	//{
	//	std::cout<< "KEY PRESSED" << std::endl;
	//}
	//	if (theControls->isKeyHeld(SDLK_a))
	//{
	//	std::cout<< "KEY HELD" << std::endl;
	//}
	//if (theControls->isKeyUp(SDLK_a))
	//{
	//	std::cout<< "KEY RELASED" << std::endl;
	//}

	//if (theControls->isMouseDown(SDL_BUTTON_LEFT))
	//{
	//	std::cout<< "LEFT MOUSE PRESSED" << std::endl;
	//}
	//	if (theControls->isMouseHeld(SDL_BUTTON_LEFT))
	//{
	//	std::cout<< "LEFT MOUSE HELD" << std::endl;
	//}
	//if (theControls->isMouseUp(SDL_BUTTON_LEFT))
	//{
	//	std::cout<< "LEFT MOUSE RELASED" << std::endl;
	//}
}

bool engine::gameLoop()
{

	//Time = SDL_GetTicks();
	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT);
	

	glOrtho(0.0f, ScreenWidth,ScreenHeight,0.0f,-100,100); 
	
	SDL_PollEvent(events);  //Poll SDL events

	OnDrawStaticBack();

	

	glTranslatef(CameraX, CameraY, 0);
	OnDraw();
	glTranslatef(-CameraX, -CameraY, 0);

	OnDrawStaticFront();

   SDL_GL_SwapWindow(window);  // Swap the window/buffer to display the result.
  
	theControls->Update();
	OnUpdate();
	
	

	if (GetEvent()->type == SDL_QUIT || endGame == true)
	{
		return false;
	}

	//int OldTime = SDL_GetTicks() - Time;
	Physics->CapFramesPerSecond(40);
	Physics->Update(40); 

	
	



	return true;
}


void engine::Run()
{
	while (gameLoop())
	{
		//Other non-engine stuff here!
	}

	SDL_Quit();
}



/*	
	switch(events->type)
{

case SDL_KEYDOWN:
switch(events->key.keysym.sym)
{
case SDLK_ESCAPE:

/*

engine::~engine()
{
Text->Destroy();
ilShutDown();
}


void engine::OnUpdate()
{
SDL_PollEvent(events);  //Poll SDL events

MainCharacter->UpdateControls();

switch(events->type)
{

case SDL_KEYDOWN:
switch(events->key.keysym.sym)
{
case SDLK_ESCAPE:
events->type = SDL_QUIT;
break;
case SDLK_UP:

break;
case SDLK_DOWN:

break;

case SDLK_EQUALS:
CameraZPos+=5;
break;
case SDLK_MINUS:
CameraZPos-=5;
break;
}
break;
case SDL_KEYUP:
switch(events->key.keysym.sym)
{
case SDLK_RETURN:
spaceKey = false;
break;
case SDLK_ESCAPE:
events->type = SDL_QUIT;
break;
case SDLK_UP:
break;
case SDLK_DOWN:
break;
case SDLK_SPACE:
spaceKey = false;
break;
}
break;
case SDL_MOUSEBUTTONUP:
{

if (events->button.button == SDL_BUTTON_LEFT){

float cameraX =(events->button.x + ((-1)*((ScreenWidth/2) + ((-1)* MainCharacter->GetX()) * Physics->GetM2P()))) ;
float cameraY =(events->button.y+ ((-1)*((ScreenHeight/1.5) + ((-1)* MainCharacter->GetY()) * Physics->GetM2P())));
TestBoxes.push_back(new CSprite(
cameraX + ((CameraZPos -((CameraZPos* 1/CameraZPos))) ),
cameraY + ((CameraZPos -((CameraZPos* 1/CameraZPos))) ),
15,15, "data/Asteroid.png",Physics, DYNAMIC_SPRITE, 1.0f));
}

}
case SDL_MOUSEBUTTONDOWN:
break;

}

}

void engine::OnDraw()
{
glClear(GL_COLOR_BUFFER_BIT);

glLoadIdentity();
glOrtho(
-CameraZPos, /*-(CameraZPos * (ScreenHeight/ScreenWidth)))*/     //left
//ScreenWidth,/*-(CameraZPos * (ScreenHeight/ScreenWidth)))*/  //right (width)
//	ScreenHeight + (CameraZPos)*(ScreenHeight/ScreenWidth),//+(CameraZPos*(ScreenHeight/ScreenWidth))), //top
//-CameraZPos - (CameraZPos)*(ScreenHeight/ScreenWidth),//+(CameraZPos*(ScreenHeight/ScreenWidth))), //+ (CameraZPos*(ScreenHeight/ScreenWidth)), //bottom
//	-100,100); // bear far values


//			Backgrounds->DrawBackground1();
//	Backgrounds->DrawBackground2();
//	Backgrounds->DrawBackground3();
//camera based on main character
//		CameraX = (ScreenWidth/2) + ((-1)* MainCharacter->GetX()) * Physics->GetM2P();
//		CameraY = (ScreenHeight/1.5) + ((-1)* MainCharacter->GetY()) * Physics->GetM2P();

//		glTranslatef(CameraX, CameraY, 0);
/*	switch(events->type)
{
case SDL_MOUSEMOTION:
Main_Light->Update(events->motion.x,events->motion.y,0);
break;
}*/

//		Physics->display(0);
//	tileManager->Draw();

//	ground->Draw();
//Box->Draw();
//Box2->Draw();
//Box3->Draw();
//for(std::vector<CBridge*>::iterator it = Bridges.begin(); it != Bridges.end(); ++it) 
//{
//		(*it)->Draw();
//	};
//		MainCharacter->Draw();
//		MainCharacter->GetSpriteBody()->ApplyForceToCenter( b2Vec2(Sun->GetX() - MainCharacter->GetX(), Sun->GetY()- MainCharacter->GetY()));
//		Sun->Draw();

//CollisionManager->RenderLines();

//			for(std::vector<CSprite*>::iterator it = TestBoxes.begin(); it != TestBoxes.end(); ++it) 
//			{
//				(*it)->GetSpriteBody()->ApplyForceToCenter( b2Vec2(Sun->GetX() - (*it)->GetX(), Sun->GetY()- (*it)->GetY()));
//				(*it)->Draw();
//			}
//
//Drawing objects after that, will not apply to cameras position

//	tileManager->DrawForeground();
//			glLoadIdentity();
///					glOrtho(
//			0,/*-(CameraZPos * (ScreenHeight/ScreenWidth)))*/     //left
//			ScreenWidth,/*-(CameraZPos * (ScreenHeight/ScreenWidth)))*/  //right (width)
//			ScreenHeight,//+(CameraZPos*(ScreenHeight/ScreenWidth))), //top
//			0,//+(CameraZPos*(ScreenHeight/ScreenWidth))), //+ (CameraZPos*(ScreenHeight/ScreenWidth)), //bottom
//			-100,100); // bear far values

//glTranslatef((-1) * ((ScreenWidth/2) + ((-1)* MainCharacter->GetX()) * Physics->GetM2P()),(-1) *((ScreenHeight/1.5) + ((-1)* MainCharacter->GetY()) * Physics->GetM2P()),0); 

//Debug Text Information
//		Text->SetRGBColor(255,0,0,1);
//		Text->TextOut(10,10,"FPS:");
//		Text->TextOut(100,10, (char*)convert(GetFrameRate()).c_str());
//		Text->TextOut(10,50,"Body Count:");
//		Text->TextOut(250,50, (char*)convert(Physics->GetWorld()->GetBodyCount()).c_str());
//		
//		Text->TextOut(10,90,"ZPos:");
//		Text->TextOut(100,90, (char*)convert(CameraZPos).c_str());
//		glColor3f(1,1,1);
///
//		SDL_GL_SwapBuffers();

//}


/*
void engine::OnIniEngine(){ //Initilizes the Engine, Runs only once when game starts

SDL_Init(SDL_INIT_EVERYTHING);

bool fullScreen = false;
if (fullScreen == true)
SDL_SetVideoMode(1024,768,32,SDL_OPENGL | SDL_FULLSCREEN);
else
SDL_SetVideoMode(1024,768,32,SDL_OPENGL);

events = new SDL_Event();
SDL_PollEvent(events);  //Do an intial poll to prevent crashes

glMatrixMode(GL_PROJECTION);
//ini world
Physics = new CPhysics();
Physics->Init();

//loading sprites
MainCharacter = new CMainCharacter((float)(ScreenWidth/2),(float)(ScreenHeight/2) -700, 100,100, "data/character.png",6,4, Physics, events, 100.0f);

ground = new CSprite((float)(ScreenWidth/2),(float)(ScreenHeight-50),ScreenHeight, 100, "data/ground.bmp", Physics , STATIC_SPRITE, 1.0f);

ilInit();
Text = new GLText("data/font/font.tga", ScreenWidth, ScreenHeight);
//Text->LoadFont("data/font/font.tga",ScreenWidth,ScreenHeight);
Text->SetRGBColor(1,1,1,1);  //sets color of the text, RGBA

spaceKey = false; //will need to get rid of this, might need to create Key Handler Class!

CameraX = (ScreenWidth/2) + ((-1)* MainCharacter->GetX()) * Physics->GetM2P();
CameraY = (ScreenHeight/1.5) + ((-1)* MainCharacter->GetY()) * Physics->GetM2P();
//Backgrounds = new CBackground(&CameraX,&CameraY);

CameraZPos = 0;


}



bool engine::gameLoop()
{
Time = SDL_GetTicks();


OnDraw();

OnUpdate();
if (events->type == SDL_QUIT)
{
return false;
}

//int OldTime = SDL_GetTicks() - Time;
Physics->CapFramesPerSecond(40);
Physics->Update(40); 

return true;
}

///Returns Current Frame Rate!, NEED TO FIX IT SO IT UPDATES EVERY MILISECOND, NOT SECOND, this causes some gravity glitches at begining of the game
int engine::GetFrameRate()
{
static float framesPerSecond    = 0.0f;       // This will store our fps
static float lastTime   = 0.0f;       // This will hold the time from the last frame
float currentTime = SDL_GetTicks() ;    
framesPerSecond += 1;
if( currentTime - lastTime > 1000 )
{
lastTime = currentTime;
current_FPS = framesPerSecond;
framesPerSecond = 0;
}
return current_FPS;
}

//		
//std::string ClockWise(std::vector<b2Vec2> p)
//{
//   int i,j,k;
//   int count = 0;
//   double z;
//
//   if (p.size() < 3)
//      return("not enough sides");
//
//   for (i=0;i<p.size();i++) {
//      j = (i + 1) % p.size();
//      k = (i + 2) % p.size();
//      z  = (p[j].x - p[i].x) * (p[k].y - p[j].y);
//      z -= (p[j].y - p[i].y) * (p[k].x - p[j].x);
//      if (z < 0)
//         count--;
//      else if (z > 0)
//         count++;
//   }
//   if (count > 0)
//      return("its COUNTER WISE");
//   else if (count < 0)
//      return("its CLOCK WISE");
//   else
//      return("its god knows what, but I like it.. cause im sexy and i know it!");
//}



*/