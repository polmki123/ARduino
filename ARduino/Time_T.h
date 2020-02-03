/*
	시작 시간과 현재 시간의 차이를 구함.
	프로젝트에서 사용안됨.
*/

#ifndef __TIME_T__
#define __TIME_T__

#include <time.h>
float t_t = 0;
float stand_time = 0;
double ar_time = 0;


class Time_T
{
private:
	clock_t start_t, now_t;
public:
	Time_T()
	{
		start_t = clock();
	}
	void time_run()
	{
		now_t = clock();
		ar_time = (double)(now_t - start_t) / CLK_TCK;
	}
};

#endif