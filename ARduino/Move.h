/*
	ȸ�� �� ������
*/
#ifndef __MOVE__
#define __MOVE__
#include <gl/glut.h>
float rad;
float rad_count = 0;
float turn_speed = 5;
void obj_move(float *trs, float *rot, float move_speed)
{
	VECTOR normal(trs, rot);	//
	trs[X] += normal.x*move_speed; //
	trs[Z] += normal.z*move_speed;
	rot[X] = normal.x + trs[X]; //�����̴� ��ŭ ������ ����
	rot[Z] = normal.z + trs[Z];
}
void obj_stand(float *trs, float *rot)
{
	glTranslatef(trs[0], trs[1], trs[2]);
	glRotatef(rot[3],0,1,0);
}

//�Է¹��� ���� ��ŭ rot�� ȸ������ ��.
//select_rot�� ��� 0�� 1�� ����. 0�� �ǽð����꿡 ����Ǵ� ȸ��, 1�� �ѹ��� ����Ǵ� ȸ���� ���
int obj_rotate(float *trs, float *rot, float rot_rad, int select_rot)
{
	CQuaternion q; //���ʹϾ�ü ����
	VECTOR normal(trs, rot); //ī�޶� ���������� ���⺤�� ����
	GLfloat matrix1[16]; //���ʹϾ��� ���� ȸ����ȯ ��� ����
	
	rot_rad = (int)rot_rad;

	if(rot_rad > 0)
	{
		if(rot_rad >=turn_speed)
		{
			q.CreateFromAxisAngle(0,1,0,-turn_speed); //y���� �������� ���� ȸ�� ����
		}
		else
		{
			q.CreateFromAxisAngle(0,1,0,-rot_rad); //y���� �������� ���� ȸ�� ����
		}
		rad_count += turn_speed;
		q.CreateMatrix(matrix1); //����� ���� ��ķ� ����
		rot[X] = normal.x*matrix1[0] + normal.y*matrix1[4] + normal.z*matrix1[8];//����� ��İ��� ���⺤�͸� ���� ���� �������� ����
		rot[Z] = normal.x*matrix1[2] + normal.y*matrix1[6] + normal.z*matrix1[10];
		rot[3] = acos((0.0*rot[X] + 1.0*rot[Z])/(sqrt(0.0 + 1.0)*sqrt(rot[X]*rot[X] + rot[Z]*rot[Z])))*180.0/PI;
		
		if(rot[X] <= 0)
		{
			rot[3] = 360.0 - rot[3];
		}
		rot[X] += trs[X];
		rot[Z] += trs[Z];
		if(select_rot == 0)
		{
			if(rot_rad < 1 && rot_rad > -1)
			{
				rad_count = 0;
				return 0; //ȸ������ ����
			}
			else
			{
				return 1; //ȸ�� ���
			}
		}
		else
		{
			if(rad_count >= rot_rad)
			{
				rad_count = 0;
				return 0; //ȸ������ ����
			}
			else
			{
				return 1; //ȸ�� ���
			}
		}
	}
	else
	{		
		if(-rot_rad >= turn_speed)
		{
			q.CreateFromAxisAngle(0,1,0,turn_speed); //y���� �������� ���� ȸ�� ����
		}
		else
		{
			q.CreateFromAxisAngle(0,1,0,-rot_rad); //y���� �������� ���� ȸ�� ����
		}
		//q.CreateFromAxisAngle(0,1,0,turn_speed); //y���� �������� ������ ȸ�� ����
		rad_count -= turn_speed;
		q.CreateMatrix(matrix1); //����� ���� ��ķ� ����	
		rot[X] = normal.x*matrix1[0] + normal.y*matrix1[4] + normal.z*matrix1[8];//����� ��İ��� ���⺤�͸� ���� ���� �������� ����
		rot[Z] = normal.x*matrix1[2] + normal.y*matrix1[6] + normal.z*matrix1[10];
		rot[3] = -acos((0*rot[X] + 1*rot[Z])/(sqrt(0.0 + 1.0)*sqrt(rot[X]*rot[X] + rot[Z]*rot[Z])))*180/PI;//glRotate�� ���� ��
		if(rot[X] >= 0)
		{
			rot[3] = -rot[3];
		}
		rot[X] += trs[X];
		rot[Z] += trs[Z];
		if(select_rot == 0)
		{
			if(rot_rad < 1 && rot_rad > -1)
			{
				rad_count = 0;
				return 0; //ȸ������ ����
			}
			else
			{
				return 1; //ȸ�����
			}
		}
		else
		{
			if(rad_count <= rot_rad)
			{
				rad_count = 0;
				return 0; //ȸ������ ����
			}
			else
			{
				return 1; //ȸ�� ���
			}
		}	
	}
}
#endif
