/*
	텍스쳐
*/
#ifndef __TEXTURE__
#define __TEXTURE__
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gl/glut.h>
#include <gl/glu.h>
using namespace std;
float sh_color = 0.3; //그림자

GLuint text_cat_head[6], text_cat_body, text_cat_arms, text_cat_hand;
GLuint text_sp_bub[4];

typedef struct BMP_DATA{
	unsigned width, height;
	unsigned short planes;
	unsigned short bpp;
	unsigned char *data;
	bool isLoad;
}BMP_DATA;

BMP_DATA bmp_data, bmp_data1;

void BindTexture2D(BMP_DATA bmp_data, GLuint *texture){
	if(!bmp_data.isLoad){
		std::cout<<"Binding Error"<<std::endl;
		exit(0);
	}
	glDeleteTextures(1,texture);
	glGenTextures(1,texture);

	glBindTexture(GL_TEXTURE_2D,*texture);	
	glTexImage2D(GL_TEXTURE_2D,0,3,bmp_data.width,bmp_data.height,0,GL_RGB,GL_UNSIGNED_BYTE,bmp_data.data);
	
	//Property Setting here using glTexParameteri
	
	//---------------- 필터링 설정--------------------------
	//nearest filtering
	//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	//linear filtering
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	//mip-mapped filtering
	//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//gluBuild2DMipmaps(GL_TEXTURE_2D, 3, bmp_data.width, bmp_data.height, GL_RGB,GL_UNSIGNED_BYTE, bmp_data.data);
	//-------------------------------------------------------
	
	//---------------- 텍스쳐 씌우기 설정--------------------
	//Repeataion
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//clamping
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	//-------------------------------------------------------
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	if(bmp_data.data)
		delete[] bmp_data.data;
	glEnable(GL_TEXTURE_2D);
}

bool LoadBMP(const char *filename,BMP_DATA *bmp_data){
	unsigned short planes;
	unsigned short bpp;
	bmp_data->isLoad=false;
	ifstream bitmap_file(filename,ios::in|ios::binary);
	if(!bitmap_file)return false;
	bitmap_file.seekg(18,ios::cur);
	bitmap_file.read((char*)&bmp_data->width,sizeof(unsigned));
	bitmap_file.read((char*)&bmp_data->height,sizeof(unsigned));
	bitmap_file.read((char*)&bmp_data->planes,sizeof(unsigned short));
	bitmap_file.read((char*)&bmp_data->bpp,sizeof(unsigned short));
	bitmap_file.seekg(24,ios::cur);
	unsigned size(bmp_data->width*bmp_data->height*3);
	bmp_data->data = new unsigned char[size];
	bitmap_file.read((char*)bmp_data->data, size);
	unsigned char temp;
	for(int i(0);i<size;i+=3){						//change color sequence b,g,r -> r,g,b
		temp=bmp_data->data[i];
		bmp_data->data[i]=bmp_data->data[i+2];
		bmp_data->data[i+2]=temp;}
	bmp_data->isLoad=true;
	return true;
}

void Init2DTextures(){
	LoadBMP("Data/data/cat_head.bmp",&bmp_data);
	BindTexture2D(bmp_data,&text_cat_head[0]);
	LoadBMP("Data/data/cat_head_1.bmp",&bmp_data);
	BindTexture2D(bmp_data,&text_cat_head[1]);
	LoadBMP("Data/data/cat_head_2.bmp",&bmp_data);
	BindTexture2D(bmp_data,&text_cat_head[2]);
	LoadBMP("Data/data/cat_head_3.bmp",&bmp_data);
	BindTexture2D(bmp_data,&text_cat_head[3]);
	LoadBMP("Data/data/cat_head_4.bmp",&bmp_data);
	BindTexture2D(bmp_data,&text_cat_head[4]);
	LoadBMP("Data/data/cat_head_5.bmp",&bmp_data);
	BindTexture2D(bmp_data,&text_cat_head[5]);
	LoadBMP("Data/data/cat_body.bmp",&bmp_data);
	BindTexture2D(bmp_data,&text_cat_body);
	LoadBMP("Data/data/cat_arms.bmp",&bmp_data);
	BindTexture2D(bmp_data,&text_cat_arms);
	LoadBMP("Data/data/cat_hand.bmp",&bmp_data);
	BindTexture2D(bmp_data,&text_cat_hand);
	LoadBMP("Data/data/speech_bub_1.bmp",&bmp_data);
	BindTexture2D(bmp_data,&text_sp_bub[0]);
	LoadBMP("Data/data/speech_bub_2.bmp",&bmp_data);
	BindTexture2D(bmp_data,&text_sp_bub[1]);
	LoadBMP("Data/data/speech_!_1.bmp",&bmp_data);
	BindTexture2D(bmp_data,&text_sp_bub[2]);
	LoadBMP("Data/data/speech_!_2.bmp",&bmp_data);
	BindTexture2D(bmp_data,&text_sp_bub[3]);
}

#endif