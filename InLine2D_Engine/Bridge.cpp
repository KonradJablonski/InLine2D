#include "Bridge.h"


CBridge::CBridge(CPhysics* Physics, b2Body* BodyA, b2Body* BodyB, float width, float height, GLuint Texture)
{
	this->Physics = Physics;
	BridgeBodies = createBridge(BodyA, BodyB, (int)width, (int)height);
	this->Texture = Texture;
	this->width = width/2;
	this->height = height/2;
}


CBridge::~CBridge(void)
{
}
void CBridge::Draw()
{
		glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, Texture);

	for (int i = 0; i < BridgeBodies.size(); i++)
	{
		glPushMatrix();
		glTranslatef(BridgeBodies[i]->GetPosition().x * Physics->GetM2P(), BridgeBodies[i]->GetPosition().y* Physics->GetM2P(), 0);
		glRotatef(BridgeBodies[i]->GetAngle()* 180/M_PI , 0.0f, 0.0f , 1.0f);
	glBegin(GL_QUADS);

	glTexCoord2f(1.0f, 1.0f);		
	glVertex3f(width,height,0.0f); 

	glTexCoord2f(0, 1.0f);			
	glVertex3f(-width,	height,0.0f); 

	glTexCoord2f(0,	0);					
	glVertex3f(-width,		-height,0.0f); 

	glTexCoord2f(1.0f,0);			
	glVertex3f(width,		-height,0.0f); 

	glEnd();
	//glTranslatef(-BridgeBodies[i]->GetPosition().x, -BridgeBodies[i]->GetPosition().y, 0);
	glPopMatrix();
	}
	
		glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}

std::vector<b2Body*> CBridge::createBridge(b2Body* sta1,b2Body* sta2,int w,int h)
{//its returning vector of Bodies!, will use for future to draw the images on top of them in NEW rope/bridge sprite class
	std::vector<b2Body*> BodyList;
	b2Vec2 pos1=Physics->GetM2P()*(sta1->GetWorldCenter()+(((b2PolygonShape*)sta1->GetFixtureList()->GetShape())->GetVertex(1)));
	b2Vec2 pos2=Physics->GetM2P()*(sta2->GetWorldCenter()+(((b2PolygonShape*)sta2->GetFixtureList()->GetShape())->GetVertex(0)));
	int num= (int)(pos2.x-pos1.x)/w;
	b2RevoluteJointDef jointDef;
	//jointDef.collideConnected = false;

	jointDef.bodyA=sta1;
	b2Body* prev,*cur;
	prev=Physics->addRect((int)(pos1.x)+(w/2),(int)(pos1.y),w + (w*0.2f),h,true, 0);
	BodyList.push_back(prev);
	jointDef.bodyB=prev;
	jointDef.localAnchorA.Set(((b2PolygonShape*)sta1->GetFixtureList()->GetShape())->GetVertex(1).x,0);
	jointDef.localAnchorB.Set(-w/2*Physics->GetP2M(),0);


	jointDef.bodyA->SetGravityScale(4);
	jointDef.bodyB->SetGravityScale(4);

	Physics->GetWorld()->CreateJoint(&jointDef);
	for(int i=0;i<num-1;i++)
	{
		cur=Physics->addRect(pos1.x+i*w,pos1.y,w + (w*0.2f),h,true,0);
		BodyList.push_back(cur);

		//not working the way i wanted, got to test this around to figure out how to limit the
		//rotation angle!
		//	jointDef.enableLimit = true;
		//jointDef.lowerAngle =  jointDef.referenceAngle;//Lowerangle * M_PI/180;
		//jointDef.upperAngle =  jointDef.referenceAngle;//Upperangle * M_PI/180;

		jointDef.bodyA=prev;
		jointDef.bodyB=cur;
		jointDef.localAnchorA.Set(w/2*Physics->GetP2M(),0);
		jointDef.localAnchorB.Set(-w/2*Physics->GetP2M(),0);

		jointDef.bodyA->SetGravityScale(4);
		jointDef.bodyB->SetGravityScale(4);

		Physics->GetWorld()->CreateJoint(&jointDef);
		prev=cur;      
	}

	//jointDef.enableLimit = true;

	jointDef.bodyA=prev;
	jointDef.bodyB=sta2;

	jointDef.localAnchorA.Set(w/2*Physics->GetP2M(),0);
	jointDef.localAnchorB.Set((((b2PolygonShape*)sta2->GetFixtureList()->GetShape())->GetVertex(0)).x,0);

	//	jointDef.bodyA->SetGravityScale(-20);
	//	jointDef.bodyB->SetGravityScale(-20);

	Physics->GetWorld()->CreateJoint(&jointDef); 

	return BodyList;
}