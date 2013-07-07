#pragma once
#include "Physics.h"

class DllExport CBridge
{
public:
	CBridge(CPhysics* Physics, b2Body* BodyA, b2Body* BodyB, float width, float height, GLuint Texture);
	~CBridge(void);
	std::vector<b2Body*> createBridge(b2Body* sta1,b2Body* sta2,int w,int h);
	void Draw();
private:
	CPhysics* Physics;

	std::vector<b2Body*> BridgeBodies;
	GLuint Texture;
    float width;
	float height;
};

