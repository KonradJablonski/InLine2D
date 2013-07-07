#include "functions.h"

float convert(std::string var)
{
	return (float)atof(var.c_str());
}

std::string convert(int var)
{
	std::stringstream ss;//create a stringstream
	ss << var;//add number to the stream
	return ss.str();//return a string with the contents of the stream
}

std::string convert(float var)
{
	std::stringstream ss;//create a stringstream
	ss << var;//add number to the stream
	return ss.str();//return a string with the contents of the stream
}

std::string convert(double var)
{
	std::stringstream ss;//create a stringstream
	ss << var;//add number to the stream
	return ss.str();//return a string with the contents of the stream
}



std::string convert(GLubyte * var)
{
	std::stringstream ss;//create a stringstream
	ss << var;//add number to the stream
	return ss.str();//return a string with the contents of the stream
}

//std::string convert(Vector3i var)
//{
//	std::stringstream ss;//create a stringstream
//	ss << var.x;
//	ss << ":";
//	ss << var.y;
//	ss << ":";
//	ss << var.z;
//	return ss.str();//return a string with the contents of the stream
//}

std::string UpperCaseToLowerCase(std::string& convertString) 
{
	for(unsigned int i=0; i<convertString.length(); i++) 
		convertString[i] = tolower(convertString[i]);

	return convertString;
}

///returns texture, make it equal to unsigned int
GLuint load_texture(const char* file)
{

	glEnable(GL_TEXTURE_2D);

	GLuint texture=NULL; //this is a handle to our texture object
	GLenum texture_format=NULL;
	GLint nofcolors;

	SDL_Surface *surface; // this surface will tell us the details of the image
	if ( (surface = IMG_Load(file)) ) {
		// Check that the image's width is a power of 2
		if ( (surface->w & (surface->w - 1)) != 0 ) {
			printf("warning: image.bmp's width is not a power of 2\n");
		}
		// Also check if the height is a power of 2
		if ( (surface->h & (surface->h - 1)) != 0 ) {
			printf("warning: image.bmp's height is not a power of 2\n");
		}
		//get number of channels in the SDL surface
		nofcolors=surface->format->BytesPerPixel;
		//contains an alpha channel
		if(nofcolors==4)
		{
			if(surface->format->Rmask==0x000000ff)
				texture_format=GL_RGBA;
			else
				texture_format=GL_BGRA;
		}
		else if(nofcolors==3) //no alpha channel
		{
			if(surface->format->Rmask==0x000000ff)
				texture_format=GL_RGB;
			else
				texture_format=GL_BGR;
		}
		else
		{
			printf("warning: the image is not truecolor...this will break ");
		}
		// Have OpenGL generate a texture object handle for us
		glGenTextures( 1, &texture );
		// Bind the texture object
		glBindTexture( GL_TEXTURE_2D, texture );
		// Set the texture's stretching properties
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		glTexImage2D( GL_TEXTURE_2D, 0, nofcolors, surface->w, surface->h, 0,
			texture_format, GL_UNSIGNED_BYTE, surface->pixels );
	}
	else {
		printf("SDL could not load PNG: %s\n", SDL_GetError());
		return 1;
	}
	glDisable(GL_TEXTURE_2D);
	//height = surface->h;
	//width = surface->w;
	SDL_FreeSurface(surface);
	return texture;
}