#include "Mathematics.h"


Mathematics::Mathematics(void)
{
}


Mathematics::~Mathematics(void)
{
}

int Mathematics::RandomRange(int min, int max)
{
	 return(rand()%(max-min)+min); 
}


float Mathematics::GetDistance(b2Vec2 p1, b2Vec2 p2)
{
	return sqrt ( pow((p1.x-p2.x), 2) + pow((p1.y-p2.y), 2) );

}
