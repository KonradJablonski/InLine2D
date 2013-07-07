#pragma once
#include "stdafx.h"

class DllExport CCollisionListener : public b2ContactListener
{
public:
	CCollisionListener(void);
	~CCollisionListener(void);

	virtual void BeginContact(b2Contact* contact);
	virtual void EndContact(b2Contact* contact);

	virtual void PostSolve(b2Contact* cotact, const b2ContactImpulse* impulse);
	virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);

};

