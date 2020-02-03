#ifndef __CHOBJ__
#define __CHOBJ__
#include <stdio.h>

/*
	trs�� trs1�� �Ÿ��� ������
	0 : y���� ���� ���ͷ� �ϴ� ��� - OpenGL
	1 : z���� ���� ���ͷ� �ϴ� ��� - OpenCV
	2 : 3���� ��ǥ������ �Ÿ�
*/
float obj_distance(float *trs, float *trs1, int i)
{
	if(i == 0)
	{
		return sqrt((trs[0]-trs1[0])*(trs[0]-trs1[0]) + (trs[2]-trs1[2])*(trs[2]-trs1[2]));
	}
	else if(i == 1)
	{
		return sqrt((trs[0]-trs1[0])*(trs[0]-trs1[0]) + (trs[1]-trs1[1])*(trs[1]-trs1[1]));
	}
	else if(i == 2)
	{
		return sqrt((trs[0]-trs1[0])*(trs[0]-trs1[0]) + (trs[1]-trs1[1])*(trs[1]-trs1[1]) + (trs[2]-trs1[2])*(trs[2]-trs1[2]));
	}
	return 1000;
}

/*
	trs�� trs1�� ���⺤�͸� ���ϰ�
	���� ���⺤�͸� ������ 
	trs�� ���⺤���� rot���� ���� ����
*/
void obj_angle(float *trs,  float *rot, float *trs1, float *rot1)
{
	trs[3] = obj_distance(trs, trs1,0); //������Ʈ ������ �Ÿ� ���
	CQuaternion q; //���ʹϾ�ü ����
	float qt_rad[4];
	float qt[3] = {0, 0, 0};
	qt_rad[0] = rot[0];
	qt_rad[1] = rot[1];
	qt_rad[2] = rot[2];
	VECTOR normal(trs, trs1); //trs->trs1 ������ ���⺤��
	VECTOR normal2(trs, rot); //trs->rot ������ ���⺤��
	GLfloat matrix2[16]; //���ʹϾ��� ���� ȸ����ȯ ��� ����
	/*
		���ʹϾ��� ���� ȸ����ȯ�� �ϴ� ������
		acos�Լ��� 0~180�� ���� ��ȯ�ϱ� ������ 
		��ȯ�Ǵ� ���� 180���� �Ѵ� ������ �ƴ��� �����ϱ� ���ؼ�
		���ʹϾ��� ���� ���⺤�� rot�� 90�� ȸ�� ��Ų�� 
		ȸ����Ų qt_rad�� normal�� ���� acos�� �̿��� ���ؼ�
		�� ���� 90���� ������ normal2�� normal�� ���� 180���� �Ѵ� ���� �� �� ����
	*/
	q.CreateFromAxisAngle(0,1,0,-90); //y���� �������� ���� ȸ�� ����
	q.CreateMatrix(matrix2); //ȸ���� ���� ��ķ� ����

	qt_rad[X] = normal2.x*matrix2[0] + normal2.y*matrix2[4] + normal2.z*matrix2[8];
	qt_rad[Z] = normal2.x*matrix2[2] + normal2.y*matrix2[6] + normal2.z*matrix2[10];
	qt_rad[3] = acos((qt_rad[X]*normal.x + qt_rad[Z]*normal.z)/(sqrt(qt_rad[X]*qt_rad[X] + qt_rad[Z]*qt_rad[Z])*sqrt(normal.x*normal.x + normal.z*normal.z)))*180.0/PI;
	if(qt_rad[3] <= 90)
	{
		rot1[3] = acos((normal2.x*normal.x + normal2.z*normal.z)/(sqrt(normal2.x*normal2.x + normal2.z*normal2.z)*sqrt(normal.x*normal.x + normal.z*normal.z)))*180.0/PI;
	}
	else if(qt_rad[3] > 90)
	{
		rot1[3] = -acos((normal2.x*normal.x + normal2.z*normal.z)/(sqrt(normal2.x*normal2.x + normal2.z*normal2.z)*sqrt(normal.x*normal.x + normal.z*normal.z)))*180.0/PI;
	}
}

#endif