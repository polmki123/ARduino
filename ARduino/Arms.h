/*
	캐릭터의 팔 부분
*/
#ifndef __ARMS__
#define __ARMS__
#include <gl/glut.h>
float h_height = 10, h_size = 2, a_size = 2, a_height = 5;
float ca_hsize = 10, ca_wsize = 2;
float ca_hsize_1 = ca_hsize/2, ca_wsize_1 = ca_wsize;

GLfloat cat_arms[][3] =
{
	{-ca_wsize, -ca_hsize, -ca_wsize}, // vertex 0
	{ca_wsize, -ca_hsize, -ca_wsize},
	{ca_wsize, ca_hsize, -ca_wsize},
	{-ca_wsize, ca_hsize, -ca_wsize},
	{-ca_wsize, -ca_hsize, ca_wsize},
	{ca_wsize, -ca_hsize, ca_wsize},
	{ca_wsize, ca_hsize, ca_wsize},
	{-ca_wsize, ca_hsize, ca_wsize},
};

GLfloat cat_arms_1[][3] =
{
	{-ca_wsize_1, -ca_hsize_1, -ca_wsize_1}, // vertex 0
	{ca_wsize_1, -ca_hsize_1, -ca_wsize_1},
	{ca_wsize_1, ca_hsize_1, -ca_wsize_1},
	{-ca_wsize_1, ca_hsize_1, -ca_wsize_1},
	{-ca_wsize_1, -ca_hsize_1, ca_wsize_1},
	{ca_wsize_1, -ca_hsize_1, ca_wsize_1},
	{ca_wsize_1, ca_hsize_1, ca_wsize_1},
	{-ca_wsize_1, ca_hsize_1, ca_wsize_1},
};

class Arms
{
private :
public :
	Arms()
	{
	}
	void arms0_poly(int a, int b, int c, int d)
	{
		VECTOR normal1, normal1_1;
		{
			VECTOR v1(cat_arms_1[a],cat_arms_1[b]),v2(cat_arms_1[a],cat_arms_1[c]),v3(cat_arms_1[a],cat_arms_1[d]);
			Cross_Product(v1,v2,normal1);
			Cross_Product(v2,v3,normal1_1);
		}	
		//glColor3f(1.0f,1.0f,1.0f);// white !
		//glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, text_cat_arms);	
		glBegin(GL_TRIANGLES);
		{
			glNormal3f(normal1.x,normal1.y,normal1.z);
			glTexCoord2f(0.0f, 0.0f); glVertex3fv(cat_arms[a]);
			glTexCoord2f(0.0f, 1.0f); glVertex3fv(cat_arms[b]);
			glTexCoord2f(1.0f, 1.0f); glVertex3fv(cat_arms[c]);
		}
		glEnd();
		glBegin(GL_TRIANGLES);
		{
			glNormal3f(normal1_1.x,normal1_1.y,normal1_1.z);
			glTexCoord2f(0.0f, 0.0f); glVertex3fv(cat_arms[a]);
			glTexCoord2f(1.0f, 1.0f); glVertex3fv(cat_arms[c]);
			glTexCoord2f(1.0f, 0.0f); glVertex3fv(cat_arms[d]);
		}
		glEnd();
		//glDisable(GL_TEXTURE_2D);		
	}

	void arms1_poly(int a, int b, int c, int d, int e)
	{
		VECTOR normal1, normal1_1;
		{
			VECTOR v1(cat_arms_1[a],cat_arms_1[b]),v2(cat_arms_1[a],cat_arms_1[c]),v3(cat_arms_1[a],cat_arms_1[d]);
			Cross_Product(v1,v2,normal1);
			Cross_Product(v2,v3,normal1_1);
		}	
		//glColor3f(1.0f,1.0f,1.0f);// white !
		//glEnable(GL_TEXTURE_2D);
		if(e == 0)
		{
			glBindTexture(GL_TEXTURE_2D, text_cat_arms);
		}
		else if(e == 1)
		{
			glBindTexture(GL_TEXTURE_2D, text_cat_hand);
		}
		glBegin(GL_TRIANGLES);
		{
			glNormal3f(normal1.x,normal1.y,normal1.z);
			glTexCoord2f(0.0f, 0.0f); glVertex3fv(cat_arms_1[a]);
			glTexCoord2f(0.0f, 1.0f); glVertex3fv(cat_arms_1[b]);
			glTexCoord2f(1.0f, 1.0f); glVertex3fv(cat_arms_1[c]);
		}
		glEnd();
		glBegin(GL_TRIANGLES);
		{
			glNormal3f(normal1_1.x,normal1_1.y,normal1_1.z);
			glTexCoord2f(0.0f, 0.0f); glVertex3fv(cat_arms_1[a]);
			glTexCoord2f(1.0f, 1.0f); glVertex3fv(cat_arms_1[c]);
			glTexCoord2f(1.0f, 0.0f); glVertex3fv(cat_arms_1[d]);
		}
		glEnd();
		//glDisable(GL_TEXTURE_2D);		
	}

	//---그리기---
	void arms0_draw()
	{	
		glPushMatrix();
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
			glTranslatef(0, -ca_hsize, 0);
			arms0_poly(0,3,2,1);
			arms0_poly(1,2,6,5);
			arms0_poly(5,6,7,4);
			arms0_poly(4,7,3,0);
			arms0_poly(3,7,6,2);
			arms0_poly(0,1,5,4);
		glPopMatrix();
	}
	void arms1_draw(int i)
	{	
		glPushMatrix();
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
			glTranslatef(0, -ca_hsize_1, 0);
			arms1_poly(0,3,2,1,i);
			arms1_poly(1,2,6,5,i);
			arms1_poly(5,6,7,4,i);
			arms1_poly(4,7,3,0,i);
			arms1_poly(3,7,6,2,i);
			arms1_poly(0,1,5,4,i);
		glPopMatrix();
		if(i == 1)
		{
			glPushMatrix();
				glTranslatef(0, -ca_hsize_1*2, 0);
				//glTranslatef(0, 10, 0);
				//glEnable(GL_TEXTURE_2D);
				//glColor3f(1, 1, 1);
				glBindTexture(GL_TEXTURE_2D, text_cat_hand);
				glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
				GLfloat zPlane[] = {0, 0, 1, 0};
				glEnable(GL_TEXTURE_GEN_S);glEnable(GL_TEXTURE_GEN_T);
				glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
				glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
				glTexGenfv(GL_S, GL_OBJECT_PLANE, zPlane);
				glTexGenfv(GL_T, GL_OBJECT_PLANE, zPlane);
				glutSolidSphere(2.0,4,10);	
				glDisable(GL_TEXTURE_GEN_S);glDisable(GL_TEXTURE_GEN_T);
				//glDisable(GL_TEXTURE_2D);		
			glPopMatrix();
		}
	}	
};


#endif