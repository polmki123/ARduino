/*
	라이팅 설정
*/
#ifndef __LIGHT__
#define __LIGHT__
#include <windows.h>		
#include <stdio.h>		
#include <gl/gl.h>	
#include <gl/glu.h>	
#include <gl/glut.h>

//물체의 재질 설정
GLfloat mat_ambient[] =  { 0.5, 0.5, 0.5, 1.0 };
GLfloat mat_specular[] = { 1.0, 1.0f, 1.0f, 1.0f };
GLfloat mat_diffuse[] =  { 0.5, 0.5f, 0.5f, 1.0f };
GLfloat mat_shininess[] = { 10.0 };

//태양광 설정
GLfloat s_ambient[] =  { 0.4, 0.4, 0.4, 1.0f };
GLfloat s_specular[] = { 0.5, 0.5, 0.5, 1.0f };
GLfloat s_diffuse[] =  { 1.0, 1.0, 1.0, 1.0f };

GLfloat sun_position[] = {0.0f, 800.0f, 330.0f, 1};//태양광의 초기위치

void Light_Color_Setting() //색을 설정
{
	//물체
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	
	//태양광
	glLightfv(GL_LIGHT0, GL_AMBIENT, s_ambient);
	glLightfv(GL_LIGHT0, GL_SPECULAR, s_specular);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, s_diffuse);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0); //태양
}

void Light_Position_Setting() //광원 위치 설정
{	
	glLightfv(GL_LIGHT0, GL_POSITION, sun_position); //태양광 위치
}

void light_draw()
{
	glPushMatrix();
	glTranslatef(sun_position[0], sun_position[1], sun_position[2]);
	glBegin(GL_POLYGON);
	{
		glColor3f(0,0,0);
		glVertex3f(-10, 0, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 10, 0);
		glVertex3f(-10, 10, 0);

	}
	glEnd();
	glPopMatrix();
}

#endif