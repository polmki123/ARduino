/*
	벡터를 계산해줌, 라이팅에 필요
*/
#ifndef __VECTOR__
#define __VECTOR__
#include <math.h>

#define PI 3.14159	

const int X = 0;
const int Y = 1;
const int Z = 2;

struct CVector3
{
public:
	CVector3() {}

	CVector3(float X, float Y, float Z) 
	{ 
		x = X; y = Y; z = Z;
	}

	float x, y, z;						
};

class VECTOR
{
public:
	float x,y,z;

	VECTOR()
	{
		x=0.0f;
		y=0.0f;
		z=0.0f;
	}

	VECTOR(const float* v)
	{
		x=v[0];
		y=v[1];
		z=v[2];
	}

	VECTOR(const float* p1,const float* p2)
	{
		float len;
		x=p2[0]-p1[0];
		y=p2[1]-p1[1];
		z=p2[2]-p1[2];
		len = sqrt(x*x + y*y + z*z);
		x = x/len;
		y = y/len;
		z = z/len;
	}
	VECTOR(const float* p1,const float* p2, int i)
	{
		x=p2[0]-p1[0];
		y=p2[1]-p1[1];
		z=p2[2]-p1[2];
	}
};//End of class VECTOR

void Cross_Product(const VECTOR& v1,const VECTOR& v2,VECTOR& ans)
{
	// a×b=(a2b3 - a3b2, a3b1 - a1b3, a1b2 - a2b1)
	float len;
	ans.x = v1.y * v2.z - v1.z * v2.y;
	ans.y = v1.z * v2.x - v1.x * v2.z;
	ans.z = v1.x * v2.y - v1.y * v2.x;
	len = sqrt(ans.x*ans.x + ans.y*ans.y + ans.z*ans.z);
	ans.x = ans.x/len;
	ans.y = ans.y/len;
	ans.z = ans.z/len;
	//법선을 구한다음 최종 법선의 길이를 구해 나누어 법선의 값이 -1~1 사이의 값이 되도록함.
}


#endif