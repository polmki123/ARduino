/*
	Ä³¸¯ÅÍ ²¿¸®
*/
#ifndef __TAIL__
#define __TAIL__
#include <gl/glut.h>
float ct_hsize = 7, ct_wsize = 1.5;

GLfloat cat_tail[][3] =
{
	{-ct_wsize, -ct_hsize, -ct_wsize}, // vertex 0
	{ct_wsize, -ct_hsize, -ct_wsize},
	{ct_wsize, ct_hsize, -ct_wsize},
	{-ct_wsize, ct_hsize, -ct_wsize},
	{-ct_wsize, -ct_hsize, ct_wsize},
	{ct_wsize, -ct_hsize, ct_wsize},
	{ct_wsize, ct_hsize, ct_wsize},
	{-ct_wsize, ct_hsize, ct_wsize},
};

class Tail
{
private :
public :
	Tail()
	{
	}
	void tail_poly(int a, int b, int c, int d, int e)
	{
		VECTOR normal1, normal1_1;
		{
			VECTOR v1(cat_tail[a],cat_tail[b]),v2(cat_tail[a],cat_tail[c]),v3(cat_tail[a],cat_tail[d]);
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
			glTexCoord2f(0.0f, 0.0f); glVertex3fv(cat_tail[a]);
			glTexCoord2f(0.0f, 1.0f); glVertex3fv(cat_tail[b]);
			glTexCoord2f(1.0f, 1.0f); glVertex3fv(cat_tail[c]);
		}
		glEnd();
		glBegin(GL_TRIANGLES);
		{
			glNormal3f(normal1_1.x,normal1_1.y,normal1_1.z);
			glTexCoord2f(0.0f, 0.0f); glVertex3fv(cat_tail[a]);
			glTexCoord2f(1.0f, 1.0f); glVertex3fv(cat_tail[c]);
			glTexCoord2f(1.0f, 0.0f); glVertex3fv(cat_tail[d]);
		}
		glEnd();
		//glDisable(GL_TEXTURE_2D);		
	}
	
	void tail_draw(int i)
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
			glutSolidSphere(1.5,20,20);	
			glDisable(GL_TEXTURE_GEN_S);glDisable(GL_TEXTURE_GEN_T);
			//glDisable(GL_TEXTURE_2D);		
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0, -ct_hsize, 0);
			tail_poly(0,3,2,1,i);
			tail_poly(1,2,6,5,i);
			tail_poly(5,6,7,4,i);
			tail_poly(4,7,3,0,i);
			tail_poly(3,7,6,2,i);
			tail_poly(0,1,5,4,i);
		glPopMatrix();
	}
};

#endif