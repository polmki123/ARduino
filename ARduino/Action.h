/*
	캐릭터의 AI부분
*/

#ifndef __ACTION__
#define __ACTION__
#include <time.h>
#include <gl/glut.h>
float ac_rot = 0;
float ac_time = 0;
float ac_time2 = 0;
float state3_time = 0;
int state3_num = 0;
int ro_end = 0;
int ac_num = 0;
int c_inter = 0;
int state = 0;
int state2 = 0;


Cat_Model cm;			//캐릭터 모델 생성
Box b_draw(0,30,0);		//박스 모덱 생성

/*
	캐릭터가 랜덤으로 움직임
*/
void ac_random()
{
	ac_time = ac_time + 1;
	srand(time(NULL));
	if(ac_time > 100)
	{
		ac_num = rand()%10;
		ac_rot = 15+rand()%90;
		ac_time = 0;
		cm.trs[3] = 50;
	}
	if(ac_num == 0 || ac_num == 5)
	{
		cm.stand();
	}
	else if(ac_num == 1 || ac_num == 6)
	{
		ro_end = cm.rotate(-ac_rot,1);
		cm.stand();
		if(ro_end == 0)
		{
			ac_time = 300;
			ro_end = 1;
			ac_num = 0;
		}
		else
		{
			ac_time = 10;
		}

	}
	else if(ac_num == 2 || ac_num == 7)
	{
		ro_end = cm.rotate(ac_rot,1);
		cm.stand();
		if(ro_end == 0)
		{
			ac_time = 300;
			ro_end = 1;
			ac_num = 0;
		}
		else
		{
			ac_time = 10;
		}
	}
	else if(ac_num == 3)
	{
		cm.run();
	}
	else
	{
		cm.walk();
	}
}

/*
	캐릭터가 박스를 찾아 움직임
*/
void ac_find_box()
{
	cm.rotate(b_draw.rot[3], 0);
	if(cm.trs[3] > 200)
	{
		cm.run();
		cm.catch_state = 0;
	}
	else if(cm.trs[3] < 60 && b_draw.ar_trs[1] < 100)
	{
		cm.catch_ac();
	}
	
	else if(cm.trs[3] < 60 && b_draw.ar_trs[1] >= 100)
	{
		cm.handup();
	}
	else
	{
		cm.walk();
		cm.catch_state = 0;
	}
}

/*
	캐릭터가 마커를 찾아 움직임
*/
void ac_find_marker(ObjectData_T *marker)
{
	cm.rotate(marker->ar_rot[3], 0);
	if(cm.trs[3] > 200)
	{
		cm.run();
		cm.catch_state = 0;
	}
	else if(cm.trs[3] < 60 && marker->ar_trs[1] < 100)
	{
		cm.bubi();
	}
	else if(cm.trs[3] < 60 && marker->ar_trs[1] >= 100)
	{
		cm.handup();
	}
	else
	{
		cm.walk();
		cm.catch_state = 0;
	}
}

/*
	state 상태에 따른 캐릭터의 움직임이 달라짐
	state = 0 : 랜덤으로 돌아다님
	state = 1 : 박스를 찾아 다님
	state = 2 : 색상 마커를 찾아 다님
	state = 3 : 2개의 색상 마커를 인식
*/
void ac_action()
{
	if(state == 0)
	{
		c_inter = 0;
		cm.trs[1] = 32;
		ac_random();
	}
	else if(state == 1)
	{
		
		c_inter = 0;
		cm.trs[1] = 32;
		ac_find_box();
	}
	else if(state == 2)
	{
		
		c_inter = 0;
		cm.trs[1] = 32;
		if(Col_marker[0].ar_trs[1] < 100)
		{
			ac_find_marker(&Col_marker[0]);
		}
		else if(state2 == 1 || Col_marker[0].ar_trs[1] < 200 && Col_marker[0].ar_trs[1] >= 100 && obj_distance(cm.trs, Col_marker[0].ar_trs, 0) < 70)
		{
			//VECTOR normal(cm.trs, Col_marker[0].ar_trs);
			state2 = cm.side_left();
		}
		else
		{
			cm.stand();
		}
	}
	else if(state == 3)
	{
		float dist = Col_marker[0].ar_trs[0] - Col_marker[1].ar_trs[0];//= obj_distance(Col_marker[0].ar_trs, Col_marker[1].ar_trs, 0); //마커사이 거리
		float c_dist = obj_distance(cm.trs, Col_marker[0].ar_trs, 0); //캐릭터와 마커사이 거리
		srand(time(NULL));
		state3_time += 1;
		if(state3_time > 100)
		{
			state3_num = rand()%2;
			state3_time = 0;
		}
		if(dist < 120 && Col_marker[0].ar_trs[1] < 200 && c_dist < 200 && c_inter == 0)
		{
			cm.trs[0] = Col_marker[0].ar_trs[0];
			cm.trs[1] = Col_marker[0].ar_trs[1] - 32;
			cm.trs[2] = Col_marker[0].ar_trs[2];
			cm.rot[X] += cm.trs[X]; //움직이는 만큼 시점도 수정
			cm.rot[Z] += cm.trs[Z];
			cm.drop_1();
			c_inter = 1;
			//ac_up_char(&R_marker);
		}
		else if(dist < 120 && c_inter == 1)
		{
			cm.trs[0] = Col_marker[0].ar_trs[0];
			cm.trs[1] = Col_marker[0].ar_trs[1] - 32;
			cm.trs[2] = Col_marker[0].ar_trs[2];
			cm.rot[X] += cm.trs[X]; //움직이는 만큼 시점도 수정
			cm.rot[Z] += cm.trs[Z];
			if(state3_num == 0)
			{
				cm.drop_1();
			}
			else
			{
				cm.drop_2();
			}
		}
		else if(dist >= 120 && c_inter == 1)
		{
			c_inter = 0;
			cm.stand();
		}
		else
		{
			cm.trs[1] = 32;
			c_inter = 0;
			cm.stand();
		}
	}
}

/*
	박스를 그려줌
*/
void ac_box() 
{
	b_draw.box_draw(cm.trs, cm.rot);
}

#endif
