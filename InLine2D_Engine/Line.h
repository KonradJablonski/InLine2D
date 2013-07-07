#pragma once
#include "stdafx.h"
#include "TextureLoader.h"

class DllExport CLine : public CTextureLoader
{
public:
	CLine(void);
	CLine(std::string TexturePath, int passedLineSize);

	~CLine(void);
	void DrawElasticLine(b2Vec2 BeginPosition, b2Vec2 EndPosition);
private:
	GLuint Texture;
	int LineSize;
};

