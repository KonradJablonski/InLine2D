#include "stdafx.h"
#include "Physics.h"
#include "Tringulate.h"


CPhysics::CPhysics(void)
{
}


CPhysics::~CPhysics(void)
{
}

void CPhysics::Init()
{
	M2P=20;
	P2M=1/M2P;
	start = SDL_GetTicks();
	world=new b2World(b2Vec2(0.0f,9.8f));
	world->SetAllowSleeping(true);
	DebugDrawObjects = false;
		 
	world->SetContactListener(&myListener);

}

void CPhysics::CapFramesPerSecond(Uint32 Amount)
{
	start = SDL_GetTicks();
	if(1000.0/Amount>SDL_GetTicks()-start) //cap to 30 fps
		SDL_Delay(1000.0/Amount-(SDL_GetTicks()-start));
}

void CPhysics::drawSquare(b2Vec2* points,b2Vec2 center,float angle,int VertexCount, float Camera_Z)
{

	Vector2dVector a;

	for (int i = 0; i < VertexCount; i++)
	{
		a.push_back(Vector2d(points[i].x,points[i].y));
	}
	Vector2dVector result;
	Triangulate::Process(a,result);
	int tcount = result.size()/3;

	glColor3f(0.7,0.3,0.7);
	//glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glTranslatef(center.x *M2P,center.y*M2P,Camera_Z);


	glRotatef(angle*180.0/M_PI,0,0,1);
	glBegin(GL_TRIANGLES);

	for(int i=0;i<tcount;i++){
		if (i == 0)
			glColor3f(1,0,1);
		else if (i == 1)
			glColor3f(1,0,0);
		else if (i == 2)
			glColor3f(0,1,0);
		else if (i == 3)
			glColor3f(0,0,1);
		else if (i == 4)
			glColor3f(0,1,1);
		else if (i == 5)
			glColor3f(1,0,1);


		glVertex2f(result[i*3+0].GetX()*M2P,result[i*3+0].GetY()*M2P);
		glVertex2f(result[i*3+1].GetX()*M2P,result[i*3+1].GetY()*M2P);
		glVertex2f(result[i*3+2].GetX()*M2P,result[i*3+2].GetY()*M2P);
	}
	glEnd();
	glPopMatrix();

	glColor3f(1,1,1);
}



void CPhysics::display(float Camera_Z)
{

	b2Body* tmp=world->GetBodyList();

	//world->GetBodyList()->GetFixtureList()->GetBody()->
	std::vector<b2Vec2> points;
	if (DebugDrawObjects){
		while(tmp)
		{
			for(int i=0;i<((b2PolygonShape*)tmp->GetFixtureList()->GetShape())->GetVertexCount();i++){
				points.push_back(((b2PolygonShape*)tmp->GetFixtureList()->GetShape())->GetVertex(i));
			}
			drawSquare(points.data(),tmp->GetWorldCenter(),tmp->GetAngle(),points.size(),Camera_Z);
			tmp=tmp->GetNext();
			points.clear();
		}
	}
}

void CPhysics::SetDebugDrawMode(bool TrueOrFalse)
{
	DebugDrawObjects = TrueOrFalse;
}


b2Body *CPhysics::addShape(int x,int y,int w,int h,std::vector<b2Vec2> PassedInVerticies,bool dyn)
{
	b2BodyDef bodydef;
	bodydef.position.Set(x*P2M,y*P2M);

	if(dyn)
		bodydef.type=b2_dynamicBody;
	b2Body* body=world->CreateBody(&bodydef);

	b2PolygonShape shape;

	shape.m_vertexCount = PassedInVerticies.size();

	int XAddedUp =0;
	int YAddedUp =0;
	for (int i = 0; i < PassedInVerticies.size(); i++)
	{
		XAddedUp = XAddedUp + PassedInVerticies[i].x;
		YAddedUp = YAddedUp + PassedInVerticies[i].y;
	}

	XAddedUp = XAddedUp/PassedInVerticies.size();
	YAddedUp = YAddedUp/PassedInVerticies.size();

	for (int i = 0; i < PassedInVerticies.size(); i++)
		shape.m_vertices[i].Set(((PassedInVerticies[i].x - (XAddedUp)) * P2M),((PassedInVerticies[i].y - (YAddedUp)) * P2M));


	shape.Set(shape.m_vertices,shape.m_vertexCount);

	b2FixtureDef fixturedef;

	fixturedef.shape=&shape;
	fixturedef.density=1.0f;



	fixturedef.restitution= 0.2f;
	fixturedef.friction= 1.2f;

	body->CreateFixture(&fixturedef);


	return body;
}


b2Body *CPhysics::addRect(int x,int y,int w,int h,bool dyn, int filterId)
{
	
	b2BodyDef bodydef;
	bodydef.position.Set(x*P2M,y*P2M);

	if(dyn)
		bodydef.type=b2_dynamicBody;
	b2Body* body=world->CreateBody(&bodydef);


	b2PolygonShape shape;

	std::vector<b2Vec2> PassedInVerticies;
	PassedInVerticies.push_back(b2Vec2(-w/2*P2M,-h/2*P2M));
	PassedInVerticies.push_back(b2Vec2((w/2)*P2M,-h/2*P2M));
	PassedInVerticies.push_back(b2Vec2((w/2)*P2M, (h/2)*P2M));
	PassedInVerticies.push_back(b2Vec2(-w/2*P2M, (h/2)*P2M));

	shape.m_vertexCount = 4;

	//for (int i = 0; i < PassedInVerticies.size(); i++)
	//	shape.m_vertices[i].Set(PassedInVerticies[i].x, PassedInVerticies[i].y);

	//CUBE in verticies
	shape.m_vertices[0].Set(-w/2*P2M,-h/2*P2M);
	shape.m_vertices[1].Set( (w/2)*P2M,-h/2*P2M);
	shape.m_vertices[2].Set( (w/2)*P2M, (h/2)*P2M);
	shape.m_vertices[3].Set(-w/2*P2M, (h/2)*P2M);
	//shape.m_vertices[4].Set(-w*P2M, (h)*P2M);
	shape.Set(shape.m_vertices,shape.m_vertexCount);
	//shape.SetAsBox(P2M*w/2,P2M*h/2);
	b2FixtureDef fixturedef;

	if (filterId != 0)
	fixturedef.filter.groupIndex = filterId;

	fixturedef.shape=&shape;

	fixturedef.density=1.0f;

	body->SetGravityScale(4);

	fixturedef.restitution= 0.2f;
	fixturedef.friction= 1.2f;

	body->CreateFixture(&fixturedef);


	//deleting fixutre, so can edit fixture through functions in sprite class!
	//	b2Fixture* myFixture = body->CreateFixture(&fixturedef);
	//body->DestroyFixture(myFixture);


	return body;
}


b2Body *CPhysics::addCircle(int x,int y,int r,bool dyn)
{
	b2BodyDef bodydef;
	bodydef.position.Set(x*P2M,y*P2M);

	if(dyn)
		bodydef.type=b2_dynamicBody;
	b2Body* body=world->CreateBody(&bodydef);

	b2CircleShape shape;


shape.m_p = b2Vec2(x *P2M,y *P2M);
	shape.m_radius = r *P2M;
	//shape.SetAsBox(P2M*w/2,P2M*h/2);
	b2FixtureDef fixturedef;

	fixturedef.shape=&shape;

	fixturedef.density=1.0f;

	body->SetGravityScale(4);

	fixturedef.restitution= 0.2f;
	fixturedef.friction= 1.2f;

	body->CreateFixture(&fixturedef);


	//deleting fixutre, so can edit fixture through functions in sprite class!
	//	b2Fixture* myFixture = body->CreateFixture(&fixturedef);
	//body->DestroyFixture(myFixture);


	return body;
}

void CPhysics::Update(int FPS)
{
	world->Step(1.0f/FPS,10,10);      //update physics

}


b2Joint* CPhysics::createRevolute(b2Body* BodyA,b2Body* BodyB,b2Vec2 AnchorA, b2Vec2 AnchorB, float lowerAngle, float upperAngle, float BodyA_mass, float BodyB_mass, bool CollideConnected, bool rotationLimit)
{
	 b2RevoluteJointDef revoluteJointDef;
  revoluteJointDef.bodyA = BodyA;
  revoluteJointDef.bodyB = BodyB;
  revoluteJointDef.localAnchorA = AnchorA;
  revoluteJointDef.localAnchorB = AnchorB;

  revoluteJointDef.enableLimit = rotationLimit;
    revoluteJointDef.lowerAngle = lowerAngle;
  revoluteJointDef.upperAngle = upperAngle;

  revoluteJointDef.referenceAngle =  revoluteJointDef.lowerAngle;
  revoluteJointDef.collideConnected = CollideConnected;
  
  	b2MassData *newMass = new b2MassData();
	newMass->mass = BodyB_mass;
	BodyB->SetMassData(newMass);
	
	b2MassData *newMass2 = new b2MassData();
	newMass2->mass = BodyA_mass;
	BodyA->SetMassData(newMass2); 

return	world->CreateJoint(&revoluteJointDef); 
}


std::vector<b2Body*> CPhysics::createBridge(b2Body* sta1,b2Body* sta2,int w,int h)
{//its returning vector of Bodies!, will use for future to draw the images on top of them in NEW rope/bridge sprite class
	std::vector<b2Body*> BodyList;
	//int Lowerangle = 90;
	//int Upperangle = 90;
	b2Vec2 pos1=M2P*(sta1->GetWorldCenter()+(((b2PolygonShape*)sta1->GetFixtureList()->GetShape())->GetVertex(1)));
	b2Vec2 pos2=M2P*(sta2->GetWorldCenter()+(((b2PolygonShape*)sta2->GetFixtureList()->GetShape())->GetVertex(0)));
	int num=(pos2.x-pos1.x)/w;
	b2RevoluteJointDef jointDef;
	//jointDef.collideConnected = false;

	jointDef.bodyA=sta1;
	b2Body* prev,*cur;
	prev=addRect(pos1.x+(w/2),pos1.y,w + (w*0.2f),h,true,0);
	BodyList.push_back(prev);
	jointDef.bodyB=prev;
	jointDef.localAnchorA.Set(((b2PolygonShape*)sta1->GetFixtureList()->GetShape())->GetVertex(1).x,0);
	jointDef.localAnchorB.Set(-w/2*P2M,0);


	jointDef.bodyA->SetGravityScale(4);
	jointDef.bodyB->SetGravityScale(4);

	world->CreateJoint(&jointDef);
	for(int i=0;i<num-1;i++)
	{
		cur=addRect(pos1.x+i*w,pos1.y,w + (w*0.2f),h,true,0);
		BodyList.push_back(cur);

		//not working the way i wanted, got to test this around to figure out how to limit the
		//rotation angle!
		//	jointDef.enableLimit = true;
		//jointDef.lowerAngle =  jointDef.referenceAngle;//Lowerangle * M_PI/180;
		//jointDef.upperAngle =  jointDef.referenceAngle;//Upperangle * M_PI/180;

		jointDef.bodyA=prev;
		jointDef.bodyB=cur;
		jointDef.localAnchorA.Set(w/2*P2M,0);
		jointDef.localAnchorB.Set(-w/2*P2M,0);

		jointDef.bodyA->SetGravityScale(4);
		jointDef.bodyB->SetGravityScale(4);

		world->CreateJoint(&jointDef);
		prev=cur;      
	}

	//jointDef.enableLimit = true;

	jointDef.bodyA=prev;
	jointDef.bodyB=sta2;

	jointDef.localAnchorA.Set(w/2*P2M,0);
	jointDef.localAnchorB.Set((((b2PolygonShape*)sta2->GetFixtureList()->GetShape())->GetVertex(0)).x,0);

	//	jointDef.bodyA->SetGravityScale(-20);
	//	jointDef.bodyB->SetGravityScale(-20);

	world->CreateJoint(&jointDef); 

	return BodyList;
}



b2Body* CPhysics::CreateAnEdge(float x, float y, float x_end, float y_end, std::string Type)
{
	b2BodyDef bodydef;
	//bodydef.position.Set(x*P2M,y*P2M);
	b2Body* body=world->CreateBody(&bodydef);



	b2EdgeShape edge;

	edge.Set(b2Vec2(x*P2M  ,y*P2M ),b2Vec2(x_end*P2M ,y_end *P2M));


	b2FixtureDef fixturedef;

	fixturedef.shape=&edge;


	fixturedef.density=1.0f;

	body->SetGravityScale(4);


	fixturedef.restitution= 0.2f;

	//	fixturedef.restitution= 1.2f;



	if (Type == "NORMAL")
		fixturedef.friction= 1.2f;
	else if(Type == "ICE")
		fixturedef.friction= 0.01f;
	body->CreateFixture(&fixturedef);

	return body;
}


b2Joint* CPhysics::createWeld(b2Body* BodyA,b2Body* BodyB,b2Vec2 AnchorA, b2Vec2 AnchorB, float BodyA_mass, float BodyB_mass, bool CollideConnected)
{

		b2WeldJointDef jointDef;
			jointDef.bodyA = BodyA;
	jointDef.bodyB = BodyB;
	jointDef.collideConnected = CollideConnected;
	jointDef.localAnchorA = AnchorA;
	jointDef.localAnchorB = AnchorB;
	jointDef.dampingRatio = 0;
	jointDef.frequencyHz = 0;

	b2MassData *newMass = new b2MassData();
	newMass->mass = BodyB_mass;
	BodyB->SetMassData(newMass);
	
	b2MassData *newMass2 = new b2MassData();
	newMass2->mass = BodyA_mass;
	BodyA->SetMassData(newMass2); 


	return world->CreateJoint(&jointDef);
	 
}

b2Joint* CPhysics::createRope(b2Body* BodyA,b2Body* BodyB,b2Vec2 AnchorA, b2Vec2 AnchorB, bool IgnoreRotA, bool IgnoreRotB, float distanceBetweenObjects, float BodyA_mass, float BodyB_mass, bool CollideConnected)
{

	b2RopeJointDef jointDef;


	jointDef.bodyA = BodyA;
	jointDef.bodyB = BodyB;
	jointDef.collideConnected = CollideConnected;
	jointDef.localAnchorA = AnchorA;
	jointDef.localAnchorB = AnchorB;
	jointDef.maxLength = distanceBetweenObjects;

	b2MassData *newMass = new b2MassData();
	newMass->mass = BodyB_mass;
	BodyB->SetMassData(newMass);
	
	b2MassData *newMass2 = new b2MassData();
	newMass2->mass = BodyA_mass;
	BodyA->SetMassData(newMass2); 

	//BodyB->SetGravityScale(2.1f);

	BodyA->SetFixedRotation(IgnoreRotA);
	BodyB->SetFixedRotation(IgnoreRotB);

	
	return world->CreateJoint(&jointDef);
	
	/*

	b2RopeJointDef jd;
	jd.bodyA=sta1; //define bodies
	jd.bodyB=sta2;
	jd.localAnchorA = b2Vec2(w/2*P2M,0); //define anchors
	jd.localAnchorB = b2Vec2(-w/2*P2M,0);

	jd.maxLength= (sta2->GetPosition() - sta1->GetPosition()).Length(); //define max length of joint = current distance between bodies
	world->CreateJoint(&jd); //create joint

	// m_localAnchorA = def->localAnchorA;
	//m_localAnchorB = def->localAnchorB;
	*/
	/*  m_maxLength = def->maxLength;

	m_mass = 0.0f;
	m_impulse = 0.0f;
	m_state = e_inactiveLimit;
	m_length = 0.0f;*/

	//  b2Vec2 pos1=M2P*(sta1->GetWorldCenter()+(((b2PolygonShape*)sta1->GetFixtureList()->GetShape())->GetVertex(1)));
	//  b2Vec2 pos2=M2P*(sta2->GetWorldCenter()+(((b2PolygonShape*)sta2->GetFixtureList()->GetShape())->GetVertex(0)));
	//  int num=(pos2.x-pos1.x)/w;
	//  b2RevoluteJointDef jointDef;
	//   jointDef.bodyA=sta1;
	//  b2Body* prev,*cur;
	//   prev=addRect(pos1.x+(w/2),pos1.y,w,h,true);
	//   jointDef.bodyB=prev;
	//  jointDef.localAnchorA.Set(((b2PolygonShape*)sta1->GetFixtureList()->GetShape())->GetVertex(1).x,0);
	//  jointDef.localAnchorB.Set(-w/2*P2M,0);
	/*   world->CreateJoint(&jointDef);
	for(int i=0;i<num-1;i++)
	{
	cur=addRect(pos1.x+i*w,pos1.y,w,h,true);
	jointDef.bodyA=prev;
	jointDef.bodyB=cur;
	jointDef.localAnchorA.Set(w/2*P2M,0);
	jointDef.localAnchorB.Set(-w/2*P2M,0);
	world->CreateJoint(&jointDef);
	prev=cur;      
	}
	jointDef.bodyA=prev;
	jointDef.bodyB=sta2;
	jointDef.localAnchorA.Set(w/2*P2M,0);
	jointDef.localAnchorB.Set((((b2PolygonShape*)sta2->GetFixtureList()->GetShape())->GetVertex(0)).x,0);
	world->CreateJoint(&jointDef); 
	}*/

}