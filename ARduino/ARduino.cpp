
// ============================================================================
//	Includes
// ============================================================================

#include <stdio.h>
#include <stdlib.h>					// malloc(), free()
#include <string.h>
#include <math.h>
#include "SOUND_UTIL.h"

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
#include "text3d.h"
#include "Light.h"
#include "Vector.h"
#include "Quaternion.h"
#include "Time_T.h"
#include "Move.h"
#include "Cat_model.h"
#include "Check_object.h"
#include "Color_tracking.h"
#include "Object_Draw.h"
#include "Action.h"
#include "Body.h"

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
char            *model_name = "Data/object_data2"; //��Ŀ�� ���, �� ������ �̿��ؼ� object.cpp���� ó�� 
ObjectData_T    *object[2];
int             objectnum;

int             xsize, ysize;
int				thresh = 100;	//default = 100
int             count1 = 0;

/* set up the video format globals */

#ifdef _WIN32
char			*vconf = "Data\\WDM_camera_flipV.xml"; //ī�޶� config �ҷ���
#else
char			*vconf = "";
#endif

char           *cparam_name    = "Data/camera_para.dat"; //ī�޶� ���� ���� �ҷ���
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


//IplImage* Left;		//���� ī�޶��� �����Ͱ� ����
IplImage* Right;	//������ ī�޶��� �����Ͱ� ����
IplImage* img;		//��ü ī�޶��� �����Ͱ� ����

//IplImage* Limg;		//���� ī�޶��� �����Ͱ� ����
IplImage* Rimg;		//������ ī�޶��� �����Ͱ� ����

IplImage * R;		//Rä�� ���� ����
IplImage * G;		//Gä�� ���� ����
IplImage * B;		//Bä�� ���� ����
IplImage * RGB;		//RGBä�� ���� ����

//CvCapture* cap1;	//���� ī�޶�κ��� ������ �޾ƿ��� ���� ����
CvCapture* cap2;	//������ ī�޶�κ��� ������ �޾ƿ��� ���� ����

//ARUint8* LdataPtr;	//ARtoolkit(���� AR)�� �̹��� ������ ����
ARUint8* RdataPtr;	//ARtoolkit(���� AR)�� �̹��� ������ ����
ARUint8* dataPtrGL; //ARtoolkit(���� AR)�� �̹��� ������ ����

int opt;			//�ɼ� 0 : 2���� ī�޶� �Է�, 1 : �ϳ��� ī�޶� �Է� //����: LED �� ��⺯ȭ(LED on/off) 



int main(int argc, char **argv)
{
	glutInit(&argc, argv);
    init();			//�ʱ�ȭ ����
	//arVideoCapStart();		// (�����) �ⲯ OpenCV->ARToolKit ȯ�游������ �� �̰� �־�

    argMainLoop( NULL, keyEvent, mainLoop ); //���η����� �ѹ����� ����ɶ����� ������ ����

	return 0;
}

/* main loop */
static void mainLoop(void)
{
	if(opt == 0) //�ɼ� 0 : 2���� ī�޶� �Է�
	{
		//cvGrabFrame( cap1 );						// ī�޶�1�κ��� �� �������� ������
		//Left = cvRetrieveFrame( cap1 );				//Left�� �̹��� ������ ����
		cvGrabFrame( cap2 );						// ī�޶�2�κ��� �� �������� ������
		Right = cvRetrieveFrame( cap2 );			//Right�� �̹��� ������ ����
		//cvSplit(Left,0,0,R,0);						//Left�̹����� Red ä���� R�� ����
		//cvSplit(Right,B,G,0,0);						//Right�̹����� Green, Blue ä���� G, B�� ����
		//cvMerge(B,G,R,0,RGB);						//R,G,B�� ���� �����͸� RGB�� �����Ͽ� ���� (���� ��º�)
		//cvCvtColor(Left,Limg,CV_BGR2BGRA);			//CV->AR�� ������ ������ ���ؼ� 4ä�η� ��������
	}
	else if(opt = 1) //�ɼ� 1 : 1���� ī�޶� �Է�
	{
		cvGrabFrame( cap2 );						//ī�޶�κ��� �� �������� ������
		Right = cvRetrieveFrame( cap2 );			//Right�� �̹��� ������ ����
		cvSplit(Right,B,G,R,0);						//Right�̹����� Red, Green, blue ä����R, G, B�� ����
		cvMerge(B,G,R,0,RGB);						//R,G,B�� ���� �����͸� RGB�� �����Ͽ� ���� (���� ��º�)
		//printf("Debug %d \n", __LINE__);
	}
	
    if( count1 == 0 ) arUtilTimerReset();			// ARToolKit Ÿ�̸� ����
		count1++;

	cvCvtColor(Right,Rimg,CV_BGR2BGRA);				//CV->AR�� ������ ������ ���ؼ� 4ä�η� ��������(�߿�!) CV_BGRA2BGR
													//CV_BGR2BGRA A���� Alphaä�α��� �ؼ� 4ä�μӼ��� �شٴ� ���ε�

	Callback_ColorDetect(Right);					//��Ŀ�� �ν��ѵ� �󺧸���.

	setMarkerTrans(&Col_marker[0], &R_blob);		//����Ŀ�� ��ġ ���� 0 = ������Ŀ, 1 = �Ķ���Ŀ
	setMarkerTrans(&Col_marker[1], &B_blob);
	


	//----�Ķ� ��Ŀ �󺧸� ǥ��-----
	/*for( int i=0; i < B_blob.m_nBlobs; i++ )
	{
		CvPoint	pt1 = cvPoint(	B_blob.m_recBlobs[i].x,				
								B_blob.m_recBlobs[i].y );
		CvPoint pt2 = cvPoint(	pt1.x + B_blob.m_recBlobs[i].width,	
								pt1.y + B_blob.m_recBlobs[i].width );
		CvScalar color	= cvScalar( 255, 0, 0 );
		cvDrawRect( RGB, pt1, pt2, color );
	}*/


	//�÷���Ŀ�� �������� ���� ǥ��
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

	RdataPtr = (ARUint8*)Rimg->imageData;		//CV->AR�� ������ ��ȯ
	dataPtrGL = (ARUint8*)img->imageData;

	if(opt == 0)
	{
		//LdataPtr = (ARUint8*)Limg->imageData;
	}

	/*draw the video*/
    argDrawMode2D();							 //(2���� �������� ��) 2DȤ�� 3D�������� �ϱ� ���� ī�޶� �Ű������� ����
    argDispImage( dataPtrGL, 0,0 );				 //AR�� ���� ���


	check_Cmarker(&Col_marker[0], object[0][0]); //�ش� ��Ŀ�� ��ġ�� ĳ������ ��ġ�� ���� ����
	check_Cmarker(&Col_marker[1], object[0][0]);

	if(opt == 0)
	{
		//ArCvGl(LdataPtr, 1);					//���� �̹��� ��Ŀ �ν� �� OpenGL Draw
	}
	ArCvGl(RdataPtr, 0);						//������ �̹��� ��Ŀ �ν� �� OpenGL Draw
	
	argSwapBuffers();							//���ۿ� ����� �̹��� ���
	
}

/*
	Ű �̺�Ʈ�� �޾Ƽ� ó��
*/
static void   keyEvent( unsigned char key, int x, int y)   
{
    /* ESC������ ������ ����� ���� */
    if( key == 0x1b ) {
        printf("*** %f (frame/sec)\n", (double)count1/arUtilTimer());
        cleanup();
        exit(0);
    }
	// 1�� ������ �ϳ��� ķ���θ� �Է�
    if( key == '1' ) 
	{
        opt = 1;
    }
	// 0�� ������ 2���� ķ���� �Է�
    if( key == '0' ) 
	{
        opt = 0;
    }
}

/*
	�̹������� ��Ŀ�� ã��
	ã�� ��Ŀ�� ��ġ�� 3D ��ǥ�� ��ȯ
*/
void ArCvGl(ARUint8* dataPtr, int eye)
{
    ARMarkerInfo    *marker_info;	//��Ŀ�� ������ ����
    int             marker_num;		//��Ŀ�� ��
    int             i,j,k;
	
	if(i = arDetectMarker(dataPtr, thresh, &marker_info, &marker_num) < 0 ) {
		cleanup(); 
		exit(0);
	}

    for( i = 0; i < objectnum; i++ ) 
	{
		k = -1;
		for( j = 0; j < marker_num; j++ ) 
		{
	        if( object[eye][i].id == marker_info[j].id) 
			{
				if( k == -1 ) k = j;	// ù��° AR��Ŀ �ν�
		        else 
					if( marker_info[k].cf < marker_info[j].cf ) k = j;	// �νĵ� AR��Ŀ�� ���� ������ �������Ͽ� ��Ī
			}
		}
		if( k == -1 ) 
		{
			object[eye][i].visible = 0;
			continue;
		}
		
		if( object[eye][i].visible == 0 ) 
		{ 
			// Get the transformation between the marker and the real camera into gPatt_trans.
			// �� �� �ǹ�: �̹� ã�Ƶ� AR��Ŀ�� ������ �����ص� AR��Ŀ�� �߽ɰ� ũ��, transmation matrix�� �̿��Ͽ�,
			// ���� ī�޶� �Է¹��� ���󿡼� '��Ŀ�� ��ġ'�� �˻��Ͽ� TransMatrix�� �����Ѵ�.
			arGetTransMat(&marker_info[k],object[eye][i].marker_center, object[eye][i].marker_width, object[eye][i].trans);
        }
        else 
		{
			//�� ������ �Ȱ��� ����̴�. �������� ���� �������� ����� �����ϴ� ��� ���͸�(��ó�� ����)�� ���ϴ�(less jittering).
            arGetTransMatCont(&marker_info[k], object[eye][i].trans, object[eye][i].marker_center, object[eye][i].marker_width, object[eye][i].trans);
        }
        object[eye][i].visible = 1;
	}

    draw(object[eye], objectnum, eye); //3D ������Ʈ�� �׷���


	/*
		��Ŀ�� ���ῡ ���� ĳ������ �ൿ ��ȯ Action.h�� ����
		state = 0 : �������� ���ƴٴ�
		state = 1 : �ڽ��� ã�� �ٴ�
		state = 2 : ���� ��Ŀ�� ã�� �ٴ�
		state = 3 : 2���� ���� ��Ŀ�� �ν�
	*/
	if(eye == 0)
	{
		if( object[eye][0].visible > 0 && object[eye][1].visible > 0 && Col_marker[0].visible == 0) 
		{
			double  wmat1[3][4], wmat2[3][4];

			arUtilMatInv(object[eye][0].trans, wmat1); //�ش� ��Ŀ�� �߽� ��Ŀ�� ����
			arUtilMatMul(wmat1, object[eye][1].trans, wmat2); //�߽ɸ�Ŀ�� �߽����� 2��° ��Ŀ ��ġ ����
			//AR�� OpenGL�� ��ǥ���� ���� ������ ������ ���� �Ѱ���.
			b_draw.ar_trs[0] = -wmat2[0][3];
			b_draw.ar_trs[1] = wmat2[2][3];
			b_draw.ar_trs[2] = wmat2[1][3];
			state = 1; //�� ��Ŀ �νĽ� find_boxȣ��
		}
		else if( object[eye][0].visible > 0 && Col_marker[0].visible > 0  && Col_marker[1].visible != 1 )
		{
			double  wmat1[3][4], wmat2[3][4];

			arUtilMatInv(object[eye][0].trans, wmat1);
			arUtilMatMul(wmat1, Col_marker[0].trans, wmat2);
			Col_marker[0].ar_trs[0] = -wmat2[0][3];
			Col_marker[0].ar_trs[1] = wmat2[2][3];
			Col_marker[0].ar_trs[2] = wmat2[1][3];
			state = 2; //���� ��Ŀ �νĽ� find_markerȣ��
		}
		else if( object[eye][0].visible > 0 && Col_marker[0].visible > 0 && Col_marker[1].visible > 0 )
		{
			double  wmat1[3][4], wmat2[3][4], wmat3[3][4];

			arUtilMatInv(object[eye][0].trans, wmat1);
			arUtilMatMul(wmat1, Col_marker[0].trans, wmat2);
			Col_marker[0].ar_trs[0] = -wmat2[0][3];
			Col_marker[0].ar_trs[1] = wmat2[2][3];
			Col_marker[0].ar_trs[2] = wmat2[1][3];
			arUtilMatMul(wmat1, Col_marker[1].trans, wmat3);
			Col_marker[1].ar_trs[0] = -wmat3[0][3];
			Col_marker[1].ar_trs[1] = wmat3[2][3];
			Col_marker[1].ar_trs[2] = wmat3[1][3];
			state = 3; //�� ��Ŀ �νĽ� find_markerȣ��
		}
		else
		{
			state = 0; //�ϳ��� ��Ŀ �νĽ� ac_random ȣ��
		}
	}
}

/*
	�÷���Ŀ�� ĳ���Ϳ��� ���� �����ְ�
	�÷���Ŀ�� �׸��ڸ� ǥ��
*/
void check_Cmarker(ObjectData_T *object, ObjectData_T obj_trs)
{
	if(object->visible == 1)
	{
		obj_angle(cm.trs, cm.rot, object->ar_trs, object->ar_rot);
		//�׸��� ǥ��(������Ÿ�� �׽�Ʈ�ÿ��� ���, ���� ��º������� �ּ�ó��)
		/*double  gl_para[16];
	       
		glClear(GL_DEPTH_BUFFER_BIT);
		argConvGlpara(obj_trs.trans, gl_para); //����� ������Ʈ�� ī�޶� ������ �Ÿ��� OpenGL�� ��Ʈ������ ��ȯ 
		argDrawMode3D();
		argDraw3dCamera( 0, 0 );
	    
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixd( gl_para );
		//------------------------------------- ��ġ ����, �������� ����!(Artoolkit ���� �Լ�)
		
		//---------------������ ������ �Ǵ� �κ�---------
		//obj_id�� ��Ŀ�� �ѹ��� ��
		Light_Position_Setting(); //����Ʈ ��ġ ����
		Light_Color_Setting(); //����Ʈ�� ���� ����

			glPushMatrix();
				glRotatef(90, 1, 0, 0);
				glTranslatef(-object->ar_trs[0],0,-object->ar_trs[2]);
				glPushMatrix(); //�׸��� ����
					glDisable(GL_LIGHTING); //������ ��
					glDisable(GL_DEPTH_TEST); //���� üũ ��
					glColor3f(0.3,0.3,0.3); //�׸��� ����(ȸ��)
					glDisable(GL_TEXTURE_2D); //�ؽ��� ��
					glShadowProjectionPOINT(sun_position, planePoint, planeNormal); //(������ġ, ����, ����)
					glutSolidSphere(30,10,10);
					glColor3f(1,1,1);
					glEnable(GL_LIGHTING);
					glEnable(GL_TEXTURE);
					glEnable(GL_DEPTH_TEST);
				glPopMatrix();
				glColor3f(1.0f,1.0f,1.0f);// white !
				glEnable(GL_TEXTURE_2D);
			glPopMatrix();
			
					//glutSolidSphere(30,10,10);
		//-----------------------------------------------
		argDrawMode2D();*/
	}
}

/*
	���α׷� �ʱ�ȭ �Լ� ���۽� �ѹ��� ����, 
	�ϵ���� ���ð� OpenGL �ʱ�ȭ�̱� ������ ���� ���ʿ�� ����.
	�� ���� ����κ��� �߸� �ɵ�� �޸� ���� �߻�.
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

	// �ܺ� ������ ���Ͽ��� ��Ŀ ������ �о��.
	// 2���� ī�޶� ����ϱ� ������ �ϳ��� ��Ŀ�� 2���� ������ ����
	//for(int i = 0; i < 2; i++)
	{
		if( (object[0]=read_ObjData(model_name, &objectnum)) == NULL ) exit(0);
	}
    printf("Objectfile num = %d\n", objectnum);		//��Ŀ�� ���� ���
	
	
	//object[0]�� id���� 0~5�� �ʱ�ȭ object[1]�� id���� 6~11�� �ʱ�ȭ
	//object[0]�� [1]�� ����ȭ�� ���ؼ� [1]�� id���� 0~5�� �ʱ�ȭ
	
	/*
	for(int i = 0; i < 6; i++)
	{
		object[1][i].id = i;
	}
	*/

	//Col_marker�� ���� ��Ŀ
	//���� ��Ŀ ���� �ʱ�ȭ
	for(int i = 0; i < 2; i++)
	{
		Col_marker[i].id = 0;
		Col_marker[i].marker_center[0] = 0;
		Col_marker[i].marker_center[1] = 0;
		Col_marker[i].marker_center[2] = 0;
		Col_marker[i].marker_width = 15*(200/148); //����� ���� ��ġ�� �޶�����. 15�� ��Ŀ�� ũ��(mm)�� �ǹ�
		Col_marker[i].visible = 0;
	}
	
    /* open the graphics window */
    argInit( &cparam, 1.0, 0, 0, 0, 0 );

	/* 
		arVideo�� ������� �ʱ� ������ 
		�ʱ�ȭ �Ͽ� �׷��� �����츸 �����ְ�
		���� ������ ������
		���� ������ OpenCV�� �þƼ� ��.
   */
	arVideoCapStop();
    arVideoClose();

	opt = 1;
	//cvGrabFrame( cap1 );					// ī�޶�κ��� �� �������� ����ϴ�.
    //Left = cvRetrieveFrame( cap1 );			//Left�� �̹��� ������ ����
	cvGrabFrame( cap2 );					// ī�޶�κ��� �� �������� ����ϴ�.
    Right = cvRetrieveFrame( cap2 );		//Right�� �̹��� ������ ����
	
	R = cvCreateImage(cvSize(xsize,ysize), IPL_DEPTH_8U, 1); //Rä�� ���� ����
	G = cvCreateImage(cvSize(xsize,ysize), IPL_DEPTH_8U, 1); //Gä�� ���� ����
	B = cvCreateImage(cvSize(xsize,ysize), IPL_DEPTH_8U, 1); //Bä�� ���� ����
	RGB = cvCreateImage(cvSize(xsize,ysize), IPL_DEPTH_8U, 3); //RGBä�� ���� ����
	img = cvCreateImage(cvSize(xsize,ysize), IPL_DEPTH_8U, 4); //RGBä�� ���� ����(ARToolKit�ڵ�� 4ä��)
	//Limg = cvCreateImage(cvSize(xsize,ysize), IPL_DEPTH_8U, 4); //RGBä�� ���� ����
	Rimg = cvCreateImage(cvSize(xsize,ysize), IPL_DEPTH_8U, 4); //RGBä�� ���� ����
	blob_img = cvCreateImage(cvSize(xsize,ysize), IPL_DEPTH_8U, 3); //RGBä�� ���� ����;
	C_B = cvCreateImage(cvSize(xsize,ysize), IPL_DEPTH_8U, 3); //RGBä�� ���� ����;
	blob_R = cvCreateImage(cvSize(xsize,ysize), IPL_DEPTH_8U, 1); //Rä�� ���� ����
	blob_B = cvCreateImage(cvSize(xsize,ysize), IPL_DEPTH_8U, 1); //Gä�� ���� ����
	blob_RGB = cvCreateImage(cvSize(xsize,ysize), IPL_DEPTH_8U, 1); //RGBä�� ���� ����
	
	t3dInit();							//3D ���� �ʱ�ȭ

	//------------OpenGL �ʱ�ȭ-------------------

	Init2DTextures();					//�ؽ��� �ʱ�ȭ
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH);
	glDepthFunc(GL_LEQUAL);
	Light_Color_Setting();
	//cap1 = cvCaptureFromCAM(0);			//0��(����) ī�޶� �ڵ��� ����
	cap2 = cvCaptureFromCAM(1);			//1��(������) ī�޶� �ڵ��� ����
}

/* 
	���α׷� ����� ȣ��
	�޸� ��ȯ
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

/* draw the the AR objects */
static int draw( ObjectData_T *En_obj, int objectnum, int j )
{
    int     i;
    double  gl_para[2][16];
       
	glClearDepth( 1.0 );
    glClear(GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_LIGHTING);

    /* calculate the viewing parameters - gl_para */
    for( i = 0; i < objectnum; i++ ) {
        if( En_obj[i].visible == 0 ) 
		{
			continue;
		}
        argConvGlpara(En_obj[i].trans, gl_para[j]); //����� ������Ʈ�� ī�޶� ������ �Ÿ��� OpenGL�� ��Ʈ������ ��ȯ 
        draw_object( En_obj[i].id, gl_para[j], j);
    }
     
	glDisable( GL_LIGHTING );
    glDisable( GL_DEPTH_TEST );
	
    return(0);
}

void select_obj_marker(int obj_id)
{
	if(obj_id == 0) //1�� ��Ŀ
	{
		glPushMatrix();
			ac_action(); //ĳ���� ��� �� AI
		glPopMatrix();
	}
	else if(obj_id == 1) //2�� ��Ŀ
	{
		glPushMatrix();
			ac_box();	//�ڽ� ���
		glPopMatrix();
	}
}

/* 
	���������� OpenGL�� ���������ִ� �κ�
*/
static int  draw_object( int obj_id, double gl_para[16], int j)
{
	//------------------------------------- ��ġ ����, �������� ����!(Artoolkit ���� �Լ�)
	argDrawMode3D();
	argDraw3dCamera( 0, 0 );
    
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixd( gl_para );
	//------------------------------------- ��ġ ����, �������� ����!(Artoolkit ���� �Լ�)
	
	//---------------������ ������ �Ǵ� �κ�---------
	//obj_id�� ��Ŀ�� �ѹ��� ��
	Light_Position_Setting();		//����Ʈ ��ġ ����
	Light_Color_Setting();			//����Ʈ�� ���� ����

	if(j == 0) // Red, Green, Blue ä��
	{
		glPushMatrix();
			glEnable(GL_DEPTH_TEST);
			glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
			glDepthMask(GL_FALSE);

			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);	// ���� ���� glColor4f (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);

			glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
			
			glDepthMask(GL_TRUE);
			//----------------------------------------------

			select_obj_marker(obj_id); //�ش� ��Ŀ�� ������Ʈ ���

			//----------------------------------------------
			glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
			glDisable(GL_LIGHTING);
			glDisable( GL_DEPTH_TEST );
		glPopMatrix();
	}
	else if(j == 1) //Red ä��
	{
		glPushMatrix();
			glEnable(GL_DEPTH_TEST);
			glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
			glDepthMask(GL_FALSE);

			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

			glColorMask(GL_TRUE, GL_FALSE, GL_FALSE, GL_TRUE);
			
			glDepthMask(GL_TRUE);
			//----------------------------------------------

			select_obj_marker(obj_id); //�ش� ��Ŀ�� ������Ʈ ���

			//----------------------------------------------
			glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
			glDisable(GL_LIGHTING);
			glDisable( GL_DEPTH_TEST );
		glPopMatrix();
	}
    argDrawMode2D();

    return 0;
}