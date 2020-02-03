/*
	캐릭터의 몸통부분
*/
#ifndef __BODY__
#define __BODY__
#include <gl/glut.h>
float cb0_size = 18;
float cb1_size = 16, cb1_hsize = 50;


GLfloat cat_body_0[][3] = 
{
	{cb0_size*sin(0*PI/180), 0, cb0_size*-cos(0*PI/180)},
	{cb0_size*sin(22.5*PI/180), 0, cb0_size*-cos(22.5*PI/180)},
	{cb0_size*sin(45*PI/180), 0, cb0_size*-cos(45*PI/180)},
	{cb0_size*sin(67.5*PI/180), 0, cb0_size*-cos(67.5*PI/180)},
	{cb0_size*sin(90*PI/180), 0, cb0_size*-cos(90*PI/180)},
	{cb0_size*sin(112.5*PI/180), 0, cb0_size*-cos(112.5*PI/180)},
	{cb0_size*sin(135*PI/180), 0, cb0_size*-cos(135*PI/180)},
	{cb0_size*sin(157.5*PI/180), 0, cb0_size*-cos(157.5*PI/180)},
	{cb0_size*sin(180*PI/180), 0, cb0_size*-cos(180*PI/180)},
	{cb0_size*sin(202.5*PI/180), 0, cb0_size*-cos(202.5*PI/180)},
	{cb0_size*sin(225*PI/180), 0, cb0_size*-cos(225*PI/180)},
	{cb0_size*sin(247.5*PI/180), 0, cb0_size*-cos(247.5*PI/180)},
	{cb0_size*sin(270*PI/180), 0, cb0_size*-cos(270*PI/180)},
	{cb0_size*sin(292.5*PI/180), 0, cb0_size*-cos(292.5*PI/180)},
	{cb0_size*sin(315*PI/180), 0, cb0_size*-cos(315*PI/180)},
	{cb0_size*sin(337.5*PI/180), 0, cb0_size*-cos(337.5*PI/180)},
	{cb0_size*sin(0*PI/180), 0, cb0_size*-cos(0*PI/180)},
};

GLfloat cat_body_1[][3] = 
{
	{cb1_size*sin(0*PI/180), cb1_hsize, cb1_size*-cos(0*PI/180)},
	{cb1_size*sin(22.5*PI/180), cb1_hsize, cb1_size*-cos(22.5*PI/180)},
	{cb1_size*sin(45*PI/180), cb1_hsize, cb1_size*-cos(45*PI/180)},
	{cb1_size*sin(67.5*PI/180), cb1_hsize, cb1_size*-cos(67.5*PI/180)},
	{cb1_size*sin(90*PI/180), cb1_hsize, cb1_size*-cos(90*PI/180)},
	{cb1_size*sin(112.5*PI/180), cb1_hsize, cb1_size*-cos(112.5*PI/180)},
	{cb1_size*sin(135*PI/180), cb1_hsize, cb1_size*-cos(135*PI/180)},
	{cb1_size*sin(157.5*PI/180), cb1_hsize, cb1_size*-cos(157.5*PI/180)},
	{cb1_size*sin(180*PI/180), cb1_hsize, cb1_size*-cos(180*PI/180)},
	{cb1_size*sin(202.5*PI/180), cb1_hsize, cb1_size*-cos(202.5*PI/180)},
	{cb1_size*sin(225*PI/180), cb1_hsize, cb1_size*-cos(225*PI/180)},
	{cb1_size*sin(247.5*PI/180), cb1_hsize, cb1_size*-cos(247.5*PI/180)},
	{cb1_size*sin(270*PI/180), cb1_hsize, cb1_size*-cos(270*PI/180)},
	{cb1_size*sin(292.5*PI/180), cb1_hsize, cb1_size*-cos(292.5*PI/180)},
	{cb1_size*sin(315*PI/180), cb1_hsize, cb1_size*-cos(315*PI/180)},
	{cb1_size*sin(337.5*PI/180), cb1_hsize, cb1_size*-cos(337.5*PI/180)},
	{cb1_size*sin(0*PI/180), cb1_hsize, cb1_size*-cos(0*PI/180)},
};
GLfloat cat_body_2[][3] = 
{
	{0,0,0},
};

class Body
{
private :
public :
	Body()
	{
	}
	void body_poly(int b, int a)
	{
		VECTOR normal1, normal1_1;
		{
			VECTOR v1(cat_body_0[b],cat_body_1[b]), v2(cat_body_0[b],cat_body_0[a]);
			VECTOR v3(cat_body_1[a],cat_body_1[b]), v4(cat_body_1[a],cat_body_0[a]);
			Cross_Product(v1,v2,normal1);
			Cross_Product(v4,v3,normal1_1);
		}
		VECTOR normal2, normal2_1;
		{
			VECTOR v1(cat_body_1[b],cat_body_0[b]), v2(cat_body_1[b],cat_body_1[a]);
			VECTOR v3(cat_body_0[a],cat_body_0[b]), v4(cat_body_0[a],cat_body_1[a]);
			Cross_Product(v2,v1,normal2);
			Cross_Product(v3,v4,normal2_1);
		}
		/*VECTOR normal1, normal1_1;
		{
			VECTOR v1(cat_body_0[a],cat_body_1[b]),v2(cat_body_0[a],cat_body_1[a]),v3(cat_body_1[b],cat_body_1[a]);
			Cross_Product(v1,v2,normal1);
			Cross_Product(v2,v3,normal1_1);
		}*/
		/*VECTOR normal2;
		{
			VECTOR v1(cat_body_0[b],cat_body_0[a]),v2(cat_body_0[b],cat_body_2[1]);
			Cross_Product(v1,v2,normal2);
		}*/
		float c0 = sqrt(pow(cat_body_0[b][0] - cat_body_0[a][0], 2)+pow(cat_body_0[b][1] - cat_body_0[a][1], 2)+pow(cat_body_0[b][2] - cat_body_0[a][2], 2))/2;
		float c1 = sqrt(pow(cat_body_1[b][0] - cat_body_1[a][0], 2)+pow(cat_body_1[b][1] - cat_body_1[a][1], 2)+pow(cat_body_1[b][2] - cat_body_1[a][2], 2))/2;
		float c01 = c1/c0;
		//glColor3f(1.0f,1.0f,1.0f);// white !
		//glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, text_cat_body);
		glBegin(GL_TRIANGLES);
		{
			glNormal3f(normal1.x,normal1.y,normal1.z);
			glTexCoord2f((float)b/16, 0.0f); 
			glVertex3fv(cat_body_0[b]);
			//glNormal3f(normal2.x,normal2.y,normal2.z);
			glTexCoord4f((float)b/16*c01, 1*c01, 0, c01); 
			glVertex3fv(cat_body_1[b]);
			//glNormal3f(normal1_1.x,normal1_1.y,normal1_1.z);
			glTexCoord4f((float)a/16*c01, 1*c01, 0, c01); 
			glVertex3fv(cat_body_1[a]);
		}
		glEnd();
		glBegin(GL_TRIANGLES);
		{
			glNormal3f(normal1.x,normal1.y,normal1.z);
			glTexCoord2f((float)b/16, 0.0f); 
			glVertex3fv(cat_body_0[b]);
			//glNormal3f(normal1_1.x,normal1_1.y,normal1_1.z);
			glTexCoord4f((float)a/16*c01, 1*c01, 0, c01); 
			glVertex3fv(cat_body_1[a]);
			//glNormal3f(normal2_1.x,normal2_1.y,normal2_1.z);
			glTexCoord2f((float)a/16, 0.0f); 
			glVertex3fv(cat_body_0[a]);
		}
		glEnd();
		
		
		glBegin(GL_TRIANGLES);
		{
			glNormal3f(normal2.x,normal2.y,normal2.z);
			glTexCoord2f(0, 0); 
			glVertex3fv(cat_body_0[b]);
			glTexCoord2f(0.1, 0); 
			glVertex3fv(cat_body_0[a]);
			glTexCoord2f(0.1, 0.1);  
			glVertex3fv(cat_body_2[0]);
		}
		glEnd();
	}

	void body_draw()
	{		
		glPushMatrix();
			body_poly(0,1);
			body_poly(1,2);
			body_poly(2,3);
			body_poly(3,4);
			body_poly(4,5);
			body_poly(5,6);
			body_poly(6,7);
			body_poly(7,8);
			body_poly(8,9);
			body_poly(9,10);
			body_poly(10,11);
			body_poly(11,12);
			body_poly(12,13);
			body_poly(13,14);
			body_poly(14,15);
			body_poly(15,16);
		glPopMatrix();
	}
};

#endif