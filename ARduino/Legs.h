/*
	캐릭터의 다리 부분
*/
#ifndef __LEGS__
#define __LEGS__
#include <gl/glut.h>
float cl_wsize = 2, cl_hsize = 7;
float cl_wsize1 = cl_wsize - 0.2, cl_hsize1 = 2;

GLfloat cat_legs[][3] =
{
	{-cl_wsize, -cl_hsize, -cl_wsize}, // vertex 0
	{cl_wsize, -cl_hsize, -cl_wsize},
	{cl_wsize, cl_hsize, -cl_wsize},
	{-cl_wsize, cl_hsize, -cl_wsize},
	{-cl_wsize, -cl_hsize, cl_wsize},
	{cl_wsize, -cl_hsize, cl_wsize},
	{cl_wsize, cl_hsize, cl_wsize},
	{-cl_wsize, cl_hsize, cl_wsize},
};
GLfloat cat_legs_1[][3] =
{
	{-cl_wsize1, -cl_hsize1, -cl_wsize1}, // vertex 0
	{cl_wsize1, -cl_hsize1, -cl_wsize1},

	{cl_wsize, cl_hsize1, -cl_wsize},
	{-cl_wsize, cl_hsize1, -cl_wsize},

	{-cl_wsize1, -cl_hsize1, cl_wsize1},
	{cl_wsize1, -cl_hsize1, cl_wsize1},

	{cl_wsize, cl_hsize1, cl_wsize},
	{-cl_wsize, cl_hsize1, cl_wsize},
};

class Legs
{
private :
public :
	Legs()
	{
	}
	void legs0_poly(int a, int b, int c, int d)
	{
		VECTOR normal1, normal1_1;
		{
			VECTOR v1(cat_legs[a],cat_legs[b]),v2(cat_legs[a],cat_legs[c]),v3(cat_legs[a],cat_legs[d]);
			Cross_Product(v1,v2,normal1);
			Cross_Product(v2,v3,normal1_1);
		}	
		//glColor3f(1.0f,1.0f,1.0f);// white !
		//glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, text_cat_arms);
		glBegin(GL_TRIANGLES);
		{
			glNormal3f(normal1.x,normal1.y,normal1.z);
			glTexCoord2f(0.0f, 0.0f); glVertex3fv(cat_legs[a]);
			glTexCoord2f(0.0f, 1.0f); glVertex3fv(cat_legs[b]);
			glTexCoord2f(1.0f, 1.0f); glVertex3fv(cat_legs[c]);
		}
		glEnd();
		glBegin(GL_TRIANGLES);
		{
			glNormal3f(normal1_1.x,normal1_1.y,normal1_1.z);
			glTexCoord2f(0.0f, 0.0f); glVertex3fv(cat_legs[a]);
			glTexCoord2f(1.0f, 1.0f); glVertex3fv(cat_legs[c]);
			glTexCoord2f(1.0f, 0.0f); glVertex3fv(cat_legs[d]);
		}
		glEnd();
		//glDisable(GL_TEXTURE_2D);		
	}
	
	void legs1_poly(int a, int b, int c, int d)
	{
		VECTOR normal1, normal1_1;
		{
			VECTOR v1(cat_legs_1[a],cat_legs_1[b]),v2(cat_legs_1[a],cat_legs_1[c]),v3(cat_legs_1[a],cat_legs_1[d]);
			Cross_Product(v1,v2,normal1);
			Cross_Product(v2,v3,normal1_1);
		}	
		//glColor3f(1.0f,1.0f,1.0f);// white !
		//glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, text_cat_hand);
		glBegin(GL_TRIANGLES);
		{
			glNormal3f(normal1.x,normal1.y,normal1.z);
			glTexCoord2f(0.0f, 0.0f); glVertex3fv(cat_legs_1[a]);
			glTexCoord2f(0.0f, 1.0f); glVertex3fv(cat_legs_1[b]);
			glTexCoord2f(1.0f, 1.0f); glVertex3fv(cat_legs_1[c]);
		}
		glEnd();
		glBegin(GL_TRIANGLES);
		{
			glNormal3f(normal1_1.x,normal1_1.y,normal1_1.z);
			glTexCoord2f(0.0f, 0.0f); glVertex3fv(cat_legs_1[a]);
			glTexCoord2f(1.0f, 1.0f); glVertex3fv(cat_legs_1[c]);
			glTexCoord2f(1.0f, 0.0f); glVertex3fv(cat_legs_1[d]);
		}
		glEnd();
		//glDisable(GL_TEXTURE_2D);		
	}
	
	void legs0_draw()
	{	
		glPushMatrix();
			//glTranslatef(0, 10, 0);
			//glEnable(GL_TEXTURE_2D);
			//glColor3f(1, 1, 1);
			glBindTexture(GL_TEXTURE_2D, text_cat_arms);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			GLfloat zPlane[] = {0, 0, 1, 0};
			glEnable(GL_TEXTURE_GEN_S);glEnable(GL_TEXTURE_GEN_T);
			glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
			glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
			glTexGenfv(GL_S, GL_OBJECT_PLANE, zPlane);
			glTexGenfv(GL_T, GL_OBJECT_PLANE, zPlane);
			glutSolidSphere(2.0,20,20);	
			glDisable(GL_TEXTURE_GEN_S);glDisable(GL_TEXTURE_GEN_T);
			//glDisable(GL_TEXTURE_2D);		
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0, -cl_hsize, 0);
			legs0_poly(0,3,2,1);
			legs0_poly(1,2,6,5);
			legs0_poly(5,6,7,4);
			legs0_poly(4,7,3,0);
			legs0_poly(3,7,6,2);
			legs0_poly(0,1,5,4);
		glPopMatrix();
	}

	void legs1_draw()
	{	
		glPushMatrix();
			//glTranslatef(0, 10, 0);
			//glEnable(GL_TEXTURE_2D);
			//glColor3f(1, 1, 1);
			glBindTexture(GL_TEXTURE_2D, text_cat_arms);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			GLfloat zPlane[] = {0, 0, 1, 0};
			glEnable(GL_TEXTURE_GEN_S);glEnable(GL_TEXTURE_GEN_T);
			glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
			glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
			glTexGenfv(GL_S, GL_OBJECT_PLANE, zPlane);
			glTexGenfv(GL_T, GL_OBJECT_PLANE, zPlane);
			glutSolidSphere(2.0,20,20);	
			glDisable(GL_TEXTURE_GEN_S);glDisable(GL_TEXTURE_GEN_T);
			//glDisable(GL_TEXTURE_2D);		
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0, -cl_hsize1, 0);
			legs1_poly(0,3,2,1);
			legs1_poly(1,2,6,5);
			legs1_poly(5,6,7,4);
			legs1_poly(4,7,3,0);
			legs1_poly(3,7,6,2);
			legs1_poly(0,1,5,4);
		glPopMatrix();
	}
};
#endif