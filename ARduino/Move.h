/*
	회전 및 움직임
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
	rot[X] = normal.x + trs[X]; //움직이는 만큼 시점도 수정
	rot[Z] = normal.z + trs[Z];
}
void obj_stand(float *trs, float *rot)
{
	glTranslatef(trs[0], trs[1], trs[2]);
	glRotatef(rot[3],0,1,0);
}

//입력받은 각도 만큼 rot를 회전시켜 줌.
//select_rot의 경우 0과 1이 존재. 0은 실시간연산에 적용되는 회전, 1은 한번만 적용되는 회전에 사용
int obj_rotate(float *trs, float *rot, float rot_rad, int select_rot)
{
	CQuaternion q; //쿼터니언객체 생성
	VECTOR normal(trs, rot); //카메라 시점으로의 방향벡터 생성
	GLfloat matrix1[16]; //쿼터니언을 통한 회전변환 행렬 저장
	
	rot_rad = (int)rot_rad;

	if(rot_rad > 0)
	{
		if(rot_rad >=turn_speed)
		{
			q.CreateFromAxisAngle(0,1,0,-turn_speed); //y축을 기준으로 왼쪽 회전 연산
		}
		else
		{
			q.CreateFromAxisAngle(0,1,0,-rot_rad); //y축을 기준으로 왼쪽 회전 연산
		}
		rad_count += turn_speed;
		q.CreateMatrix(matrix1); //연산된 값을 행렬로 만듬
		rot[X] = normal.x*matrix1[0] + normal.y*matrix1[4] + normal.z*matrix1[8];//연산된 행렬값에 방향벡터를 곱한 값을 시점으로 저장
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
				return 0; //회전연산 중지
			}
			else
			{
				return 1; //회전 계속
			}
		}
		else
		{
			if(rad_count >= rot_rad)
			{
				rad_count = 0;
				return 0; //회전연산 중지
			}
			else
			{
				return 1; //회전 계속
			}
		}
	}
	else
	{		
		if(-rot_rad >= turn_speed)
		{
			q.CreateFromAxisAngle(0,1,0,turn_speed); //y축을 기준으로 왼쪽 회전 연산
		}
		else
		{
			q.CreateFromAxisAngle(0,1,0,-rot_rad); //y축을 기준으로 왼쪽 회전 연산
		}
		//q.CreateFromAxisAngle(0,1,0,turn_speed); //y축을 기준으로 오른쪽 회전 연산
		rad_count -= turn_speed;
		q.CreateMatrix(matrix1); //연산된 값을 행렬로 만듬	
		rot[X] = normal.x*matrix1[0] + normal.y*matrix1[4] + normal.z*matrix1[8];//연산된 행렬값에 방향벡터를 곱한 값을 시점으로 저장
		rot[Z] = normal.x*matrix1[2] + normal.y*matrix1[6] + normal.z*matrix1[10];
		rot[3] = -acos((0*rot[X] + 1*rot[Z])/(sqrt(0.0 + 1.0)*sqrt(rot[X]*rot[X] + rot[Z]*rot[Z])))*180/PI;//glRotate를 위한 값
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
				return 0; //회전연산 중지
			}
			else
			{
				return 1; //회전계속
			}
		}
		else
		{
			if(rad_count <= rot_rad)
			{
				rad_count = 0;
				return 0; //회전연산 중지
			}
			else
			{
				return 1; //회전 계속
			}
		}	
	}
}
#endif
