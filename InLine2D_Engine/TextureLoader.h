#pragma once
#include "stdafx.h"

class DllExport CTextureLoader
{
public:
	CTextureLoader(void);
	~CTextureLoader(void);

protected:
	GLuint load_texture(const char* filename);
	int GetTextureWidth() { return TextureWidth; }
	int GetTextureHeight() { return TextureHeight; }

private:
	int TextureWidth;
	int TextureHeight;
};

