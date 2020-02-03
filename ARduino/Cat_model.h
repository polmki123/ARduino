/*
	캐릭터를 종합하여 그려주고
	애니메이션 설정
*/
#ifndef __CAT_MODEL__
#define __CAT_MODEL__
#include <gl/glut.h>
#include "Texture.h"
#include "Head.h"
#include "Body.h"
#include "Arms.h"
#include "Legs.h"
#include "Tail.h"
#include "Move.h"
#include "Shadow.h"

class Cat_Model
{
private :
	Head hh;//각 부분의 객체를 생성
	Body bb;
	Arms aa;
	Legs ll;
	Tail tt;
	float stand_time; //Stand 애니메이션 시간 저장변수
	float walk_time; //Walk 애니메이션 시간 저장 변수
	float run_time;
	float catch1_time;
	float catch2_time;
	float catch3_time;
	float catch2_tt;
	float handup_time;
	float side_time;
	float bubi_time;
	float drop_time;
	int select; //회전 on off(1 = on, 0 = off)
	int h_select;
	SOUND_UTIL step_sound;
	SOUND_UTIL drop_sound;
	SOUND_UTIL side_sound;
public :
	float trs[5]; //위치저장
	float rot[4]; //회전방향저장
	int catch_state;
	Cat_Model()
	{
		select = 1;
		h_select = 1;
		//rad = 0;
		stand_time = 0;
		walk_time = 0;
		run_time = 0;
		catch1_time = 0;
		catch2_time = 0;
		catch3_time = 0;
		catch2_tt = 1;
		catch_state = 0;
		handup_time = 0;
		side_time = 0;
		bubi_time = 0;
		drop_time = 0;
		step_sound.Init_Sound(1,"Data\\data\\step_1.wav");
		drop_sound.Init_Sound(1,"Data\\data\\drop.mp3");
		side_sound.Init_Sound(1,"Data\\data\\side.mp3");
		trs[0] = 0;
		trs[1] = 32;
		trs[2] = 0;
		trs[3] = 20; //물체와의 거리 (10이하일경우 앞으로 전진X)
		trs[4] = 0; //물체와의 거리 (10이하일경우 앞으로 전진X)
		rot[0] = trs[0];
		rot[1] = trs[1];
		rot[2] = trs[2]+1;
		rot[3] = 0; //glRotate를 위한 회전 각도 초기값 0
	}

	//------------------------------------------STAND-----------------------------------------------
	void stand() //stand의 최종 통합
	{		
		stand_time += 10; //함수호출마다 10씩 증가(애니메이션의 기초)
		glPushMatrix();
			glRotatef(180,0,0,1);			
			glRotatef(90,1,0,0); //artoolkit의 좌표와 연동되도록 회전
			glPushMatrix(); //그림자 스택
				glDisable(GL_LIGHTING); //라이팅 끔
				glDisable(GL_DEPTH_TEST); //깊이 체크 끔
				glColor3f(0.3,0.3,0.3); //그림자 색상(회색)
				glDisable(GL_TEXTURE_2D); //텍스쳐 끔
				glShadowProjectionPOINT(sun_position, planePoint, planeNormal); //(광원위치, 몰라, 몰라)
				orgin_stand();
				glColor3f(1,1,1);
				glEnable(GL_LIGHTING);
				glEnable(GL_TEXTURE);
				glEnable(GL_DEPTH_TEST);
			glPopMatrix();
			glColor3f(1.0f,1.0f,1.0f);// white !
			glEnable(GL_TEXTURE_2D);
			orgin_stand();
		glPopMatrix();
	}

	void orgin_stand()//캐릭터 모델
	{		
		glPushMatrix();
			obj_stand(trs, rot); //현재 캐릭터의 위치값과 방향벡터를 넘겨주어 translate와 rotate 시킴
			legs_stand();
			body_stand();
		glPopMatrix();
		if(stand_time > 36000) //시간은 무한 반복
		{
			stand_time = 0;
		}
	}

	void stand_rotate()
	{		
		stand_time += 10;
		glPushMatrix();
			glPushMatrix(); //그림자 스택
				glDisable(GL_LIGHTING); //라이팅 끔
				glDisable(GL_DEPTH_TEST); //깊이 체크 끔
				glColor3f(0.3,0.3,0.3); //그림자 색상(회색)
				glDisable(GL_TEXTURE_2D); //텍스쳐 끔
				glShadowProjectionPOINT(sun_position, planePoint, planeNormal); //(광원위치, 몰라, 몰라)
				origin_stand_rotate();
				glColor3f(1,1,1);
				glEnable(GL_LIGHTING);
				glEnable(GL_TEXTURE);
				glEnable(GL_DEPTH_TEST);
			glPopMatrix();
			glColor3f(1.0f,1.0f,1.0f);// white !
			glEnable(GL_TEXTURE_2D);
			origin_stand_rotate();
		glPopMatrix();
	}

	void origin_stand_rotate()
	{		
		glPushMatrix();
			obj_stand(trs, rot);
			legs_stand();
			body_stand();
		glPopMatrix();
		if(stand_time > 36000)
		{
			stand_time = 0;
		}
	}
	
	void arms_stand()
	{		
		glPushMatrix();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(16,47,0);
			glRotatef(5*abs(sin(stand_time*PI/180)),0,0,1);
			glRotatef(15,0,0,1);
			aa.arms0_draw();
			glTranslatef(0,-ca_hsize*2,0);
			glRotatef(-5,1,0,0);
			aa.arms1_draw(0);
			glTranslatef(0,-ca_hsize_1*2,0);
			aa.arms1_draw(1);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-16,47,0);
			glRotatef(-5*abs(sin(stand_time*PI/180)),0,0,1);
			glRotatef(-15,0,0,1);
			aa.arms0_draw();
			glTranslatef(0,-ca_hsize*2,0);
			glRotatef(-5,1,0,0);
			aa.arms1_draw(0);
			glTranslatef(0,-ca_hsize_1*2,0);
			aa.arms1_draw(1);
		glPopMatrix();
	}

	void legs_stand()
	{		
		glPushMatrix();
			glTranslatef(-9,0,0);
			glPushMatrix();
				glRotatef(5*sin((stand_time+180)*PI/180),1,0,0);
				glRotatef(-5,1,0,0);
				ll.legs0_draw();
			glPopMatrix();
			glTranslatef(0,-cl_hsize*4,0);
			glRotatef(-5*sin((stand_time+180)*PI/180),1,0,0);
			glRotatef(5,1,0,0);
			glTranslatef(0,cl_hsize*2,0);
			ll.legs0_draw();
			glTranslatef(0,-cl_hsize*2,0);
			ll.legs1_draw();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(9,0,0);
			glPushMatrix();
				glRotatef(5*sin(stand_time*PI/180),1,0,0);
				glRotatef(-5,1,0,0);
				ll.legs0_draw();
			glPopMatrix();
			glTranslatef(0,-cl_hsize*4,0);
			glRotatef(-5*sin(stand_time*PI/180),1,0,0);
			glRotatef(5,1,0,0);
			glTranslatef(0,cl_hsize*2,0);
			ll.legs0_draw();
			glTranslatef(0,-cl_hsize*2,0);
			ll.legs1_draw();
		glPopMatrix();
	}

	void tail_stand()
	{
		glPushMatrix();
			glTranslatef(0,10,-17);
			glRotatef(30,1,0,0);
			glRotatef(-15*sin(stand_time*PI/270+1),1,0,1);
			tt.tail_draw(0);
			glTranslatef(0,-14,0);
			glRotatef(30*cos(stand_time*PI/180+2),1,0,0);
			tt.tail_draw(0);
			glTranslatef(0,-14,0);
			glRotatef(-20*sin(stand_time*PI/180+0.45),1,1,1);
			tt.tail_draw(1);
		glPopMatrix();
	}

	void body_stand()
	{
		glPushMatrix();
			glTranslatef(0,-1*abs(sin(stand_time*PI/180)),0);
			glTranslatef(0,cb1_hsize/2,0);
			glRotatef(5*sin(stand_time*PI/180),0,0,1);
			glTranslatef(0,-cb1_hsize/2,0);
			bb.body_draw();
			glPushMatrix();
				glTranslatef(0,cb1_hsize,0);
				glRotatef(5*sin(stand_time*PI/180),0,0,1);
				glTranslatef(0,-cb1_hsize,0);

				hh.draw(0);
			glPopMatrix();
			arms_stand();
			tail_stand();
		glPopMatrix();
	}

	//------------------------------------------ROTATE----------------------------------------------
	int rotate(float rtt, int i)
	{
		if(select == 1)
		{
			glPushMatrix();
			glRotatef(180,0,0,1);			
			glRotatef(90,1,0,0);
				select = obj_rotate(trs, rot, rtt, i); //select 1 : 회전 계속 0: 회전중지
			glPopMatrix();
			return 1;
		}
		else
		{
			glPushMatrix();
			glRotatef(180,0,0,1);			
			glRotatef(90,1,0,0);
			glPopMatrix();
			select = 1;
			return 0;
		}
	}

	//------------------------------------------WALK-----------------------------------------------
	void walk()
	{	
		walk_time += 10;	
		glPushMatrix();
			glRotatef(180,0,0,1);			
			glRotatef(90,1,0,0);
			glPushMatrix(); //그림자 스택
				glDisable(GL_LIGHTING); //라이팅 끔
				glDisable(GL_DEPTH_TEST); //깊이 체크 끔
				glColor3f(0.3,0.3,0.3); //그림자 색상(회색)
				glDisable(GL_TEXTURE_2D); //텍스쳐 끔
				glShadowProjectionPOINT(sun_position, planePoint, planeNormal); //(광원위치, 몰라, 몰라)
				orgin_walk();
				glColor3f(1,1,1);
				glEnable(GL_LIGHTING);
				glEnable(GL_TEXTURE);
				glEnable(GL_DEPTH_TEST);
			glPopMatrix();
			glColor3f(1.0f,1.0f,1.0f);// white !
			glEnable(GL_TEXTURE_2D);
			orgin_walk();
		glPopMatrix();
		if((int)walk_time % 180 == 0)
		{
			step_sound.Play_Sound();
		}
	}

	void orgin_walk()
	{	
		glPushMatrix();
			obj_stand(trs, rot);
			obj_move(trs, rot, 1);
			body_walk();
		glPopMatrix();
		if(walk_time > 36000)
		{
			walk_time = 0;
		}
	}	
	void arms_walk()
	{		
		//왼손
		glPushMatrix();
			glTranslatef(16,47,0);
			//glRotatef(5*abs(sin(walk_time*PI/180)),0,0,1);
			glRotatef(25,0,0,1);
			glRotatef(-25*sin(walk_time*PI/180),1,0,0);
			aa.arms0_draw();
			glTranslatef(0,-ca_hsize*2,0);
			glRotatef(-20*abs(sin(walk_time*PI/180)),1,0,0);
			aa.arms1_draw(0);
			glTranslatef(0,-ca_hsize_1*2,0);
			glRotatef(-5*abs(sin(walk_time*PI/180)),1,0,0);
			aa.arms1_draw(1);
		glPopMatrix();

		//오른손
		glPushMatrix();
			glTranslatef(-16,47,0);
			//glRotatef(-5*abs(sin(walk_time*PI/180)),0,0,1);
			glRotatef(-25,0,0,1);
			glRotatef(25*sin(walk_time*PI/180),1,0,0);
			aa.arms0_draw();
			glTranslatef(0,-ca_hsize*2,0);
			glRotatef(-20*abs(sin(walk_time*PI/180)),1,0,0);
			aa.arms1_draw(0);
			glTranslatef(0,-ca_hsize_1*2,0);
			glRotatef(-5*abs(sin(walk_time*PI/180)),1,0,0);
			aa.arms1_draw(1);
		glPopMatrix();
	}
	
	void legs_walk()
	{
		//왼발
		glPushMatrix();
			glTranslatef(9,0,0);				
			glRotatef(15*sin(walk_time*PI/180),1,0,0);
			ll.legs0_draw();
			glTranslatef(0,-cl_hsize*2,0);
			glRotatef(35*sin(walk_time*PI/180),1,0,0);
			glRotatef(35,1,0,0);
			ll.legs0_draw();
			glTranslatef(0,-cl_hsize*2,0);
			glRotatef(5*sin(walk_time*PI/180),1,0,0);
			ll.legs1_draw();
		glPopMatrix();

		//오른발
		glPushMatrix();
			glTranslatef(-9,0,0);				
			glRotatef(15*-sin(walk_time*PI/180),1,0,0);
			ll.legs0_draw();
			glTranslatef(0,-cl_hsize*2,0);
			glRotatef(35*-sin(walk_time*PI/180),1,0,0);
			glRotatef(35,1,0,0);
			ll.legs0_draw();
			glTranslatef(0,-cl_hsize*2,0);
			glRotatef(5*sin(walk_time*PI/180),1,0,0);
			ll.legs1_draw();
		glPopMatrix();

	}

	void tail_walk()
	{
		glPushMatrix();
			glTranslatef(0,10,-17);
			glRotatef(-15*sin(walk_time*PI/180),1,0,1);
			glRotatef(45,1,0,0);
			tt.tail_draw(0);
			glTranslatef(0,-14,0);
			glRotatef(20*cos(walk_time*PI/270),0,0,1);
			tt.tail_draw(0);
			glTranslatef(0,-14,0);
			glRotatef(-30*sin(walk_time*PI/360),1,0,0);
			tt.tail_draw(1);
		glPopMatrix();
	}
	
	void body_walk()
	{
		glPushMatrix();
			glTranslatef(0,-1*abs(sin(walk_time*PI/180)),0);
			glTranslatef(0,cb1_hsize/2,0);
			glRotatef(5*sin(walk_time*PI/180),0,0,1);
			glRotatef(5*sin(walk_time*PI/180),0,-1,0);
			glTranslatef(0,-cb1_hsize/2,0);
			bb.body_draw();
			glPushMatrix();
				glTranslatef(0,cb1_hsize,0);
				glRotatef(10*sin(walk_time*PI/180),0,0,1);
				glTranslatef(0,-cb1_hsize,0);
				hh.draw(0);
			glPopMatrix();
			legs_walk();
			arms_walk();
			tail_walk();
		glPopMatrix();
	}

	
	
	//------------------------------------------RUN-----------------------------------------------
	void run()
	{	
		run_time += 20;	
		glPushMatrix();
			glRotatef(180,0,0,1);			
			glRotatef(90,1,0,0);
			glPushMatrix(); //그림자 스택
				glDisable(GL_LIGHTING); //라이팅 끔
				glDisable(GL_DEPTH_TEST); //깊이 체크 끔
				glColor3f(0.3,0.3,0.3); //그림자 색상(회색)
				glDisable(GL_TEXTURE_2D); //텍스쳐 끔
				glShadowProjectionPOINT(sun_position, planePoint, planeNormal); //(광원위치, 몰라, 몰라)
				orgin_run();
				glColor3f(1,1,1);
				glEnable(GL_LIGHTING);
				glEnable(GL_TEXTURE);
				glEnable(GL_DEPTH_TEST);
			glPopMatrix();
			glColor3f(1.0f,1.0f,1.0f);// white !
			glEnable(GL_TEXTURE_2D);
			orgin_run();
		glPopMatrix();
		if((int)run_time % 90 == 0)
		{
			step_sound.Play_Sound();
		}
	}

	void orgin_run()
	{	
		glPushMatrix();
			obj_stand(trs, rot);
			obj_move(trs, rot, 3);
			body_run();
		glPopMatrix();
		if(run_time > 36000)
		{
			run_time = 0;
		}
	}	
	void arms_run()
	{		
		//왼손
		glPushMatrix();
			glTranslatef(16,47,0);
			//glRotatef(5*abs(sin(run_time*PI/180)),0,0,1);
			glRotatef(40,0,0,1);
			glRotatef(-50*sin(run_time*PI/180),1,0,0);
			aa.arms0_draw();
			glTranslatef(0,-ca_hsize*2,0);
			glRotatef(-20*abs(sin(run_time*PI/180)),1,0,0);
			glRotatef(-80,1,0,0);
			aa.arms1_draw(0);
			glTranslatef(0,-ca_hsize_1*2,0);
			glRotatef(-5*abs(sin(run_time*PI/180)),1,0,0);
			glRotatef(-10,1,0,0);
			aa.arms1_draw(1);
		glPopMatrix();

		//오른손
		glPushMatrix();
			glTranslatef(-16,47,0);
			//glRotatef(-5*abs(sin(run_time*PI/180)),0,0,1);
			glRotatef(-40,0,0,1);
			glRotatef(50*sin(run_time*PI/180),1,0,0);
			aa.arms0_draw();
			glTranslatef(0,-ca_hsize*2,0);
			glRotatef(-20*abs(sin(run_time*PI/180)),1,0,0);
			glRotatef(-80,1,0,0);
			aa.arms1_draw(0);
			glTranslatef(0,-ca_hsize_1*2,0);
			glRotatef(-5*abs(sin(run_time*PI/180)),1,0,0);
			glRotatef(-10,1,0,0);
			aa.arms1_draw(1);
		glPopMatrix();
	}
	
	void legs_run()
	{
		//왼발
		glPushMatrix();
			glTranslatef(9,0,0);				
			glRotatef(50*sin(run_time*PI/180),1,0,0);
			ll.legs0_draw();
			glTranslatef(0,-cl_hsize*2,0);
			glRotatef(35*sin(run_time*PI/180),1,0,0);
			glRotatef(35,1,0,0);
			ll.legs0_draw();
			glTranslatef(0,-cl_hsize*2,0);
			glRotatef(5*sin(run_time*PI/180),1,0,0);
			ll.legs1_draw();
		glPopMatrix();

		//오른발
		glPushMatrix();
			glTranslatef(-9,0,0);				
			glRotatef(50*-sin(run_time*PI/180),1,0,0);
			ll.legs0_draw();
			glTranslatef(0,-cl_hsize*2,0);
			glRotatef(35*-sin(run_time*PI/180),1,0,0);
			glRotatef(35,1,0,0);
			ll.legs0_draw();
			glTranslatef(0,-cl_hsize*2,0);
			glRotatef(5*sin(run_time*PI/180),1,0,0);
			ll.legs1_draw();
		glPopMatrix();

	}

	void tail_run()
	{
		glPushMatrix();
			glTranslatef(0,10,-17);
			glRotatef(-15*sin(run_time*PI/180),1,0,1);
			glRotatef(70,1,0,0);
			tt.tail_draw(0);
			glTranslatef(0,-14,0);
			glRotatef(40*cos(run_time*PI/270),1,0,1);
			tt.tail_draw(0);
			glTranslatef(0,-14,0);
			glRotatef(-30*sin(run_time*PI/360),1,0,0);
			tt.tail_draw(1);
		glPopMatrix();
	}
	
	void body_run()
	{
		glPushMatrix();
			glTranslatef(0,-1*abs(sin(run_time*PI/180)),0);
			glTranslatef(0,cb1_hsize/2,0);
			glRotatef(5*sin(run_time*PI/180),0,0,1);
			glRotatef(5*sin(run_time*PI/180),0,-1,0);
			glTranslatef(0,-cb1_hsize/2,0);
			bb.body_draw();
			glPushMatrix();
				glTranslatef(0,cb1_hsize,0);
				glRotatef(10*sin(run_time*PI/180),0,0,1);
				glTranslatef(0,-cb1_hsize,0);
				hh.draw(1);
			glPopMatrix();
			legs_run();
			arms_run();
			tail_run();
		glPopMatrix();
	}

	//------------------------------------------catch_ac-----------------------------------------------

	void catch_ac()
	{
		if(catch_state == 0)
		{
			catch1();
			catch2_time = 0;
		}
		else
		{
			catch2();
			catch1_time = 0;
		}
	}	
	
	//------------------------------------------catch1-----------------------------------------------
	void catch1() //catch1의 최종 통합
	{		
		catch1_time += 1; //함수호출마다 10씩 증가(애니메이션의 기초)
		glPushMatrix();
			glRotatef(180,0,0,1);			
			glRotatef(90,1,0,0); //artoolkit의 좌표와 연동되도록 회전
			glPushMatrix(); //그림자 스택
				glDisable(GL_LIGHTING); //라이팅 끔
				glDisable(GL_DEPTH_TEST); //깊이 체크 끔
				glColor3f(0.3,0.3,0.3); //그림자 색상(회색)
				glDisable(GL_TEXTURE_2D); //텍스쳐 끔
				glShadowProjectionPOINT(sun_position, planePoint, planeNormal); //(광원위치, 몰라, 몰라)
				orgin_catch1();
				glColor3f(1,1,1);
				glEnable(GL_LIGHTING);
				glEnable(GL_TEXTURE);
				glEnable(GL_DEPTH_TEST);
			glPopMatrix();
			glColor3f(1.0f,1.0f,1.0f);// white !
			glEnable(GL_TEXTURE_2D);
			orgin_catch1();
		glPopMatrix();
	}

	void orgin_catch1()//캐릭터 모델
	{		
		glPushMatrix();
			obj_stand(trs, rot); //현재 캐릭터의 위치값과 방향벡터를 넘겨주어 translate와 rotate 시킴
			glTranslatef(0,-5*abs(sin(catch1_time*PI/180)),0);
			legs_catch1();
			body_catch1();
		glPopMatrix();
		if(catch1_time > 90) //시간은 무한 반복
		{
			catch1_time = 90;
			catch_state = 1;
		}
	}

	void arms_catch1()
	{		
		glPushMatrix();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(16,47,0);
			glRotatef(-70*sin((catch1_time)*PI/180),1,0,0);
			aa.arms0_draw();
			glTranslatef(0,-ca_hsize*2,0);
			glRotatef(-5,1,0,0);
			aa.arms1_draw(0);
			glTranslatef(0,-ca_hsize_1*2,0);
			aa.arms1_draw(1);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-16,47,0);
			glRotatef(-70*sin((catch1_time)*PI/180),1,0,0);
			aa.arms0_draw();
			glTranslatef(0,-ca_hsize*2,0);
			glRotatef(-5,1,0,0);
			aa.arms1_draw(0);
			glTranslatef(0,-ca_hsize_1*2,0);
			aa.arms1_draw(1);
		glPopMatrix();
	}

	void legs_catch1()
	{		
		glPushMatrix();
			glTranslatef(-9,0,0);
			//glPushMatrix();
				glRotatef(-30*sin(catch1_time*PI/180),1,0,0);
				ll.legs0_draw();
			//glPopMatrix();
			glTranslatef(0,-cl_hsize*4,0);
			glTranslatef(0,cl_hsize*2,0);
			glRotatef(60*sin(catch1_time*PI/180),1,0,0);
			ll.legs0_draw();
			glTranslatef(0,-cl_hsize*2,0);
			ll.legs1_draw();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(9,0,0);
			//glPushMatrix();
				glRotatef(-30*sin(catch1_time*PI/180),1,0,0);
				ll.legs0_draw();
			//glPopMatrix();
			glTranslatef(0,-cl_hsize*4,0);
			glTranslatef(0,cl_hsize*2,0);
			glRotatef(60*sin(catch1_time*PI/180),1,0,0);
			ll.legs0_draw();
			glTranslatef(0,-cl_hsize*2,0);
			ll.legs1_draw();
		glPopMatrix();
	}

	void tail_catch1()
	{
		glPushMatrix();
			glTranslatef(0,10,-17);
			glRotatef(30,1,0,0);
			glRotatef(-15*sin(catch1_time*PI/270+1),1,0,1);
			tt.tail_draw(0);
			glTranslatef(0,-14,0);
			glRotatef(30*cos(catch1_time*PI/180+2),1,0,0);
			tt.tail_draw(0);
			glTranslatef(0,-14,0);
			glRotatef(-20*sin(catch1_time*PI/180+0.45),1,1,1);
			tt.tail_draw(1);
		glPopMatrix();
	}

	void body_catch1()
	{
		glPushMatrix();
			glTranslatef(0,cb1_hsize/2,0);
			glTranslatef(0,-cb1_hsize/2,0);
			glRotatef(30*sin(catch1_time*PI/180),1,0,0);
			bb.body_draw();
			glPushMatrix();
				glTranslatef(0,cb1_hsize,0);
				glRotatef(5*sin(catch1_time*PI/180),0,0,1);
				glTranslatef(0,-cb1_hsize,0);

				hh.draw(2);
			glPopMatrix();
			arms_catch1();
			tail_catch1();
		glPopMatrix();
	}

	
	//------------------------------------------catch2-----------------------------------------------
	void catch2() //catch2의 최종 통합
	{		
		catch2_time += catch2_tt; //함수호출마다 10씩 증가(애니메이션의 기초)
		catch3_time += 1; //함수호출마다 10씩 증가(애니메이션의 기초)
		glPushMatrix();
			glRotatef(180,0,0,1);			
			glRotatef(90,1,0,0); //artoolkit의 좌표와 연동되도록 회전
			glPushMatrix(); //그림자 스택
				glDisable(GL_LIGHTING); //라이팅 끔
				glDisable(GL_DEPTH_TEST); //깊이 체크 끔
				glColor3f(0.3,0.3,0.3); //그림자 색상(회색)
				glDisable(GL_TEXTURE_2D); //텍스쳐 끔
				glShadowProjectionPOINT(sun_position, planePoint, planeNormal); //(광원위치, 몰라, 몰라)
				orgin_catch2();
				glColor3f(1,1,1);
				glEnable(GL_LIGHTING);
				glEnable(GL_TEXTURE);
				glEnable(GL_DEPTH_TEST);
			glPopMatrix();
			glColor3f(1.0f,1.0f,1.0f);// white !
			glEnable(GL_TEXTURE_2D);
			orgin_catch2();
		glPopMatrix();
	}

	void orgin_catch2()//캐릭터 모델
	{		
		glPushMatrix();
			obj_stand(trs, rot); //현재 캐릭터의 위치값과 방향벡터를 넘겨주어 translate와 rotate 시킴
			glTranslatef(0,-5,0);
			legs_catch2();
			body_catch2();
		glPopMatrix();
		if(catch2_time > 90) //시간은 무한 반복
		{
			catch2_time = 90;
		}
		else if(catch2_time < 0)
		{
			catch2_tt = 1;
			catch3_time = 0;
		}
		if(catch3_time > 180)
		{
			catch2_tt = -1;
			catch3_time = 0;
		}
	}

	void arms_catch2()
	{		
		glPushMatrix();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(16,47,0);
			glRotatef(-70,1,0,0);
			aa.arms0_draw();
			glTranslatef(0,-ca_hsize*2,0);
			glRotatef(-5,1,0,0);
			aa.arms1_draw(0);
			glTranslatef(0,-ca_hsize_1*2,0);
			aa.arms1_draw(1);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-16,47,0);
			glRotatef(-70,1,0,0);
			aa.arms0_draw();
			glTranslatef(0,-ca_hsize*2,0);
			glRotatef(-5,1,0,0);
			aa.arms1_draw(0);
			glTranslatef(0,-ca_hsize_1*2,0);
			aa.arms1_draw(1);
		glPopMatrix();
	}

	void legs_catch2()
	{		
		glPushMatrix();
			glTranslatef(-9,0,0);
			//glPushMatrix();
				glRotatef(-30,1,0,0);
				ll.legs0_draw();
			//glPopMatrix();
			glTranslatef(0,-cl_hsize*4,0);
			glTranslatef(0,cl_hsize*2,0);
			glRotatef(60,1,0,0);
			ll.legs0_draw();
			glTranslatef(0,-cl_hsize*2,0);
			ll.legs1_draw();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(9,0,0);
			//glPushMatrix();
				glRotatef(-30,1,0,0);
				ll.legs0_draw();
			//glPopMatrix();
			glTranslatef(0,-cl_hsize*4,0);
			glTranslatef(0,cl_hsize*2,0);
			glRotatef(60,1,0,0);
			ll.legs0_draw();
			glTranslatef(0,-cl_hsize*2,0);
			ll.legs1_draw();
		glPopMatrix();
	}

	void tail_catch2()
	{
		glPushMatrix();
			glTranslatef(0,10,-17);
			glRotatef(30,1,0,0);
			glRotatef(80*sin(catch2_time*PI/180),1,0,0);
			glRotatef(-15*sin(90*PI/270+1),1,0,0);
			tt.tail_draw(0);
			glTranslatef(0,-14,0);
			glRotatef(30*sin(catch2_time*PI/180),1,0,0);
			glRotatef(30*cos(90*PI/180+2),1,0,0);
			tt.tail_draw(0);
			glTranslatef(0,-14,0);
			glRotatef(40*sin(catch2_time*PI/180),1,0,0);
			glRotatef(-20*sin(90*PI/180+0.45),1,0,0);
			tt.tail_draw(1);
		glPopMatrix();
	}

	void body_catch2()
	{
		glPushMatrix();
			glTranslatef(0,cb1_hsize/2,0);
			glTranslatef(0,-cb1_hsize/2,0);
			glRotatef(-15*sin(catch2_time*PI/180),1,0,0);
			glRotatef(30,1,0,0);
			bb.body_draw();
			glPushMatrix();
				glTranslatef(0,cb1_hsize,0);
				glRotatef(-25*sin(catch2_time*PI/180),1,0,0);
				glTranslatef(0,-cb1_hsize,0);
				hh.draw(1);
			glPopMatrix();
			arms_catch2();
			tail_catch2();
		glPopMatrix();
	}

	
	//------------------------------------------handup-----------------------------------------------
	void handup() //handup의 최종 통합
	{		
		handup_time += 10; //함수호출마다 10씩 증가(애니메이션의 기초)
		glPushMatrix();
			glRotatef(180,0,0,1);			
			glRotatef(90,1,0,0); //artoolkit의 좌표와 연동되도록 회전
			glPushMatrix(); //그림자 스택
				glDisable(GL_LIGHTING); //라이팅 끔
				glDisable(GL_DEPTH_TEST); //깊이 체크 끔
				glColor3f(0.3,0.3,0.3); //그림자 색상(회색)
				glDisable(GL_TEXTURE_2D); //텍스쳐 끔
				glShadowProjectionPOINT(sun_position, planePoint, planeNormal); //(광원위치, 몰라, 몰라)
				orgin_handup();
				glColor3f(1,1,1);
				glEnable(GL_LIGHTING);
				glEnable(GL_TEXTURE);
				glEnable(GL_DEPTH_TEST);
			glPopMatrix();
			glColor3f(1.0f,1.0f,1.0f);// white !
			glEnable(GL_TEXTURE_2D);
			orgin_handup();
		glPopMatrix();
	}

	void orgin_handup()//캐릭터 모델
	{		
		glPushMatrix();
			obj_stand(trs, rot); //현재 캐릭터의 위치값과 방향벡터를 넘겨주어 translate와 rotate 시킴
			legs_handup();
			body_handup();
		glPopMatrix();
		if(handup_time > 36000) //시간은 무한 반복
		{
			handup_time = 0;
		}
	}

	void arms_handup()
	{		
		glPushMatrix();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(16,47,0);
			glRotatef(-150,1,0,0);
			aa.arms0_draw();
			glTranslatef(0,-ca_hsize*2,0);
			glRotatef(-5,1,0,0);
			aa.arms1_draw(0);
			glTranslatef(0,-ca_hsize_1*2,0);
			aa.arms1_draw(1);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-16,47,0);
			glRotatef(-150,1,0,0);
			aa.arms0_draw();
			glTranslatef(0,-ca_hsize*2,0);
			glRotatef(-5,1,0,0);
			aa.arms1_draw(0);
			glTranslatef(0,-ca_hsize_1*2,0);
			aa.arms1_draw(1);
		glPopMatrix();
	}

	void legs_handup()
	{		
		glPushMatrix();
			glTranslatef(-9,0,0);
			glPushMatrix();
				glRotatef(5*sin((handup_time+180)*PI/180),1,0,0);
				glRotatef(-5,1,0,0);
				ll.legs0_draw();
			glPopMatrix();
			glTranslatef(0,-cl_hsize*4,0);
			glRotatef(-5*sin((handup_time+180)*PI/180),1,0,0);
			glRotatef(5,1,0,0);
			glTranslatef(0,cl_hsize*2,0);
			ll.legs0_draw();
			glTranslatef(0,-cl_hsize*2,0);
			ll.legs1_draw();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(9,0,0);
			glPushMatrix();
				glRotatef(5*sin(handup_time*PI/180),1,0,0);
				glRotatef(-5,1,0,0);
				ll.legs0_draw();
			glPopMatrix();
			glTranslatef(0,-cl_hsize*4,0);
			glRotatef(-5*sin(handup_time*PI/180),1,0,0);
			glRotatef(5,1,0,0);
			glTranslatef(0,cl_hsize*2,0);
			ll.legs0_draw();
			glTranslatef(0,-cl_hsize*2,0);
			ll.legs1_draw();
		glPopMatrix();
	}

	void tail_handup()
	{
		glPushMatrix();
			glTranslatef(0,10,-17);
			glRotatef(30,1,0,0);
			glRotatef(-15*sin(handup_time*PI/270+1),1,0,1);
			tt.tail_draw(0);
			glTranslatef(0,-14,0);
			glRotatef(30*cos(handup_time*PI/180+2),1,0,0);
			tt.tail_draw(0);
			glTranslatef(0,-14,0);
			glRotatef(-20*sin(handup_time*PI/180+0.45),1,1,1);
			tt.tail_draw(1);
		glPopMatrix();
	}

	void body_handup()
	{
		glPushMatrix();
			glTranslatef(0,-1*abs(sin(handup_time*PI/180)),0);
			glTranslatef(0,cb1_hsize/2,0);
			glRotatef(5*sin(handup_time*PI/180),0,0,1);
			glTranslatef(0,-cb1_hsize/2,0);
			bb.body_draw();
			glPushMatrix();
				glTranslatef(0,cb1_hsize,0);
				glRotatef(-60,1,0,0);
				glTranslatef(0,-cb1_hsize,0);
				hh.draw(3);
			glPopMatrix();
			arms_handup();
			tail_handup();
		glPopMatrix();
	}

	//------------------------------------------side_left-----------------------------------------------
	int side_left()
	{	
		side_time += 10;	
		glPushMatrix();
			glRotatef(180,0,0,1);			
			glRotatef(90,1,0,0);
			glPushMatrix(); //그림자 스택
				glDisable(GL_LIGHTING); //라이팅 끔
				glDisable(GL_DEPTH_TEST); //깊이 체크 끔
				glColor3f(0.3,0.3,0.3); //그림자 색상(회색)
				glDisable(GL_TEXTURE_2D); //텍스쳐 끔
				glShadowProjectionPOINT(sun_position, planePoint, planeNormal); //(광원위치, 몰라, 몰라)
				orgin_side_left();
				glColor3f(1,1,1);
				glEnable(GL_LIGHTING);
				glEnable(GL_TEXTURE);
				glEnable(GL_DEPTH_TEST);
			glPopMatrix();
			glColor3f(1.0f,1.0f,1.0f);// white !
			glEnable(GL_TEXTURE_2D);
			orgin_side_left();
		glPopMatrix();
		if((int)side_time % 170 == 0)
		{
			side_sound.Play_Sound();
		}
		if(side_time < 180)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}

	void orgin_side_left()
	{	
		glPushMatrix();
			obj_stand(trs, rot);
			body_side_left();
		glPopMatrix();
		if(side_time > 180)
		{
			side_time = 0;
		}
	}	
	void arms_side_left()
	{		
		//왼손
		glPushMatrix();
			glTranslatef(16,47,0);
			glRotatef(25,0,0,1);
			glRotatef(35*sin(side_time*PI/180),1,0,0);
			glRotatef(25*sin(side_time*PI/180),0,0,-1);
			aa.arms0_draw();
			glTranslatef(0,-ca_hsize*2,0);
			glRotatef(-90*abs(sin(side_time*PI/180)),1,0,0);
			aa.arms1_draw(0);
			glTranslatef(0,-ca_hsize_1*2,0);
			glRotatef(-5*abs(sin(side_time*PI/180)),1,0,0);
			aa.arms1_draw(1);
		glPopMatrix();

		//오른손
		glPushMatrix();
			glTranslatef(-16,47,0);
			glRotatef(-25,0,0,1);
			glRotatef(25*sin(side_time*PI/180),1,0,0);
			aa.arms0_draw();
			glTranslatef(0,-ca_hsize*2,0);
			glRotatef(-20*abs(sin(side_time*PI/180)),1,0,0);
			aa.arms1_draw(0);
			glTranslatef(0,-ca_hsize_1*2,0);
			glRotatef(-5*abs(sin(side_time*PI/180)),1,0,0);
			aa.arms1_draw(1);
		glPopMatrix();
	}
	
	void legs_side_left()
	{
		//왼발
		glPushMatrix();
			glTranslatef(9,0,0);				
			glRotatef(40*sin(side_time*PI/180),0,0,-1);
			ll.legs0_draw();
			glTranslatef(0,-cl_hsize*2,0);
			glRotatef(5,1,0,0);
			ll.legs0_draw();
			glTranslatef(0,-cl_hsize*2,0);
			glRotatef(5,1,0,0);
			ll.legs1_draw();
		glPopMatrix();

		//오른발
		glPushMatrix();
			glTranslatef(-9,0,0);		
			glRotatef(25*sin(side_time*PI/180),0,0,1);
			ll.legs0_draw();
			glTranslatef(0,-cl_hsize*2,0);
			glRotatef(5,1,0,0);
			ll.legs0_draw();
			glTranslatef(0,-cl_hsize*2,0);
			glRotatef(5,1,0,0);
			ll.legs1_draw();
		glPopMatrix();

	}

	void tail_side_left()
	{
		glPushMatrix();
			glTranslatef(0,10,-17);
			glRotatef(-15*sin(side_time*PI/180),1,0,1);
			glRotatef(45,1,0,0);
			tt.tail_draw(0);
			glTranslatef(0,-14,0);
			glRotatef(-20*cos(side_time*PI/270),0,0,1);
			tt.tail_draw(0);
			glTranslatef(0,-14,0);
			glRotatef(-30*sin(side_time*PI/360),0,0,1);
			tt.tail_draw(1);
		glPopMatrix();
	}
	
	void body_side_left()
	{
		glPushMatrix();
			glTranslatef(0,-1*abs(sin(side_time*PI/180)),0);
			glTranslatef(0,cb1_hsize/2,0);
			glRotatef(20*sin(side_time*PI/180),0,0,1);
			glTranslatef(0,-cb1_hsize/2,0);
			bb.body_draw();
			glPushMatrix();
				glTranslatef(0,cb1_hsize,0);
				glRotatef(20*sin(side_time*PI/180),0,0,1);
				glTranslatef(0,-cb1_hsize,0);
				hh.draw(2);
			glPopMatrix();
			legs_side_left();
			arms_side_left();
			tail_side_left();
		glPopMatrix();
	}

	
	//------------------------------------------bubi-----------------------------------------------
	void bubi() //bubi의 최종 통합
	{		
		bubi_time += 10; //함수호출마다 10씩 증가(애니메이션의 기초)
		glPushMatrix();
			glRotatef(180,0,0,1);			
			glRotatef(90,1,0,0); //artoolkit의 좌표와 연동되도록 회전
			glPushMatrix(); //그림자 스택
				glDisable(GL_LIGHTING); //라이팅 끔
				glDisable(GL_DEPTH_TEST); //깊이 체크 끔
				glColor3f(0.3,0.3,0.3); //그림자 색상(회색)
				glDisable(GL_TEXTURE_2D); //텍스쳐 끔
				glShadowProjectionPOINT(sun_position, planePoint, planeNormal); //(광원위치, 몰라, 몰라)
				orgin_bubi();
				glColor3f(1,1,1);
				glEnable(GL_LIGHTING);
				glEnable(GL_TEXTURE);
				glEnable(GL_DEPTH_TEST);
			glPopMatrix();
			glColor3f(1.0f,1.0f,1.0f);// white !
			glEnable(GL_TEXTURE_2D);
			orgin_bubi();
		glPopMatrix();
	}

	void orgin_bubi()//캐릭터 모델
	{		
		glPushMatrix();
			obj_stand(trs, rot); //현재 캐릭터의 위치값과 방향벡터를 넘겨주어 translate와 rotate 시킴
			legs_bubi();
			body_bubi();
		glPopMatrix();
		if(bubi_time > 36000) //시간은 무한 반복
		{
			bubi_time = 0;
		}
	}

	void bubi_rotate()
	{		
		bubi_time += 10;
		glPushMatrix();
			glPushMatrix(); //그림자 스택
				glDisable(GL_LIGHTING); //라이팅 끔
				glDisable(GL_DEPTH_TEST); //깊이 체크 끔
				glColor3f(0.3,0.3,0.3); //그림자 색상(회색)
				glDisable(GL_TEXTURE_2D); //텍스쳐 끔
				glShadowProjectionPOINT(sun_position, planePoint, planeNormal); //(광원위치, 몰라, 몰라)
				origin_stand_rotate();
				glColor3f(1,1,1);
				glEnable(GL_LIGHTING);
				glEnable(GL_TEXTURE);
				glEnable(GL_DEPTH_TEST);
			glPopMatrix();
			glColor3f(1.0f,1.0f,1.0f);// white !
			glEnable(GL_TEXTURE_2D);
			origin_stand_rotate();
		glPopMatrix();
	}

	void origin_bubi_rotate()
	{		
		glPushMatrix();
			obj_stand(trs, rot);
			legs_bubi();
			body_bubi();
		glPopMatrix();
		if(bubi_time > 36000)
		{
			bubi_time = 0;
		}
	}
	
	void arms_bubi()
	{		
		glPushMatrix();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(16,47,0);
			//glRotatef(5*abs(sin(bubi_time*PI/180)),0,0,1);
			glRotatef(10,0,1,0);
			glRotatef(-90,1,0,0);
			aa.arms0_draw();
			glTranslatef(0,-ca_hsize*2,0);
			glRotatef(-5,1,0,0);
			aa.arms1_draw(0);
			glTranslatef(0,-ca_hsize_1*2,0);
			aa.arms1_draw(1);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-16,47,0);
			//glRotatef(-5*abs(sin(bubi_time*PI/180)),0,0,1);
			glRotatef(-10,0,1,0);
			glRotatef(-90,1,0,0);
			aa.arms0_draw();
			glTranslatef(0,-ca_hsize*2,0);
			glRotatef(-5,1,0,0);
			aa.arms1_draw(0);
			glTranslatef(0,-ca_hsize_1*2,0);
			aa.arms1_draw(1);
		glPopMatrix();
	}

	void legs_bubi()
	{		
		glPushMatrix();
			glTranslatef(-9,0,0);
			glPushMatrix();
				glRotatef(5*sin((bubi_time+180)*PI/180),1,0,0);
				glRotatef(-5,1,0,0);
				ll.legs0_draw();
			glPopMatrix();
			glTranslatef(0,-cl_hsize*4,0);
			glRotatef(-5*sin((bubi_time+180)*PI/180),1,0,0);
			glRotatef(5,1,0,0);
			glTranslatef(0,cl_hsize*2,0);
			ll.legs0_draw();
			glTranslatef(0,-cl_hsize*2,0);
			ll.legs1_draw();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(9,0,0);
			glPushMatrix();
				glRotatef(5*sin(bubi_time*PI/180),1,0,0);
				glRotatef(-5,1,0,0);
				ll.legs0_draw();
			glPopMatrix();
			glTranslatef(0,-cl_hsize*4,0);
			glRotatef(-5*sin(bubi_time*PI/180),1,0,0);
			glRotatef(5,1,0,0);
			glTranslatef(0,cl_hsize*2,0);
			ll.legs0_draw();
			glTranslatef(0,-cl_hsize*2,0);
			ll.legs1_draw();
		glPopMatrix();
	}

	void tail_bubi()
	{
		glPushMatrix();
			glTranslatef(0,10,-17);
			glRotatef(30,1,0,0);
			glRotatef(-15*sin(bubi_time*PI/270+1),1,0,1);
			tt.tail_draw(0);
			glTranslatef(0,-14,0);
			glRotatef(30*cos(bubi_time*PI/180+2),1,0,0);
			tt.tail_draw(0);
			glTranslatef(0,-14,0);
			glRotatef(-20*sin(bubi_time*PI/180+0.45),1,1,1);
			tt.tail_draw(1);
		glPopMatrix();
	}

	void body_bubi()
	{
		glPushMatrix();
			glTranslatef(0,-1*abs(sin(bubi_time*PI/180)),0);
			glTranslatef(0,cb1_hsize/2,0);
			glRotatef(5*sin(bubi_time*PI/180),0,0,1);
			glTranslatef(0,-cb1_hsize/2,0);
			bb.body_draw();
			glPushMatrix();
				glTranslatef(0,cb1_hsize,0);
				glRotatef(30*sin(bubi_time*PI/180),0,1,0);
				glTranslatef(0,-cb1_hsize,0);

				hh.draw(1);
			glPopMatrix();
			arms_bubi();
			tail_bubi();
		glPopMatrix();
	}

	
	//------------------------------------------drop_1-----------------------------------------------
	void drop_1() //drop_1의 최종 통합
	{		
		stand_time += 10; //함수호출마다 10씩 증가(애니메이션의 기초)
		glPushMatrix();
			glRotatef(180,0,0,1);			
			glRotatef(90,1,0,0); //artoolkit의 좌표와 연동되도록 회전
			glPushMatrix(); //그림자 스택
				glDisable(GL_LIGHTING); //라이팅 끔
				glDisable(GL_DEPTH_TEST); //깊이 체크 끔
				glColor3f(0.3,0.3,0.3); //그림자 색상(회색)
				glDisable(GL_TEXTURE_2D); //텍스쳐 끔
				glShadowProjectionPOINT(sun_position, planePoint, planeNormal); //(광원위치, 몰라, 몰라)
				orgin_drop_1();
				glColor3f(1,1,1);
				glEnable(GL_LIGHTING);
				glEnable(GL_TEXTURE);
				glEnable(GL_DEPTH_TEST);
			glPopMatrix();
			glColor3f(1.0f,1.0f,1.0f);// white !
			glEnable(GL_TEXTURE_2D);
			orgin_drop_1();
		glPopMatrix();
	}

	void orgin_drop_1()//캐릭터 모델
	{		
		glPushMatrix();
			obj_stand(trs, rot); //현재 캐릭터의 위치값과 방향벡터를 넘겨주어 translate와 rotate 시킴
			legs_drop_1();
			body_drop_1();
		glPopMatrix();
		/*if(drop_1_time > 36000) //시간은 무한 반복
		{
			drop_1_time = 0;
		}*/
	}

	void origin_drop_1_rotate()
	{		
		glPushMatrix();
			obj_stand(trs, rot);
			legs_drop_1();
			body_drop_1();
		glPopMatrix();
		/*if(drop_1_time > 36000)
		{
			drop_1_time = 0;
		}*/
	}
	
	void arms_drop_1()
	{		
		glPushMatrix();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(16,47,0);
			//glRotatef(5*abs(sin(drop_1_time*PI/180)),0,0,1);
			glRotatef(-65,1,0,0);
			glRotatef(15,0,0,1);
			aa.arms0_draw();
			glTranslatef(0,-ca_hsize*2,0);
			glRotatef(-5,1,0,0);
			aa.arms1_draw(0);
			glTranslatef(0,-ca_hsize_1*2,0);
			aa.arms1_draw(1);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-16,47,0);
			//glRotatef(-5*abs(sin(drop_1_time*PI/180)),0,0,1);
			glRotatef(-65,1,0,0);
			glRotatef(-15,0,0,1);
			aa.arms0_draw();
			glTranslatef(0,-ca_hsize*2,0);
			glRotatef(-5,1,0,0);
			aa.arms1_draw(0);
			glTranslatef(0,-ca_hsize_1*2,0);
			aa.arms1_draw(1);
		glPopMatrix();
	}

	void legs_drop_1()
	{		
		glPushMatrix();
			glTranslatef(-9,0,0);
			//glPushMatrix();
				//glRotatef(5*sin((drop_1_time+180)*PI/180),1,0,0);
				//glRotatef(-45,1,0,0);
				ll.legs0_draw();
			//glPopMatrix();
			glTranslatef(0,-cl_hsize*4,0);
			//glRotatef(-5*sin((drop_1_time+180)*PI/180),1,0,0);
			glRotatef(5,1,0,0);
			glTranslatef(0,cl_hsize*2,0);
			ll.legs0_draw();
			glTranslatef(0,-cl_hsize*2,0);
			ll.legs1_draw();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(9,0,0);
			//glPushMatrix();
				//glRotatef(5*sin(drop_1_time*PI/180),1,0,0);
				//glRotatef(-45,1,0,0);
				ll.legs0_draw();
			//glPopMatrix();
			glTranslatef(0,-cl_hsize*4,0);
			//glRotatef(-5*sin(drop_1_time*PI/180),1,0,0);
			glRotatef(5,1,0,0);
			glTranslatef(0,cl_hsize*2,0);
			ll.legs0_draw();
			glTranslatef(0,-cl_hsize*2,0);
			ll.legs1_draw();
		glPopMatrix();
	}

	void tail_drop_1()
	{
		glPushMatrix();
			glTranslatef(0,10,-17);
			glRotatef(30,1,0,0);
			glRotatef(-10*sin(stand_time*PI/270+1),1,0,1);
			glRotatef(-10,1,0,0);
			tt.tail_draw(0);
			glTranslatef(0,-14,0);
			//glRotatef(30*cos(stand_time*PI/180+2),1,0,0);
			glRotatef(-40,1,0,0);
			tt.tail_draw(0);
			glTranslatef(0,-14,0);
			//glRotatef(-20*sin(stand_time*PI/180+0.45),1,1,1);
			glRotatef(-20,1,0,0);
			tt.tail_draw(1);
		glPopMatrix();
	}

	void body_drop_1()
	{
		glPushMatrix();
			glTranslatef(0,-1*abs(sin(stand_time*PI/180)),0);
			glTranslatef(0,cb1_hsize/2,0);
			//glRotatef(5*sin(stand_time*PI/180),0,0,1);
			glTranslatef(0,-cb1_hsize/2,0);
			glRotatef(40,1,0,0);
			bb.body_draw();
			glPushMatrix();
				glTranslatef(0,cb1_hsize,0);
				glRotatef(5*sin(stand_time*PI/180),0,0,1);
				glTranslatef(0,-cb1_hsize,0);
				hh.draw(4);
			glPopMatrix();
			arms_drop_1();
			tail_drop_1();
		glPopMatrix();
	}


	
	//------------------------------------------drop_2-----------------------------------------------
	void drop_2() //drop_2의 최종 통합
	{		
		drop_time += 10; //함수호출마다 10씩 증가(애니메이션의 기초)
		glPushMatrix();
			glRotatef(180,0,0,1);			
			glRotatef(90,1,0,0); //artoolkit의 좌표와 연동되도록 회전
			glPushMatrix(); //그림자 스택
				glDisable(GL_LIGHTING); //라이팅 끔
				glDisable(GL_DEPTH_TEST); //깊이 체크 끔
				glColor3f(0.3,0.3,0.3); //그림자 색상(회색)
				glDisable(GL_TEXTURE_2D); //텍스쳐 끔
				glShadowProjectionPOINT(sun_position, planePoint, planeNormal); //(광원위치, 몰라, 몰라)
				orgin_drop_2();
				glColor3f(1,1,1);
				glEnable(GL_LIGHTING);
				glEnable(GL_TEXTURE);
				glEnable(GL_DEPTH_TEST);
			glPopMatrix();
			glColor3f(1.0f,1.0f,1.0f);// white !
			glEnable(GL_TEXTURE_2D);
			orgin_drop_2();
		glPopMatrix();
		if((int)drop_time % 500 == 0)
		{
			drop_sound.Play_Sound();
		}
	}

	void orgin_drop_2()//캐릭터 모델
	{		
		glPushMatrix();
			obj_stand(trs, rot); //현재 캐릭터의 위치값과 방향벡터를 넘겨주어 translate와 rotate 시킴
			glRotatef(10*sin(drop_time*PI/180),0,1,0);
			legs_drop_2();
			body_drop_2();
		glPopMatrix();
		if(drop_time > 36000) //시간은 무한 반복
		{
			drop_time = 0;
		}
	}
	
	void arms_drop_2()
	{		
		glPushMatrix();
			glTranslatef(16,47,0);
			glRotatef(-65,1,0,0);
			glRotatef(40,0,0,1);
			glRotatef(-50*sin(drop_time*PI/180),0,0,1);
			aa.arms0_draw();
			glTranslatef(0,-ca_hsize*2,0);
			glRotatef(-20*abs(sin(drop_time*PI/180)),0,0,1);
			glRotatef(-50,0,0,1);
			aa.arms1_draw(0);
			glTranslatef(0,-ca_hsize_1*2,0);
			glRotatef(-5*abs(sin(drop_time*PI/180)),0,0,1);
			glRotatef(-10,0,0,1);
			aa.arms1_draw(1);
		glPopMatrix();

		//오른손
		glPushMatrix();
			glTranslatef(-16,47,0);
			glRotatef(-65,1,0,0);
			glRotatef(-40,0,0,1);
			glRotatef(-50*sin(drop_time*PI/180),0,0,1);
			aa.arms0_draw();
			glTranslatef(0,-ca_hsize*2,0);
			glRotatef(20*abs(sin(drop_time*PI/180)),0,0,1);
			glRotatef(50,0,0,1);
			aa.arms1_draw(0);
			glTranslatef(0,-ca_hsize_1*2,0);
			glRotatef(5*abs(sin(drop_time*PI/180)),0,0,1);
			glRotatef(10,0,0,1);
			aa.arms1_draw(1);
		glPopMatrix();
	}

	void legs_drop_2()
	{		
		//왼발
		glPushMatrix();
			glTranslatef(9,0,0);				
			glRotatef(40*sin(drop_time*PI/180),1,0,0);
			ll.legs0_draw();
			glTranslatef(0,-cl_hsize*2,0);
			glRotatef(20*sin(drop_time*PI/180),1,0,0);
			glRotatef(20,1,0,0);
			ll.legs0_draw();
			glTranslatef(0,-cl_hsize*2,0);
			glRotatef(5*sin(drop_time*PI/180),1,0,0);
			ll.legs1_draw();
		glPopMatrix();

		//오른발
		glPushMatrix();
			glTranslatef(-9,0,0);				
			glRotatef(40*-sin(drop_time*PI/180),1,0,0);
			ll.legs0_draw();
			glTranslatef(0,-cl_hsize*2,0);
			glRotatef(20*-sin(drop_time*PI/180),1,0,0);
			glRotatef(20,1,0,0);
			ll.legs0_draw();
			glTranslatef(0,-cl_hsize*2,0);
			glRotatef(5*sin(drop_time*PI/180),1,0,0);
			ll.legs1_draw();
		glPopMatrix();
	}

	void tail_drop_2()
	{
		glPushMatrix();
			glTranslatef(0,10,-17);
			glRotatef(30,1,0,0);
			glRotatef(-10*sin(drop_time*PI/270+1),1,0,1);
			glRotatef(-10,1,0,0);
			tt.tail_draw(0);
			glTranslatef(0,-14,0);
			glRotatef(30*cos(drop_time*PI/180+2),1,0,0);
			glRotatef(-40,1,0,0);
			tt.tail_draw(0);
			glTranslatef(0,-14,0);
			glRotatef(-20,1,0,0);
			tt.tail_draw(1);
		glPopMatrix();
	}

	void body_drop_2()
	{
		glPushMatrix();
			glTranslatef(0,cb1_hsize/2,0);
			glTranslatef(0,-cb1_hsize/2,0);
			glRotatef(40,1,0,0);
			bb.body_draw();
			glPushMatrix();
				glTranslatef(0,cb1_hsize,0);
				glRotatef(15*sin(drop_time*PI/180),1,0,0);
				glTranslatef(0,-cb1_hsize,0);
				hh.draw(1);
			glPopMatrix();
			arms_drop_2();
			tail_drop_2();
		glPopMatrix();
	}
};
#endif
