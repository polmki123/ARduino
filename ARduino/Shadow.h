/*
	그림자를 위한 행렬 식
*/
#ifndef __SHADOW__
#define __SHADOW__
#include <gl/glut.h>

float planeNormal[] = { 0, 1, 0};   // n
float planePoint[]  = { 0, 0, 0};   // e

void glShadowProjectionPOINT(float * l, float * e, float * n) //매트릭스 구조 재배열
{
	float d, c;
	float mat[16];

	d = -n[0]*l[0] -n[1]*l[1] -n[2]*l[2];
	c = -e[0]*n[0] -e[1]*n[1] -e[2]*n[2] - d;

	mat[0]  = -l[0]*n[0]+c; 
	mat[4]  = -n[1]*l[0]; 
	mat[8]  = -n[2]*l[0]; 
	mat[12] = -l[0]*c-l[0]*d;

	mat[1]  = -n[0]*l[1];        
	mat[5]  = -l[1]*n[1]+c;
	mat[9]  = -n[2]*l[1]; 
	mat[13] = -l[1]*c-l[1]*d;

	mat[2]  = -n[0]*l[2];        
	mat[6]  = -n[1]*l[2]; 
	mat[10] = -l[2]*n[2]+c; 
	mat[14] = -l[2]*c-l[2]*d;

	mat[3]  = -n[0];        
	mat[7]  = -n[1]; 
	mat[11] = -n[2]; 
	mat[15] = -d;

	glMultMatrixf(mat);
}

#endif