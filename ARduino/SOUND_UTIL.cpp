#include "SOUND_UTIL.h"
#include <digitalv.h>

//############################
//	Descrirption
//	1)type_of_source
//		1> mpegvideo (mp3)
//		waveaudio (wav)
//############################

void SOUND_UTIL::Init_Sound(int type_of_source,const char* filename){
	if(type_of_source==1)mciOpenParm.lpstrDeviceType="mpegvideo";
	else mciOpenParm.lpstrDeviceType= "waveaudio";
	mciOpenParm.lpstrElementName=filename;
	errorCode=mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_TYPE|MCI_OPEN_ELEMENT,(DWORD)(LPVOID)&mciOpenParm);
	std::cout<<"Sound Error code :"<<errorCode<<std::endl;
	wDeviceID=mciOpenParm.wDeviceID;
}

void SOUND_UTIL::Close_Sound(){
	//mciSendCommand(wDeviceID, MCI_CLOSE, 0,(DWORD)(LPVOID)&mciOpenParm);
	mciSendCommand(wDeviceID, MCI_STOP, 0,(DWORD)(LPVOID)&mciOpenParm);
}

void SOUND_UTIL::Play_Sound(bool repeat){
	MCI_PLAY_PARMS mciPlayParams;
	mciPlayParams.dwCallback=NULL;

	errorCode=mciSendCommand(wDeviceID,MCI_SEEK,MCI_SEEK_TO_START, (DWORD)(LPVOID)&mciPlayParams);
	//std::cout<<"Sound Seek Error code :"<<errorCode<<std::endl;
	if(repeat)errorCode=mciSendCommand(wDeviceID,MCI_PLAY,MCI_NOTIFY|MCI_DGV_PLAY_REPEAT,(DWORD)(LPVOID)&mciPlayParams);
	else errorCode=mciSendCommand(wDeviceID,MCI_PLAY,MCI_NOTIFY,(DWORD)(LPVOID)&mciPlayParams);
	//std::cout<<"Sound Play Error code :"<<errorCode<<std::endl;
}

void SOUND_UTIL::Change_Sound(int type_of_source,const char* filename){
	Close_Sound();
	Init_Sound(type_of_source,filename);
}


