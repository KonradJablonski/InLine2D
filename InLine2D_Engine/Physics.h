#pragma once

#include "stdafx.h"
#include "CollisionListener.h"

class DllExport CPhysics
{
public:
	CPhysics(void);
	~CPhysics(void);
#define M_PI 3.14

	void CapFramesPerSecond(Uint32 Amount);
	void Init();
	void display(float Camera_Z);
	void Update(int FPS);

	b2World* GetWorld(){ return world;};
	float GetM2P(){ return M2P; }
	float GetP2M(){ return P2M; }
	b2Body* addRect(int x,int y,int w,int h,bool dyn, int filterId);
	void drawSquare(b2Vec2* points,b2Vec2 center,float angle,int VertexCount,float  Camera_Z);
	void SetDebugDrawMode(bool TrueOrFalse);
	b2Body* addShape(int x,int y,int w,int h,std::vector<b2Vec2> PassedInVerticies,bool dyn);
	std::vector<b2Body*> createBridge(b2Body* sta1,b2Body* sta2,int w,int h);
	//void createRope(b2Body* sta1,b2Body* sta2,int w,int h);
	b2Joint* createRope(b2Body* BodyA,b2Body* BodyB,b2Vec2 AnchorA, b2Vec2 AnchorB, bool IgnoreRotA, bool IgnoreRotB, float distanceBetweenObjects, float BodyA_mass, float BodyB_mass, bool CollideConnected);
	b2Joint* createWeld(b2Body* BodyA,b2Body* BodyB,b2Vec2 AnchorA, b2Vec2 AnchorB, float BodyA_mass, float BodyB_mass, bool CollideConnected);
	b2Joint* createRevolute(b2Body* BodyA,b2Body* BodyB,b2Vec2 AnchorA, b2Vec2 AnchorB, float lowerAngle, float upperAngle, float BodyA_mass, float BodyB_mass, bool CollideConnected, bool rotationLimit);

	b2Body*  CreateAnEdge(float x, float y, float x_end, float y_end,std::string Type);
	b2Body *CPhysics::addCircle(int x,int y,int r,bool dyn);
private:
	//physics varaibles
	int start;
	float M2P; // meters to Pixels conversion
	float P2M; //pixels to meters conversion
	bool DebugDrawObjects;
	b2World* world;

	CCollisionListener myListener;
};

