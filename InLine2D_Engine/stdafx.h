#pragma once
// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <time.h>
#include <vector>
//SDL Libraries
#include <SDL2\SDL.h>
#include <SDL2\SDL_opengl.h>
#include <SDL2\SDL_image.h>

//openGL
//#include <GL/glew.h>
//#include <GL/gl.h>
//#include <GL/glu.h>

#include <Box2D/Box2D.h> //physics library 
//#include <IL/il.h> //text library

//types of Spries
#define STATIC_SPRITE 0 // gravity doesnt affect, but objects collide with it
#define DYNAMIC_SPRITE 1 //gravity affects it, and objects collide with it
#define NORMAL_SPRITE 2 //gravity doesnt affect it, and objectsdont collide with it

#define DllExport   __declspec( dllexport ) 

#include "Global\functions.h" // global Essencial functions
