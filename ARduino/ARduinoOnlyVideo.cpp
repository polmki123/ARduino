
// ============================================================================
//	Includes
// ============================================================================

#include <stdio.h>
#include <stdlib.h>					// malloc(), free()
#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif
#include <AR/config.h>
#include <AR/video.h>
#include <AR/param.h>			// arParamDisp()
#include <AR/ar.h>
//#include <AR/gsub_lite.h>
#include <AR/gsub.h>
#include <opencv\cv.h>
#include <opencv\highgui.h>

#include "object.h"
#include "Color_tracking.h"

/*
// ============================================================================
//	Constants
// ============================================================================

#define VIEW_SCALEFACTOR		0.025		// 1.0 ARToolKit unit becomes 0.025 of my OpenGL units.
#define VIEW_DISTANCE_MIN		0.1			// Objects closer to the camera than this will not be displayed.
#define VIEW_DISTANCE_MAX		100.0		// Objects further away from the camera than this will not be displayed.

// ============================================================================
//	Global variables
// ============================================================================

// Preferences.
static int prefWindowed = TRUE;
static int prefWidth = 640;					// Fullscreen mode width.
static int prefHeight = 480;				// Fullscreen mode height.
static int prefDepth = 32;					// Fullscreen mode bit depth.
static int prefRefresh = 0;					// Fullscreen mode refresh rate. Set to 0 to use default rate.

// Image acquisition.
static ARUint8		*gARTImage = NULL;

// Marker detection.
static int			gARTThreshhold = 100;
static long			gCallCountMarkerDetect = 0;

// Transformation matrix retrieval.
static double		gPatt_width     = 80.0;	// Per-marker, but we are using only 1 marker.
static double		gPatt_centre[2] = {0.0, 0.0}; // Per-marker, but we are using only 1 marker.
static double		gPatt_trans[3][4];		// Per-marker, but we are using only 1 marker.
static int			gPatt_found = FALSE;	// Per-marker, but we are using only 1 marker.
static int			gPatt_id;				// Per-marker, but we are using only 1 marker.

// Drawing.
static ARParam		gARTCparam;
static ARGL_CONTEXT_SETTINGS_REF gArglSettings = NULL;
static int gDrawRotate = FALSE;
static float gDrawRotateAngle = 0;			// For use in drawing.
*/



#define COLLIDE_DIST 30000.0

/* Object Data */
char            *model_name = "Data/object_data_0416"; //마커를 등록, 이 파일을 이용해서 object.cpp에서 처리
ObjectData_T    *object[2];
int             objectnum;

int             xsize, ysize;
int				thresh = 100;	//default = 100
int             count1 = 0;

/* set up the video format globals */

#ifdef _WIN32
char			*vconf = "Data\\WDM_camera_flipV.xml"; //카메라 config 불러옴
#else
char			*vconf = "";
#endif

char           *cparam_name    = "Data/camera_para.dat"; //카메라 셋팅 파일 불러옴
ARParam         cparam;

static void	  init(void);
static void   cleanup(void);
static void   keyEvent( unsigned char key, int x, int y);
static void   mainLoop(void);
static int	  draw( ObjectData_T *object, int objectnum, int num );
static int    draw_object( int obj_id, double gl_para[16], int j );
void		  ArCvGl(ARUint8* dataPtr, int eye);
void		  check_Cmarker(ObjectData_T *object, ObjectData_T obj_trs);
void		  select_obj_marker(int obj_id);


//IplImage* Left;		//왼쪽 카메라의 데이터가 저장
IplImage* Right;	//오른쪽 카메라의 데이터가 저장
IplImage* img;		//전체 카메라의 데이터가 저장

IplImage* Limg;		//왼쪽 카메라의 데이터가 저장
IplImage* Rimg;		//오른쪽 카메라의 데이터가 저장

IplImage * R;		//R채널 저장 변수
IplImage * G;		//G채널 저장 변수
IplImage * B;		//B채널 저장 변수
IplImage * RGB;		//RGB채널 통합 변수

//CvCapture* cap1;	//왼쪽 카메라로부터 영상을 받아오기 위한 변수
CvCapture* cap2;	//오른쪽 카메라로부터 영상을 받아오기 위한 변수

ARUint8* LdataPtr;	//ARtoolkit(이하 AR)의 이미지 데이터 변수
ARUint8* RdataPtr;	//ARtoolkit(이하 AR)의 이미지 데이터 변수
ARUint8* dataPtrGL; //ARtoolkit(이하 AR)의 이미지 데이터 변수

int opt;			//옵션 0 : 2개의 카메라 입력, 1 : 하나의 카메라 입력



int main(int argc, char **argv)
{
	glutInit(&argc, argv);
    init();			//초기화 수행
	arVideoCapStart();
	
    argMainLoop( NULL, keyEvent, mainLoop ); //메인루프에 한번들어가면 종료될때까지 나오지 않음

	return 0;
}

/* main loop */
static void mainLoop(void)
{
	if(opt == 0) //옵션 0 : 2대의 카메라 입력
	{
		//cvGrabFrame( cap1 );						// 카메라1로부터 한 프레임을 가져옴
		//Left = cvRetrieveFrame( cap1 );				//Left에 이미지 파일을 저장
		cvGrabFrame( cap2 );						// 카메라2로부터 한 프레임을 가져옴
		Right = cvRetrieveFrame( cap2 );			//Right에 이미지 파일을 저장
		//cvSplit(Left,0,0,R,0);						//Left이미지의 Red 채널을 R에 저장
		cvSplit(Right,B,G,0,0);						//Right이미지의 Green, Blue 채널을 G, B에 저장
		cvMerge(B,G,R,0,RGB);						//R,G,B의 영상 데이터를 RGB에 통합하여 저장 (최종 출력본)
		//cvCvtColor(Left,Limg,CV_BGR2BGRA);			//CV->AR로 데이터 변경을 위해서 4채널로 변경해줌
	}
	else if(opt = 1) //옵션 1 : 1대의 카메라 입력
	{
		cvGrabFrame( cap2 );						//카메라로부터 한 프레임을 가져옴
		Right = cvRetrieveFrame( cap2 );			//Right에 이미지 파일을 저장
		cvSplit(Right,B,G,R,0);						//Right이미지의 Red, Green, blue 채널을R, G, B에 저장
		cvMerge(B,G,R,0,RGB);						//R,G,B의 영상 데이터를 RGB에 통합하여 저장 (최종 출력본)
	}

	
    if( count1 == 0 ) arUtilTimerReset();			//몰라. <-??
		count1++;

	cvCvtColor(Right,Rimg,CV_BGR2BGRA);				//CV->AR로 데이터 변경을 위해서 4채널로 변경해줌(중요!)
	
	/*
	Callback_ColorDetect(Right);					//마커를 인식한뒤 라벨링함.

	setMarkerTrans(&Col_marker[0], &R_blob);		//색상마커의 위치 구함 0 = 빨간마커, 1 = 파란마커
	setMarkerTrans(&Col_marker[1], &B_blob);
	*/



	//----파란 마커 라벨링 표시-----
	/*for( int i=0; i < B_blob.m_nBlobs; i++ )
	{
		CvPoint	pt1 = cvPoint(	B_blob.m_recBlobs[i].x,				
								B_blob.m_recBlobs[i].y );
		CvPoint pt2 = cvPoint(	pt1.x + B_blob.m_recBlobs[i].width,	
								pt1.y + B_blob.m_recBlobs[i].width );
		CvScalar color	= cvScalar( 255, 0, 0 );
		cvDrawRect( RGB, pt1, pt2, color );
	}*/


	//컬러마커의 꼭지점에 점을 표시
	/*cvCircle( RGB, cvPoint(B_blob.Mark_corner[0].x, B_blob.Mark_corner[0].y), 2, CV_RGB(0,0,255), 2 );
	cvCircle( RGB, cvPoint(B_blob.Mark_corner[1].x, B_blob.Mark_corner[1].y), 2, CV_RGB(255,0,0), 2 );
	cvCircle( RGB, cvPoint(B_blob.Mark_corner[2].x, B_blob.Mark_corner[2].y), 2, CV_RGB(0,255,0), 2 );
	cvCircle( RGB, cvPoint(B_blob.Mark_corner[3].x, B_blob.Mark_corner[3].y), 2, CV_RGB(0,0,0), 2 );
	cvCircle( RGB, cvPoint(R_blob.Mark_corner[0].x, R_blob.Mark_corner[0].y), 2, CV_RGB(0,0,255), 2 );
	cvCircle( RGB, cvPoint(R_blob.Mark_corner[1].x, R_blob.Mark_corner[1].y), 2, CV_RGB(255,0,0), 2 );
	cvCircle( RGB, cvPoint(R_blob.Mark_corner[2].x, R_blob.Mark_corner[2].y), 2, CV_RGB(0,255,0), 2 );
	cvCircle( RGB, cvPoint(R_blob.Mark_corner[3].x, R_blob.Mark_corner[3].y), 2, CV_RGB(0,0,0), 2 );
	for(int i = 0; i < 2; i++)
	{
		int x1 = Mark_corner[i].x;
		int y1 = Mark_corner[i].y;
		int x2 = Mark_corner[2].x;
		int y2 = Mark_corner[2].y;
		int x3 = Mark_corner[3].x;
		int y3 = Mark_corner[3].y;

		cvLine( RGB, cvPoint(x1, y1), cvPoint(x2, y2), CV_RGB( 0, 0, 255), 1 );

		for( int m=0;   m < 3; m++ )
		for( int n=m+1; n < 4; n++ )
		{
			int x1 = Mark_corner[m].x + blob.m_recBlobs[0].x;
			int y1 = Mark_corner[m].y + blob.m_recBlobs[0].y;
			int x2 = Mark_corner[n].x + blob.m_recBlobs[0].x;
			int y2 = Mark_corner[n].y + blob.m_recBlobs[0].y;

			cvLine( RGB, cvPoint(x1, y1), cvPoint(x2, y2), CV_RGB( 0, 0, 255), 1 );
		}
	}*/

	cvCvtColor(RGB,img,CV_BGR2BGRA);

	RdataPtr = (ARUint8*)Rimg->imageData;		//CV->AR로 데이터 변환
	dataPtrGL = (ARUint8*)img->imageData;
	if(opt == 0)
	{
		LdataPtr = (ARUint8*)Limg->imageData;
	}

	/*draw the video*/
    argDrawMode2D();
    argDispImage( dataPtrGL, 0,0 );				//AR로 최종 출력

	/*
	check_Cmarker(&Col_marker[0], object[0][0]);//해당 마커의 위치와 캐릭터의 위치의 각을 구함
	check_Cmarker(&Col_marker[1], object[0][0]);

	if(opt == 0)
	{
		ArCvGl(LdataPtr, 1);					//왼쪽 이미지 마커 인식 및 OpenGL Draw
	}
	ArCvGl(RdataPtr, 0);						//오른쪽 이미지 마커 인식 및 OpenGL Draw
	*/
	argSwapBuffers();							//버퍼에 저장된 이미지 출력
	
}

/*
	키 이벤트를 받아서 처리
*/
static void   keyEvent( unsigned char key, int x, int y)   
{
    /* ESC누르면 프레임 출력후 종료 */
    if( key == 0x1b ) {
        printf("*** %f (frame/sec)\n", (double)count1/arUtilTimer());
        cleanup();
        exit(0);
    }
	// 1을 누르면 하나의 캠으로만 입력
    if( key == '1' ) 
	{
        opt = 1;
    }
	// 0을 누르면 2개의 캠으로 입력
    if( key == '0' ) 
	{
        opt = 0;
    }
}



/*
	프로그램 초기화 함수 시작시 한번만 수행, 
	하드웨어 세팅과 OpenGL 초기화이기 때문에 별로 알필요는 없음.
	단 변수 선언부분을 잘못 걸들면 메모리 누수 발생.
*/
static void init( void )
{
	ARParam  wparam;

    // open the video path
    if( arVideoOpen( vconf ) < 0 ) exit(0);
    // find the size of the window 
    if( arVideoInqSize(&xsize, &ysize) < 0 ) exit(0);
    printf("Image size (x,y) = (%d,%d)\n", xsize, ysize);

    // set the initial camera parameters
    if( arParamLoad(cparam_name, 1, &wparam) < 0 ) {
        printf("Camera parameter load error !!\n");
        exit(0);
    }
    arParamChangeSize( &wparam, xsize, ysize, &cparam );
    arInitCparam( &cparam );
    printf("*** Camera Parameter ***\n");
    arParamDisp( &cparam );

	// 외부 데이터 파일에서 마커 정보를 읽어옴.
	// 2대의 카메라를 사용하기 때문에 하나의 마커에 2개의 변수를 생성
	/*for(int i = 0; i < 2; i++)
	{
		if( (object[i]=read_ObjData(model_name, &objectnum)) == NULL ) exit(0);
	}*/
    printf("Objectfile num = %d\n", objectnum);		//마커의 개수 출력
	
	/*
	//object[0]은 id값이 0~5로 초기화 object[1]은 id값이 6~11로 초기화
	//object[0]과 [1]의 동기화를 위해서 [1]의 id값도 0~5로 초기화
	for(int i = 0; i < 6; i++)
	{
		object[1][i].id = i;
	}

	//Col_marker는 색상 마커
	//색상 마커 정보 초기화
	for(int i = 0; i < 2; i++)
	{
		Col_marker[i].id = 0;
		Col_marker[i].marker_center[0] = 0;
		Col_marker[i].marker_center[1] = 0;
		Col_marker[i].marker_center[2] = 0;
		Col_marker[i].marker_width = 15*(200/148); //사이즈에 따라 위치가 달라진다. 15는 마커의 크기(mm)를 의미
		Col_marker[i].visible = 0;
	}
	*/

    /* open the graphics window */
    argInit( &cparam, 1.0, 0, 0, 0, 0 );

	/* 
		arVideo는 사용하지 않기 때문에 
		초기화 하여 그래픽 윈도우만 열어주고
		비디오 연결은 해제함
		비디오 연결은 OpenCV가 맡아서 함.
   */
	arVideoCapStop();
    arVideoClose();

	opt = 1;
	//cvGrabFrame( cap1 );					// 카메라로부터 한 프레임을 잡습니다.
    //Left = cvRetrieveFrame( cap1 );			//Left에 이미지 파일을 저장
	cvGrabFrame( cap2 );					// 카메라로부터 한 프레임을 잡습니다.
    Right = cvRetrieveFrame( cap2 );		//Right에 이미지 파일을 저장
	
	R = cvCreateImage(cvSize(xsize,ysize), IPL_DEPTH_8U, 1); //R채널 저장 변수
	G = cvCreateImage(cvSize(xsize,ysize), IPL_DEPTH_8U, 1); //G채널 저장 변수
	B = cvCreateImage(cvSize(xsize,ysize), IPL_DEPTH_8U, 1); //B채널 저장 변수
	RGB = cvCreateImage(cvSize(xsize,ysize), IPL_DEPTH_8U, 3); //RGB채널 통합 변수
	img = cvCreateImage(cvSize(xsize,ysize), IPL_DEPTH_8U, 4); //RGB채널 통합 변수
	Limg = cvCreateImage(cvSize(xsize,ysize), IPL_DEPTH_8U, 4); //RGB채널 통합 변수
	Rimg = cvCreateImage(cvSize(xsize,ysize), IPL_DEPTH_8U, 4); //RGB채널 통합 변수
	blob_img = cvCreateImage(cvSize(xsize,ysize), IPL_DEPTH_8U, 3); //RGB채널 통합 변수;
	C_B = cvCreateImage(cvSize(xsize,ysize), IPL_DEPTH_8U, 3); //RGB채널 통합 변수;
	blob_R = cvCreateImage(cvSize(xsize,ysize), IPL_DEPTH_8U, 1); //R채널 저장 변수
	blob_B = cvCreateImage(cvSize(xsize,ysize), IPL_DEPTH_8U, 1); //G채널 저장 변수
	blob_RGB = cvCreateImage(cvSize(xsize,ysize), IPL_DEPTH_8U, 1); //RGB채널 통합 변수
		
	//t3dInit();							//3D 글자 초기화

	//------------OpenGL 초기화-------------------

	//Init2DTextures();					//텍스쳐 초기화
	//glEnable(GL_DEPTH_TEST);
	//glEnable(GL_COLOR_MATERIAL);
	//glShadeModel(GL_SMOOTH);
	//glDepthFunc(GL_LEQUAL);
	//Light_Color_Setting();
	//cap1 = cvCaptureFromCAM(0);			//0번(왼쪽) 카메라 핸들을 얻어옴
	cap2 = cvCaptureFromCAM(1);			//1번(오른쪽) 카메라 핸들을 얻어옴
}

/* 
	프로그램 종료시 호출
	메모리 반환
*/
static void cleanup(void)
{
	arVideoCapStop();
    arVideoClose();
    argCleanup();
	//cvReleaseImage( &Left );
	cvReleaseImage( &Right );
	//cvReleaseCapture( &cap1 );
	cvReleaseCapture( &cap2 );
	cvReleaseImage( &R );
	cvReleaseImage( &G );
	cvReleaseImage( &B );	
	cvReleaseImage( &RGB );
	cvDestroyAllWindows();
}

