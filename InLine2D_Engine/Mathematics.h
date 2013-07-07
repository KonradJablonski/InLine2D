#pragma once
#include "stdafx.h" 

class DllExport Mathematics
{
public:
	Mathematics(void);
	~Mathematics(void);

	int RandomRange(int MinValue, int MaxValue);
	float GetDistance(b2Vec2 p1, b2Vec2 p2);
};

