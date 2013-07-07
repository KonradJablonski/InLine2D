#include "stdafx.h"
#include "Sprite.h"

///do not use this constructor!
CSprite::CSprite()
{
}

CSprite::CSprite(float X, float Y, float W, float H, std::string FileName,     CPhysics* enginePhysics, int spriteType2, int filterID)
{
	Texture = load_texture(FileName.c_str());
	AnimAmount_W = 1;
	AnimAmount_H = 1;
	width = W*3;
	height = H*3;
	Init(X,Y,enginePhysics,spriteType2, filterID);
}

///this constructor can define width and height of an object, if you dont choose height and width it will set automatically to the image size witdth/height.
CSprite::CSprite(float X, float Y, float W, float H, std::string FileName, CPhysics* enginePhysics,int spriteType2)
{
	Texture = load_texture(FileName.c_str());
	AnimAmount_W = 1;
	AnimAmount_H = 1;
	width = W*3;
	height = H*3;
	Init(X,Y,enginePhysics,spriteType2, 0);
}


CSprite::CSprite(float X, float Y, float W, float H, GLuint AlreadyLoadedTexture, CPhysics* enginePhysics,int spriteType2)
{
	Texture = AlreadyLoadedTexture;
	AnimAmount_W = 1;
	AnimAmount_H = 1;
	width = W*3;
	height = H*3;
	Init(X,Y,enginePhysics,spriteType2, 0);
}

///non animated sprite, with 1 frame
CSprite::CSprite(float X, float Y, std::string FileName, CPhysics* enginePhysics,int  spriteType2)
{
	Texture = load_texture(FileName.c_str());
	width = GetTextureWidth();
	height = GetTextureHeight();
	AnimAmount_W = 1;
	AnimAmount_H = 1;
	Init(X,Y ,enginePhysics,spriteType2, 0);
}

///non animated sprite, with 1 frame
CSprite::CSprite(float X, float Y, GLuint AlreadyLoadedTexture, CPhysics* enginePhysics,int  spriteType2)
{
	Texture = AlreadyLoadedTexture;
	width = GetTextureWidth();
	height = GetTextureHeight();
	AnimAmount_W = 1;
	AnimAmount_H = 1;
	Init(X,Y ,enginePhysics,spriteType2, 0);
}

CSprite::~CSprite()
{
	Physics->GetWorld()->DestroyBody(SpriteBody);
	glDeleteTextures(1,&Texture); // deleting Sprite Texture
}

///init should only run in constructor, no where else!
void CSprite::Init(float X, float Y, CPhysics *enginePhysics, int spriteType2, int FilterID)
{
	current_frame_x = 0;
	current_frame_y = 0;
	
	Delay = SDL_GetTicks();	
	x = X;
	y = Y;
	Physics = enginePhysics;
	spriteType = spriteType2;
	
	SpriteBody = NULL;
	if (spriteType2 == STATIC_SPRITE)
	{
		//SpriteBody = Physics->addCircle(X,Y,width/3.7f, true);
		SpriteBody = Physics->addRect(X,Y,width/1.5/AnimAmount_W, height/1.5/AnimAmount_H,true,FilterID);
		SpriteBody->SetType(b2_staticBody);
	}
	else if (spriteType2 == DYNAMIC_SPRITE)
	{
		SpriteBody = Physics->addRect(X,Y,width/1.5/AnimAmount_W, height/1.5/AnimAmount_H,true,FilterID);
		SpriteBody->SetType(b2_dynamicBody);
	}
	
//	b2MassData *newMass = new b2MassData();
	//newMass->mass = mass;
	//SpriteBody->SetMassData(newMass);
}

///draws the sprite, this needs to be updated constantly
void CSprite::Draw()
{
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPushMatrix();
	//glMatrixMode(GL_PROJECTION);

	if(spriteType != NORMAL_SPRITE)
	{
		glTranslatef(SpriteBody->GetPosition().x *20.0f,SpriteBody->GetPosition().y *20.0f,0);
		glRotatef(SpriteBody->GetAngle()*180.0/M_PI,0,0,1);
	}
	else if (spriteType == NORMAL_SPRITE)
	{
		glTranslatef(x,y,0);
	}
	
		glBindTexture(GL_TEXTURE_2D, Texture);

	glBegin(GL_QUADS);

	glTexCoord2f((current_frame_x+1.0f)/AnimAmount_W,  (current_frame_y+1.0f)/AnimAmount_H);		
	glVertex3f(width/(2 + AnimAmount_W),		height/(2+ AnimAmount_H),0.0f); 

	glTexCoord2f(current_frame_x/AnimAmount_W,		    (current_frame_y+1.0f)/AnimAmount_H);			
	glVertex3f(-width/(2 + AnimAmount_W),		height/(2 + AnimAmount_H),0.0f); 

	glTexCoord2f(current_frame_x/AnimAmount_W,			current_frame_y/AnimAmount_H);					
	glVertex3f(-width/(2 + AnimAmount_W),		-height/(2+ AnimAmount_H),0.0f); 

	glTexCoord2f((current_frame_x+1.0f)/AnimAmount_W,	current_frame_y/AnimAmount_H);			
	glVertex3f(width/(2 + AnimAmount_W),		-height/(2 + AnimAmount_H),0.0f); 

	glEnd();

	
	/*if(spriteType != NORMAL_SPRITE)
	{
		glRotatef(-SpriteBody->GetAngle()*180.0/M_PI,0,0,1);
		glTranslatef(-(SpriteBody->GetPosition().x *20.0f),-(SpriteBody->GetPosition().y *20.0f),-CameraZPos);
	}
	else if (spriteType == NORMAL_SPRITE)
	{
		glTranslatef(-x,-y,-CameraZPos);
	}*/
	
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	
	
}

///put in updated function, arguments( First frame of animation, last frame of animation, row of animation, animation delay the lower the faster)
void CSprite::PlayAnimation(int first, int last, int row, int AnimationDelay)
{
	current_frame_y = row;

	if (Delay+AnimationDelay < (SDL_GetTicks()))
	{
		if (current_frame_x < last)
		{
			current_frame_x++;
			Delay = SDL_GetTicks();
		}
		else
		{
			current_frame_x = first;
		}
	}
}


void CSprite::SetGravityScale(float scale)
{
	SpriteBody->SetGravityScale(scale);
}

///gets X position of the sprite
float CSprite::GetX()
{
	return SpriteBody->GetPosition().x;
}

///sets the position x of sprite
void CSprite::SetX(float X)
{
	SpriteBody->SetTransform(b2Vec2(X,SpriteBody->GetPosition().y),SpriteBody->GetAngle() );
}
///gets position Y of the sprite
float CSprite::GetY()
{
	return SpriteBody->GetPosition().y;
}
///sets the position Y of the sprite
void CSprite::SetY(float Y)
{
	SpriteBody->SetTransform(b2Vec2(SpriteBody->GetPosition().x,Y),SpriteBody->GetAngle() );
}
///Sets position X and Y of the sprite
void CSprite::SetPosition(float X, float Y)
{
	SpriteBody->SetTransform(b2Vec2(X,Y),SpriteBody->GetAngle() );
}
///sets the angle of sprite in RADIANS
void CSprite::SetAngle(float Angle)
{
	SpriteBody->SetTransform(b2Vec2(SpriteBody->GetPosition().x,SpriteBody->GetPosition().y), Angle );
}
///sets fixed Rotation of the spirt
void CSprite::SetFixedRotation(float AngleSpeed)
{
	SpriteBody->SetFixedRotation(AngleSpeed);
}
///Gets Width of the sprite
float CSprite::GetWidth(){
	return width;
}
///Sets Width of the sprite
void CSprite::SetWidth(float w)
{
	width = w;
}
///gets Height of the sprite
float CSprite::GetHeight()
{
	return height;
}
/// sets height of the sprite
void CSprite::SetHeight(float h)
{
	height = 3;	
}

///sets width and height of the sprite 
///(NOTE* This changes just image for now, might need to delete fixture in order to change the Body aswell...)
void CSprite::SetSize(float w, float h)
{
	width = w;
	height = h;
}
