#ifndef __CHOBJ__
#define __CHOBJ__
#include <stdio.h>

/*
	trs와 trs1의 거리를 구해줌
	0 : y축을 법선 벡터로 하는 경우 - OpenGL
	1 : z축을 법선 벡터로 하는 경우 - OpenCV
	2 : 3차원 좌표에서의 거리
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
	trs와 trs1의 방향벡터를 구하고
	구한 방향벡터를 가지고 
	trs의 방향벡터인 rot와의 각을 구함
*/
void obj_angle(float *trs,  float *rot, float *trs1, float *rot1)
{
	trs[3] = obj_distance(trs, trs1,0); //오브젝트 사이의 거리 계산
	CQuaternion q; //쿼터니언객체 생성
	float qt_rad[4];
	float qt[3] = {0, 0, 0};
	qt_rad[0] = rot[0];
	qt_rad[1] = rot[1];
	qt_rad[2] = rot[2];
	VECTOR normal(trs, trs1); //trs->trs1 사이의 방향벡터
	VECTOR normal2(trs, rot); //trs->rot 사이의 방향벡터
	GLfloat matrix2[16]; //쿼터니언을 통한 회전변환 행렬 저장
	/*
		쿼터니언을 통한 회전변환을 하는 이유는
		acos함수가 0~180의 값만 반환하기 때문에 
		반환되는 값이 180도를 넘는 값인지 아닌지 구분하기 위해서
		쿼터니언을 통해 방향벡터 rot를 90도 회전 시킨뒤 
		회전시킨 qt_rad를 normal과 각을 acos를 이용해 구해서
		그 값이 90도가 넘으면 normal2와 normal의 값은 180도가 넘는 것을 알 수 있음
	*/
	q.CreateFromAxisAngle(0,1,0,-90); //y축을 기준으로 왼쪽 회전 연산
	q.CreateMatrix(matrix2); //회전된 값을 행렬로 만듬

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