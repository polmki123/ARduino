/*
	캐릭터의 머리부분
*/
#ifndef __HEAD__
#define __HEAD__
#include <gl/glut.h>

float ch0_size = 32;
float ch1_size = 35,ch1_hsize = 5;
float ch2_size = 33,ch2_hsize = 40;
float ch3_size = 26,ch3_hsize = 53;
float ch4_size = 15,ch4_hsize = 65;
float ch5_hsize = 70;
float chmus_hsize = 7, chmus_wsize = 1.5;

GLfloat cat_ear[][3] =
{
	{-10, 0, 0},
	{10, 0, 0},
	{0, 30, 0},
	{0, 0, -10},
};

GLfloat cat_mus[][3] =
{
	{-chmus_hsize, -chmus_wsize, -chmus_wsize},
	{chmus_hsize, -chmus_wsize, -chmus_wsize},
	{chmus_hsize, chmus_wsize, -chmus_wsize},
	{-chmus_hsize, chmus_wsize, -chmus_wsize},
	{-chmus_hsize, -chmus_wsize, chmus_wsize},
	{chmus_hsize, -chmus_wsize, chmus_wsize},
	{chmus_hsize, chmus_wsize, chmus_wsize},
	{-chmus_hsize, chmus_wsize, chmus_wsize},
};

GLfloat cat_head_0[][3] = 
{
	{ch0_size*sin(0*PI/180), 0, ch0_size*-cos(0*PI/180)},
	{ch0_size*sin(22.5*PI/180), 0, ch0_size*-cos(22.5*PI/180)},
	{ch0_size*sin(45*PI/180), 0, ch0_size*-cos(45*PI/180)},
	{ch0_size*sin(67.5*PI/180), 0, ch0_size*-cos(67.5*PI/180)},
	{ch0_size*sin(90*PI/180), 0, ch0_size*-cos(90*PI/180)},
	{ch0_size*sin(112.5*PI/180), 0, ch0_size*-cos(112.5*PI/180)},
	{ch0_size*sin(135*PI/180), 0, ch0_size*-cos(135*PI/180)},
	{ch0_size*sin(157.5*PI/180), 0, ch0_size*-cos(157.5*PI/180)},
	{ch0_size*sin(180*PI/180), 0, ch0_size*-cos(180*PI/180)},
	{ch0_size*sin(202.5*PI/180), 0, ch0_size*-cos(202.5*PI/180)},
	{ch0_size*sin(225*PI/180), 0, ch0_size*-cos(225*PI/180)},
	{ch0_size*sin(247.5*PI/180), 0, ch0_size*-cos(247.5*PI/180)},
	{ch0_size*sin(270*PI/180), 0, ch0_size*-cos(270*PI/180)},
	{ch0_size*sin(292.5*PI/180), 0, ch0_size*-cos(292.5*PI/180)},
	{ch0_size*sin(315*PI/180), 0, ch0_size*-cos(315*PI/180)},
	{ch0_size*sin(337.5*PI/180), 0, ch0_size*-cos(337.5*PI/180)},
	{ch0_size*sin(0*PI/180), 0, ch0_size*-cos(0*PI/180)},
};

GLfloat cat_head_1[][3] = 
{
	{ch1_size*sin(0*PI/180), ch1_hsize, ch1_size*-cos(0*PI/180)},
	{ch1_size*sin(22.5*PI/180), ch1_hsize, ch1_size*-cos(22.5*PI/180)},
	{ch1_size*sin(45*PI/180), ch1_hsize, ch1_size*-cos(45*PI/180)},
	{ch1_size*sin(67.5*PI/180), ch1_hsize, ch1_size*-cos(67.5*PI/180)},
	{ch1_size*sin(90*PI/180), ch1_hsize, ch1_size*-cos(90*PI/180)},
	{ch1_size*sin(112.5*PI/180), ch1_hsize, ch1_size*-cos(112.5*PI/180)},
	{ch1_size*sin(135*PI/180), ch1_hsize, ch1_size*-cos(135*PI/180)},
	{ch1_size*sin(157.5*PI/180), ch1_hsize, ch1_size*-cos(157.5*PI/180)},
	{ch1_size*sin(180*PI/180), ch1_hsize, ch1_size*-cos(180*PI/180)},
	{ch1_size*sin(202.5*PI/180), ch1_hsize, ch1_size*-cos(202.5*PI/180)},
	{ch1_size*sin(225*PI/180), ch1_hsize, ch1_size*-cos(225*PI/180)},
	{ch1_size*sin(247.5*PI/180), ch1_hsize, ch1_size*-cos(247.5*PI/180)},
	{ch1_size*sin(270*PI/180), ch1_hsize, ch1_size*-cos(270*PI/180)},
	{ch1_size*sin(292.5*PI/180), ch1_hsize, ch1_size*-cos(292.5*PI/180)},
	{ch1_size*sin(315*PI/180), ch1_hsize, ch1_size*-cos(315*PI/180)},
	{ch1_size*sin(337.5*PI/180), ch1_hsize, ch1_size*-cos(337.5*PI/180)},
	{ch1_size*sin(0*PI/180), ch1_hsize, ch1_size*-cos(0*PI/180)},
};

GLfloat cat_head_2[][3] = 
{
	{ch2_size*sin(0*PI/180), ch2_hsize, ch2_size*-cos(0*PI/180)},
	{ch2_size*sin(22.5*PI/180), ch2_hsize,ch2_size*-cos(22.5*PI/180)},
	{ch2_size*sin(45*PI/180), ch2_hsize,ch2_size*-cos(45*PI/180)},
	{ch2_size*sin(67.5*PI/180), ch2_hsize,ch2_size*-cos(67.5*PI/180)},
	{ch2_size*sin(90*PI/180), ch2_hsize,ch2_size*-cos(90*PI/180)},
	{ch2_size*sin(112.5*PI/180), ch2_hsize,ch2_size*-cos(112.5*PI/180)},
	{ch2_size*sin(135*PI/180), ch2_hsize,ch2_size*-cos(135*PI/180)},
	{ch2_size*sin(157.5*PI/180), ch2_hsize,ch2_size*-cos(157.5*PI/180)},
	{ch2_size*sin(180*PI/180), ch2_hsize,ch2_size*-cos(180*PI/180)},
	{ch2_size*sin(202.5*PI/180),ch2_hsize,ch2_size*-cos(202.5*PI/180)},
	{ch2_size*sin(225*PI/180),ch2_hsize,ch2_size*-cos(225*PI/180)},
	{ch2_size*sin(247.5*PI/180),ch2_hsize,ch2_size*-cos(247.5*PI/180)},
	{ch2_size*sin(270*PI/180),ch2_hsize,ch2_size*-cos(270*PI/180)},
	{ch2_size*sin(292.5*PI/180),ch2_hsize,ch2_size*-cos(292.5*PI/180)},
	{ch2_size*sin(315*PI/180),ch2_hsize,ch2_size*-cos(315*PI/180)},
	{ch2_size*sin(337.5*PI/180),ch2_hsize,ch2_size*-cos(337.5*PI/180)},
	{ch2_size*sin(0*PI/180), ch2_hsize, ch2_size*-cos(0*PI/180)},
};


GLfloat cat_head_3[][3] = 
{
	{ch3_size*sin(0*PI/180), ch3_hsize, ch3_size*-cos(0*PI/180)},
	{ch3_size*sin(22.5*PI/180), ch3_hsize, ch3_size*-cos(22.5*PI/180)},
	{ch3_size*sin(45*PI/180), ch3_hsize, ch3_size*-cos(45*PI/180)},
	{ch3_size*sin(67.5*PI/180), ch3_hsize, ch3_size*-cos(67.5*PI/180)},
	{ch3_size*sin(90*PI/180), ch3_hsize, ch3_size*-cos(90*PI/180)},
	{ch3_size*sin(112.5*PI/180), ch3_hsize, ch3_size*-cos(112.5*PI/180)},
	{ch3_size*sin(135*PI/180), ch3_hsize, ch3_size*-cos(135*PI/180)},
	{ch3_size*sin(157.5*PI/180), ch3_hsize, ch3_size*-cos(157.5*PI/180)},
	{ch3_size*sin(180*PI/180), ch3_hsize, ch3_size*-cos(180*PI/180)},
	{ch3_size*sin(202.5*PI/180), ch3_hsize, ch3_size*-cos(202.5*PI/180)},
	{ch3_size*sin(225*PI/180), ch3_hsize, ch3_size*-cos(225*PI/180)},
	{ch3_size*sin(247.5*PI/180), ch3_hsize, ch3_size*-cos(247.5*PI/180)},
	{ch3_size*sin(270*PI/180), ch3_hsize, ch3_size*-cos(270*PI/180)},
	{ch3_size*sin(292.5*PI/180), ch3_hsize, ch3_size*-cos(292.5*PI/180)},
	{ch3_size*sin(315*PI/180), ch3_hsize, ch3_size*-cos(315*PI/180)},
	{ch3_size*sin(337.5*PI/180), ch3_hsize, ch3_size*-cos(337.5*PI/180)},
	{ch3_size*sin(0*PI/180), ch3_hsize, ch3_size*-cos(0*PI/180)},
};
GLfloat cat_head_4[][3] = 
{
	{ch4_size*sin(0*PI/180), ch4_hsize, ch4_size*-cos(0*PI/180)},
	{ch4_size*sin(22.5*PI/180), ch4_hsize, ch4_size*-cos(22.5*PI/180)},
	{ch4_size*sin(45*PI/180), ch4_hsize, ch4_size*-cos(45*PI/180)},
	{ch4_size*sin(67.5*PI/180), ch4_hsize, ch4_size*-cos(67.5*PI/180)},
	{ch4_size*sin(90*PI/180), ch4_hsize, ch4_size*-cos(90*PI/180)},
	{ch4_size*sin(112.5*PI/180), ch4_hsize, ch4_size*-cos(112.5*PI/180)},
	{ch4_size*sin(135*PI/180), ch4_hsize, ch4_size*-cos(135*PI/180)},
	{ch4_size*sin(157.5*PI/180), ch4_hsize, ch4_size*-cos(157.5*PI/180)},
	{ch4_size*sin(180*PI/180), ch4_hsize, ch4_size*-cos(180*PI/180)},
	{ch4_size*sin(202.5*PI/180), ch4_hsize, ch4_size*-cos(202.5*PI/180)},
	{ch4_size*sin(225*PI/180), ch4_hsize, ch4_size*-cos(225*PI/180)},
	{ch4_size*sin(247.5*PI/180), ch4_hsize, ch4_size*-cos(247.5*PI/180)},
	{ch4_size*sin(270*PI/180), ch4_hsize, ch4_size*-cos(270*PI/180)},
	{ch4_size*sin(292.5*PI/180), ch4_hsize, ch4_size*-cos(292.5*PI/180)},
	{ch4_size*sin(315*PI/180), ch4_hsize, ch4_size*-cos(315*PI/180)},
	{ch4_size*sin(337.5*PI/180), ch4_hsize, ch4_size*-cos(337.5*PI/180)},
	{ch4_size*sin(0*PI/180), ch4_hsize, ch4_size*-cos(0*PI/180)},
};

GLfloat cat_head_5[][3] =
{
	{0, ch5_hsize, 0},
	{0, 0, 0},
};

class Head
{
private :
	float eye_time;
public :
	Head()
	{
		eye_time = 0;
	}

	void ear_poly(int a, int b, int c)
	{
		VECTOR normal1;
		{
			VECTOR v1(cat_ear[a],cat_ear[b]),v2(cat_ear[a],cat_ear[c]);
			Cross_Product(v1,v2,normal1);
		}
		//glEnable(GL_TEXTURE_2D);
		//glColor3f(1.0f,1.0f,1.0f);// white !
		glBindTexture(GL_TEXTURE_2D, text_cat_head[0]);	
		glBegin(GL_POLYGON);
		{
			glNormal3f(normal1.x,normal1.y,normal1.z);
			glTexCoord2f(0.45,0); 
			glVertex3fv(cat_ear[a]);
			glTexCoord2f(0.55, 0); 
			glVertex3fv(cat_ear[b]);
			glTexCoord2f(0.50,0.1); 
			glVertex3fv(cat_ear[c]);
		}
		glEnd();
		//glDisable(GL_TEXTURE_2D);
	}

	void polygon1(int b, int a, int face)
	{
		VECTOR normal0, normal0_1;
		{
			VECTOR v1(cat_head_0[b],cat_head_1[b]),v2(cat_head_0[b],cat_head_1[a]),v3(cat_head_0[b],cat_head_0[a]);
			Cross_Product(v1,v2,normal0);
			Cross_Product(v2,v3,normal0_1);
		}
		VECTOR normal1, normal1_1;
		{
			VECTOR v1(cat_head_1[b],cat_head_2[b]),v2(cat_head_1[b],cat_head_2[a]),v3(cat_head_1[b],cat_head_1[a]);
			Cross_Product(v1,v2,normal1);
			Cross_Product(v2,v3,normal1_1);
		}
		VECTOR normal2, normal2_1;
		{
			VECTOR v1(cat_head_2[b],cat_head_3[b]),v2(cat_head_2[b],cat_head_3[a]),v3(cat_head_2[b],cat_head_2[a]);
			Cross_Product(v1,v2,normal2);
			Cross_Product(v2,v3,normal2_1);
		}
		VECTOR normal3, normal3_1;
		{
			VECTOR v1(cat_head_3[b],cat_head_4[b]),v2(cat_head_3[b],cat_head_4[a]),v3(cat_head_3[b],cat_head_3[a]);
			Cross_Product(v1,v2,normal3);
			Cross_Product(v2,v3,normal3_1);
		}
		VECTOR normal4;
		{
			VECTOR v1(cat_head_4[a],cat_head_4[b]),v2(cat_head_4[a],cat_head_5[0]);
			Cross_Product(v1,v2,normal4);
		}
		VECTOR normal5;
		{
			VECTOR v1(cat_head_0[b],cat_head_0[a]),v2(cat_head_0[b],cat_head_5[1]);
			Cross_Product(v1,v2,normal5);
		}
		float c0 = sqrt(pow(cat_head_0[b][0] - cat_head_0[a][0], 2)+pow(cat_head_0[b][1] - cat_head_0[a][1], 2)+pow(cat_head_0[b][2] - cat_head_0[a][2], 2))/2;
		float c1 = sqrt(pow(cat_head_1[b][0] - cat_head_1[a][0], 2)+pow(cat_head_1[b][1] - cat_head_1[a][1], 2)+pow(cat_head_1[b][2] - cat_head_1[a][2], 2))/2;
		float c2 = sqrt(pow(cat_head_2[b][0] - cat_head_2[a][0], 2)+pow(cat_head_2[b][1] - cat_head_2[a][1], 2)+pow(cat_head_2[b][2] - cat_head_2[a][2], 2))/2;
		float c3 = sqrt(pow(cat_head_3[b][0] - cat_head_3[a][0], 2)+pow(cat_head_3[b][1] - cat_head_3[a][1], 2)+pow(cat_head_3[b][2] - cat_head_3[a][2], 2))/2;
		float c4 = sqrt(pow(cat_head_4[b][0] - cat_head_4[a][0], 2)+pow(cat_head_4[b][1] - cat_head_4[a][1], 2)+pow(cat_head_4[b][2] - cat_head_4[a][2], 2))/2;
		
		float c01 = c1/c0;
		float c12 = c2/c1;
		float c23 = c3/c2;
		float c34 = c4/c3;
		
		//glEnable(GL_TEXTURE_2D);
		//glColor3f(1.0f,1.0f,1.0f);// white !
		eye_time = eye_time + 0.002;
		if(face == 0)
		{
			if(eye_time > 3 && eye_time <= 3.5)
			{
				glBindTexture(GL_TEXTURE_2D, text_cat_head[1]);
			}
			else if(eye_time > 7 && eye_time <= 7.5)
			{
				glBindTexture(GL_TEXTURE_2D, text_cat_head[1]);
			}
			else if(eye_time > 8 && eye_time <= 8.5)
			{
				glBindTexture(GL_TEXTURE_2D, text_cat_head[1]);
			}
			else if(eye_time > 8.5)
			{
				glBindTexture(GL_TEXTURE_2D, text_cat_head[0]);
				eye_time = 0;
			}
			else
			{
				glBindTexture(GL_TEXTURE_2D, text_cat_head[0]);
			}
		}
		else if(face == 1)
		{
			glBindTexture(GL_TEXTURE_2D, text_cat_head[3]);
		}
		else if(face == 2)
		{
			glBindTexture(GL_TEXTURE_2D, text_cat_head[4]);
		}
		else if(face == 3)
		{
			glBindTexture(GL_TEXTURE_2D, text_cat_head[5]);
		}
		else if(face == 4)
		{
			glBindTexture(GL_TEXTURE_2D, text_cat_head[1]);
		}


		glBegin(GL_TRIANGLES);
		{
			glNormal3f(normal0.x,normal0.y,normal0.z);
			glTexCoord2f((float)b/16, 0.0f); 
			glVertex3fv(cat_head_0[b]);
			glTexCoord4f((float)b/16*c01, ch1_hsize/ch5_hsize*c01, 0, c01); 
			glVertex3fv(cat_head_1[b]);
			glTexCoord4f((float)a/16*c01, ch1_hsize/ch5_hsize*c01, 0, c01); 
			glVertex3fv(cat_head_1[a]);
		}
		glEnd();
		glBegin(GL_TRIANGLES);
		{
			glNormal3f(normal0_1.x,normal0_1.y,normal0_1.z);
			glTexCoord2f((float)b/16, 0.0f); 
			glVertex3fv(cat_head_0[b]);
			glTexCoord4f((float)a/16*c01, ch1_hsize/ch5_hsize*c01, 0, c01); 
			glVertex3fv(cat_head_1[a]);
			glTexCoord2f((float)a/16, 0.0f); 
			glVertex3fv(cat_head_0[a]);
		}
		glEnd();

		glBegin(GL_TRIANGLES);
		{
			glNormal3f(normal1.x,normal1.y,normal1.z);
			glTexCoord2f((float)b/16, ch1_hsize/ch5_hsize); 
			glVertex3fv(cat_head_1[b]);
			glTexCoord4f((float)b/16*c12, ch2_hsize/ch5_hsize*c12, 0, c12); 
			glVertex3fv(cat_head_2[b]);
			glTexCoord4f((float)a/16*c12, ch2_hsize/ch5_hsize*c12, 0, c12); 
			glVertex3fv(cat_head_2[a]);
		}
		glEnd();
		
		glBegin(GL_TRIANGLES);
		{
			glNormal3f(normal1_1.x,normal1_1.y,normal1_1.z);
			glTexCoord2f((float)b/16, ch1_hsize/ch5_hsize); 
			glVertex3fv(cat_head_1[b]);
			glTexCoord4f((float)a/16*c12, ch2_hsize/ch5_hsize*c12, 0, c12); 
			glVertex3fv(cat_head_2[a]);
			glTexCoord2f((float)a/16, ch1_hsize/ch5_hsize); 
			glVertex3fv(cat_head_1[a]);
		}
		glEnd();

		glBegin(GL_TRIANGLES);
		{
			glNormal3f(normal2.x,normal2.y,normal2.z);
			glTexCoord2f((float)b/16, ch2_hsize/ch5_hsize); 
			glVertex3fv(cat_head_2[b]);
			glTexCoord4f((float)b/16*c23, ch3_hsize/ch5_hsize*c23, 0, c23); 
			glVertex3fv(cat_head_3[b]);
			glTexCoord4f((float)a/16*c23, ch3_hsize/ch5_hsize*c23, 0, c23); 
			glVertex3fv(cat_head_3[a]);
		}
		glEnd();

		glBegin(GL_TRIANGLES);
		{
			glNormal3f(normal2_1.x,normal2_1.y,normal2_1.z);
			glTexCoord2f((float)b/16, ch2_hsize/ch5_hsize); 
			glVertex3fv(cat_head_2[b]);
			glTexCoord4f((float)a/16*c23, ch3_hsize/ch5_hsize*c23, 0, c23); 
			glVertex3fv(cat_head_3[a]);
			glTexCoord2f((float)a/16, ch2_hsize/ch5_hsize); 
			glVertex3fv(cat_head_2[a]);
		}
		glEnd();

		glBegin(GL_TRIANGLES);
		{
			glNormal3f(normal3.x,normal3.y,normal3.z);
			glTexCoord2f((float)b/16, ch3_hsize/ch5_hsize); 
			glVertex3fv(cat_head_3[b]);
			glTexCoord4f((float)b/16*c34, ch4_hsize/ch5_hsize*c34, 0, c34); 
			glVertex3fv(cat_head_4[b]);
			glTexCoord4f((float)a/16*c34, ch4_hsize/ch5_hsize*c34, 0, c34); 
			glVertex3fv(cat_head_4[a]);
		}
		glEnd();
		glBegin(GL_TRIANGLES);
		{
			glNormal3f(normal3_1.x,normal3_1.y,normal3_1.z);
			glTexCoord2f((float)b/16, ch3_hsize/ch5_hsize); 
			glVertex3fv(cat_head_3[b]);
			glTexCoord4f((float)a/16*c34, ch4_hsize/ch5_hsize*c34, 0, c34); 
			glVertex3fv(cat_head_4[a]);
			glTexCoord2f((float)a/16, ch3_hsize/ch5_hsize); 
			glVertex3fv(cat_head_3[a]);
		}
		glEnd();

		glBegin(GL_TRIANGLES);
		{
			glNormal3f(normal4.x,normal4.y,normal4.z);
			glTexCoord2f((float)b/16, ch4_hsize/ch5_hsize); 
			glVertex3fv(cat_head_4[b]);
			glTexCoord4f((float)0.5, ch5_hsize/ch5_hsize,0,1); 
			glVertex3fv(cat_head_5[0]);
			glTexCoord2f((float)a/16, ch4_hsize/ch5_hsize); 
			glVertex3fv(cat_head_4[a]);
		}
		glEnd();
		glBegin(GL_TRIANGLES);
		{
			glNormal3f(normal5.x,normal5.y,normal5.z);
			glTexCoord2f((float)b/16, 0); 
			glVertex3fv(cat_head_0[b]);
			glTexCoord2f((float)a/16, 0); 
			glVertex3fv(cat_head_0[a]);
			glTexCoord4f((float)0.5, 0,0,1); 
			glVertex3fv(cat_head_5[1]);
		}
		glEnd();
		
		//glDisable(GL_TEXTURE_2D);
	}
	
	void mus_poly(int a, int b, int c, int d)
	{
		
		VECTOR normal1;
		{
			VECTOR v1(cat_mus[a],cat_mus[b]),v2(cat_mus[a],cat_mus[d]);
			Cross_Product(v1,v2,normal1);
		}
		//glEnable(GL_TEXTURE_2D);
		//glColor3f(1.0f,1.0f,1.0f);// white !
		glBindTexture(GL_TEXTURE_2D, text_cat_head[0]);	
		glBegin(GL_POLYGON);
		{
			glNormal3f(normal1.x,normal1.y,normal1.z);
			glTexCoord2f(0.45,0); 
			glVertex3fv(cat_mus[a]);
			glTexCoord2f(0.45, 0.1); 
			glVertex3fv(cat_mus[b]);
			glTexCoord2f(0.55,0.1); 
			glVertex3fv(cat_mus[c]);
			glTexCoord2f(0.55,0); 
			glVertex3fv(cat_mus[d]);
		}
		glEnd();
		//glDisable(GL_TEXTURE_2D);
	}

	void ear_draw()
	{
		glPushMatrix();
			ear_poly(0,1,2);
			ear_poly(0,2,3);
			ear_poly(2,1,3);
		glPopMatrix();
	}
	void mus_draw()
	{		
		glPushMatrix();
			mus_poly(0,3,2,1);
			mus_poly(1,2,6,5);
			mus_poly(4,5,6,7);
			mus_poly(0,4,7,3);
			mus_poly(3,7,6,2);
			mus_poly(0,1,5,4);
		glPopMatrix();	
	}
	void head_draw(int face)
	{	
		glPushMatrix();
			polygon1(0,1,face);
			polygon1(1,2,face);
			polygon1(2,3,face);
			polygon1(3,4,face);
			polygon1(4,5,face);
			polygon1(5,6,face);
			polygon1(6,7,face);
			polygon1(7,8,face);
			polygon1(8,9,face);
			polygon1(9,10,face);
			polygon1(10,11,face);
			polygon1(11,12,face);
			polygon1(12,13,face);
			polygon1(13,14,face);
			polygon1(14,15,face);
			polygon1(15,16,face);
		glPopMatrix();
		glPushMatrix();	
			glTranslatef(-30, 17, 20);
			glRotatef(-5,0,0,1);
			mus_draw();
		glPopMatrix();	
		glPushMatrix();	
			glTranslatef(-30, 12, 20);
			glRotatef(5,0,0,1);
			mus_draw();
		glPopMatrix();	
		glPushMatrix();	
			glTranslatef(30, 17, 20);
			glRotatef(5,0,0,1);
			mus_draw();
		glPopMatrix();	
		glPushMatrix();	
			glTranslatef(30, 12, 20);
			glRotatef(-5,0,0,1);
			mus_draw();
		glPopMatrix();	
		glPushMatrix();
			glTranslatef(20, 50, 0);
			glRotatef(-20,0,0,1);
			ear_draw();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-20, 50, 0);
			glRotatef(20,0,0,1);
			ear_draw();
		glPopMatrix();
	}
	void draw(int face)
	{
		glPushMatrix();
			glTranslatef(0,50,0);
			head_draw(face);
		glPopMatrix();
	}
};

#endif