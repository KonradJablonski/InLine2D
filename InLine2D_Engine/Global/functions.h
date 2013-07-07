#pragma once

#include "../stdafx.h"
#include <sstream>
//#include "math_3d.h"

//********************************************************************
//
//	This class contains any functions which are useful on a global scale!
//
//********************************************************************

extern std::string convert(int var);
extern std::string convert(float var);
extern std::string convert(double var);

extern std::string convert(GLubyte * var);
//extern std::string convert(Vector3i var);
extern float convert(std::string var);
extern std::string UpperCaseToLowerCase(std::string& convertString);

extern GLuint load_texture(const char* file);