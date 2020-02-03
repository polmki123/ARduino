#ifndef __OBJDRAW__
#define __OBJDRAW__
#include <gl/glut.h>

float obj_box_size = 30;


GLfloat obj_box[][3] = 
{ 
	{-obj_box_size, -obj_box_size, -obj_box_size},
	{obj_box_size, -obj_box_size, -obj_box_size},
	{obj_box_size, obj_box_size, -obj_box_size},
	{-obj_box_size, obj_box_size, -obj_box_size},
	{-obj_box_size, -obj_box_size, obj_box_size},
	{obj_box_size, -obj_box_size, obj_box_size},
	{obj_box_size, obj_box_size, obj_box_size},
	{-obj_box_size, obj_box_size, obj_box_size},
};
/* obj_box[][] 꼭지점 지정 순서 
* 7 팔분면체 꼭지점 (z<0) obj_box[0]
* 8 팔분면체 꼭지점 (z<0) obj_box[1]
* 5 팔분면체 꼭지점 (z<0) obj_box[2]
* 6 팔분면체 꼭지점 (z<0) obj_box[3]
* 3 팔분면체 꼭지점 (z>0) obj_box[4]
* 4 팔분면체 꼭지점 (z>0) obj_box[5]
* 1 팔분면체 꼭지점 (z>0) obj_box[6]
* 2 팔분면체 꼭지점 (z>0) obj_box[7]
*/

float plat[][3] = 
{
	{-20, 0, 20},
	{20, 0, 20},
	{20, 0, -20},
	{-20, 0, -20},
};

class Box
{
public :
	float trs[3];
	float ar_trs[3];
	float rot[4];
	float len;
	int check, obj_num, ro_end;
	Box(float x, float y, float z)
	{
		trs[0] = x;
		trs[1] = y;
		trs[2] = z;
		ar_trs[0] = 0;
		ar_trs[1] = 0;
		ar_trs[2] = 0;
		rot[0] = 0;
		rot[1] = 0;
		rot[2] = 1;
		check = 0;
		ro_end = 1;
	}

	void box_poly(int a, int b, int c , int d)
	{
		
		VECTOR normal1;
		{
			VECTOR v1(obj_box[a],obj_box[b]),v2(obj_box[a],obj_box[c]);
			Cross_Product(v1,v2,normal1);
		}
		VECTOR normal2;
		{
			VECTOR v1(obj_box[a],obj_box[c]),v2(obj_box[a],obj_box[d]);
			Cross_Product(v1,v2,normal2);
		}
		glBegin(GL_TRIANGLES);
		{
			glNormal3f(normal1.x,normal1.y,normal1.z);
			glVertex3fv(obj_box[a]);
			glVertex3fv(obj_box[b]);
			glVertex3fv(obj_box[c]);
		}
		glEnd();
		glBegin(GL_TRIANGLES);
		{
			glNormal3f(normal2.x,normal2.y,normal2.z);
			glVertex3fv(obj_box[a]);
			glVertex3fv(obj_box[c]);
			glVertex3fv(obj_box[d]);
		}
		glEnd();
	}

	void plat_poly(int a, int b, int c , int d)
	{
		
		VECTOR normal1;
		{
			VECTOR v1(plat[a],plat[b]),v2(plat[a],plat[c]);
			Cross_Product(v1,v2,normal1);
		}
		VECTOR normal2;
		{
			VECTOR v1(plat[a],plat[c]),v2(plat[a],plat[d]);
			Cross_Product(v1,v2,normal2);
		}
		//glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		//glEnable(GL_TEXTURE_2D);
		//glColor4f(1.0f,1.0f,1.0f,1.0);// white !
		glBindTexture(GL_TEXTURE_2D, text_cat_head[1]);
		glBegin(GL_TRIANGLES);
		{
			glNormal3f(normal1.x,normal1.y,normal1.z);
			glTexCoord2f(0, 0); 
			glVertex3fv(plat[a]);
			glTexCoord2f(1, 0); 
			glVertex3fv(plat[b]);
			glTexCoord2f(1, 1); 
			glVertex3fv(plat[c]);
		}
		glEnd();
		glBegin(GL_TRIANGLES);
		{
			glNormal3f(normal2.x,normal2.y,normal2.z);
			glTexCoord2f(0, 0); 
			glVertex3fv(plat[a]);
			glTexCoord2f(1, 1); 
			glVertex3fv(plat[c]);
			glTexCoord2f(0, 1); 
			glVertex3fv(plat[d]);
		}
		glEnd();
		//glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
	}

	void box_draw(float *cm_t, float *cm_r)
	{
		obj_angle(cm_t, cm_r, ar_trs, rot); //박스와 매개변수와의 각도를 계산하여 rot[3]에 저장
		glPushMatrix();
			glTranslatef(trs[0], trs[1], trs[2]);	// Place base of cube on marker surface.
			glRotatef(90,1,0,0);					// artoolkit의 좌표와 연동되도록 회전
			box_poly(0,3,2,1);						// 밑면 (7,6,5,8 팔분면체 위 꼭지점으로 이루어진)
			box_poly(5,6,7,4);						// 윗면 (4,1,2,3 팔분면체 위 꼭지점으로 이루어진)
			box_poly(1,2,6,5);						// 옆면1(8,5,1,4 팔분면체 위 꼭지점으로 이루어진)
			box_poly(4,7,3,0);						// 옆면2(3,2,6,7 팔분면체 위 꼭지점으로 이루어진)
			box_poly(6,2,3,7);						// 옆면3(1,5,6,2 팔분면체 위 꼭지점으로 이루어진)
			box_poly(4,0,1,5);						// 옆면4(3,7,8,4 팔분면체 위 꼭지점으로 이루어진)
		glPopMatrix();
	}

	void draw_plat()
	{
		glPushMatrix();
			plat_poly(0,1,2,3);
		glPopMatrix();
	}
};

#endif
