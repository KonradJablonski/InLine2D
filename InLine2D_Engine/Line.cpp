#include "Line.h"

CLine::CLine(void)
{
}

CLine::CLine(std::string TexturePath, int passedLineSize)
{
	LineSize = passedLineSize;
	Texture = load_texture(TexturePath.c_str());
}


CLine::~CLine(void)
{
}

void CLine::DrawElasticLine(b2Vec2 BeginPosition, b2Vec2 EndPosition)
{
	glEnable(GL_TEXTURE_2D);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	//glPushMatrix();

		glBindTexture(GL_TEXTURE_2D, Texture);
	//	glColor3f(0.0f,0.0f,0.0f);

		glLineWidth((GLfloat)LineSize);

		glBegin(GL_LINES);
			glTexCoord2f(0.0, 1.0);
			glVertex2f(BeginPosition.x, BeginPosition.y);
			glTexCoord2f(1.0, 0.0);
			glVertex2f(EndPosition.x, EndPosition.y);
		glEnd();

	//	glColor3f(1.0f,1.0f,1.0f);
//	glPopMatrix();

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	
}