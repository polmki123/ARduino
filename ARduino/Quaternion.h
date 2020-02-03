/*
	ÄõÅÍ´Ï¾ð
*/
#ifndef __QUATERNION__
#define __QUATERNION__
#include "Vector.h"
#include <math.h>

#define PI 3.14159	

class CQuaternion 
{

public:
	CQuaternion() { x = y = z = 0.0f;   w = 1.0f;  }
	
	CQuaternion(float X, float Y, float Z, float W) 
	{ 
		x = X;		y = Y;		z = Z;		w = W;
	}

	void CreateFromAxisAngle(float X, float Y, float Z, float degree);

	void CreateMatrix(float *pMatrix);

	void disp(GLfloat *matrix);

private:

	float x, y, z, w;
};

void CQuaternion::CreateFromAxisAngle(float X, float Y, float Z, float degree) 
{ 
	float angle = float((degree / 180.0f) * PI);
	float result = (float)sin(angle / 2.0f );
		

	w = (float)cos( angle / 2.0f );
	x = float(X * result);
	y = float(Y * result);
	z = float(Z * result);
}


void CQuaternion::CreateMatrix(float *pMatrix)
{
	if(!pMatrix) return;
	// First row
	pMatrix[ 0] = 1.0f - 2.0f * ( y * y + z * z );  
	pMatrix[ 1] = 2.0f * ( x * y - w * z );  
	pMatrix[ 2] = 2.0f * ( x * z + w * y );  
	pMatrix[ 3] = 0.0f;  
	// Second row
	pMatrix[ 4] = 2.0f * ( x * y + w * z );  
	pMatrix[ 5] = 1.0f - 2.0f * ( x * x + z * z );  
	pMatrix[ 6] = 2.0f * ( y * z - w * x );  
	pMatrix[ 7] = 0.0f;  
	// Third row
	pMatrix[ 8] = 2.0f * ( x * z - w * y );  
	pMatrix[ 9] = 2.0f * ( y * z + w * x );  
	pMatrix[10] = 1.0f - 2.0f * ( x * x + y * y );  
	pMatrix[11] = 0.0f;  
	// Fourth row
	pMatrix[12] = 0;  
	pMatrix[13] = 0;  
	pMatrix[14] = 0;  
	pMatrix[15] = 1.0f;
}

void CQuaternion::disp(GLfloat *matrix)
{
	for(int i = 0; i < 16; i++)
	{
		printf("%f ",matrix[i]);
		if(i%4 == 3)
		{
			printf("\n");
		}
	}
}

#endif