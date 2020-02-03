/*
	사운드 출력 헤더
*/
#ifndef __SOUND_UTIL__
#define __SOUND_UTIL__

#include <windows.h>
#include <iostream>

class SOUND_UTIL{
public:
	SOUND_UTIL(){};
	~SOUND_UTIL(){};

public:
	void Init_Sound(int type_of_source,const char* filename);
	void Change_Sound(int type_of_source,const char* filename);
	void Close_Sound();
	void Play_Sound(bool repeat=false);


private:
	MCI_OPEN_PARMS mciOpenParm;
	MCI_PLAY_PARMS mciPlayParams;
	DWORD wDeviceID;
	int errorCode;
};

#endif