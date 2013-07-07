#include "TextureLoader.h"


CTextureLoader::CTextureLoader(void)
{
}


CTextureLoader::~CTextureLoader(void)
{
}

///returns texture, make it equal to unsigned int
GLuint CTextureLoader::load_texture(const char* file)
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
	TextureHeight = surface->h;
	TextureWidth = surface->w;
	SDL_FreeSurface(surface);
	return texture;
}