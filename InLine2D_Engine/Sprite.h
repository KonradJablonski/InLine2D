#pragma once
#include "stdafx.h"
#include "Physics.h"
#include "TextureLoader.h"

class DllExport CSprite : public CTextureLoader
{
public:
	CSprite(); //standard constructor, not used but needs to be here or it will CRASH!s 

	CSprite(float X, float Y, float W, float H, std::string FileName,        CPhysics* enginePhysics, int spriteType, int filterID);

	CSprite(float X, float Y, std::string FileName,        CPhysics* enginePhysics, int spriteType);
	CSprite(float X, float Y, GLuint AlreadyLoadedTexture, CPhysics* enginePhysics, int spriteType);

	CSprite(float X, float Y, float W, float H, std::string FileName,        CPhysics* enginePhysics, int spriteType);
	CSprite(float X, float Y, float W, float H, GLuint AlreadyLoadedTexture, CPhysics* enginePhysics, int spriteType);

	~CSprite();

	 void Draw();
	 void PlayAnimation(int first, int last, int row, int AnimationDelay);
	///if set to true, sprite will not rotate! Should be set to true on Characters/NPCs
	 void SetIgnoreRotation(bool ignoreMe) { SpriteBody->SetFixedRotation(ignoreMe);} 
	///returns spriteBody, contains a lot of functions that class is missing!
	 b2Body * GetSpriteBody(){return SpriteBody;}
	///defines how much does gravity effect the object, the higher value the faster object will fall!
	 void SetGravityScale(float scale);

	 float GetX();
	 void SetX(float X);
	 float GetY();
	 void SetY(float Y);
	 void SetPosition(float X, float Y);
 	void SetAngle(float Angle);
	 void SetFixedRotation(float AngleSpeed);
 	float GetWidth();
	 void SetWidth(float w);
	float GetHeight();
	void SetHeight(float h);
	void SetSize(float w, float h);
	GLuint GetTexture() { return Texture; }

private:
	void Init(float X, float Y, CPhysics *enginePhysics,int spriteType2, int FilterID);
	

	GLuint Texture; //Texuture of the sprite
	GLuint OldTexture;

	float current_frame_x; //current frame of the animation
	float current_frame_y; //current row of the animation
	int AnimAmount_W; //number of frames horizontly in an image
	int AnimAmount_H; //numbers of frames vertically in an image

	float x; //x position of the sprite
	float y; //y position of the sprite
	float width; //width of the sprite
	float height; //height of the sprite
	int Delay; //Delay of the animation in the sprite
	int spriteType; //there are different types of sprites for example: DYNAMIC< STATIC NORMAL

	CPhysics *Physics; //Physics clas
	b2Body *SpriteBody; //Sprite Body that contains very important informations about sprite!  Position, rotation etc.
};