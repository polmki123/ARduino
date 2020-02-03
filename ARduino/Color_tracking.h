/*
	컬러 마커를 트래킹함
*/
#ifndef __COLORTRACKING__
#define __COLORTRACKING__
#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <gl/glut.h>
#include "BlobLabeling.h"

int r_trs[4][2];
//ObjectData_T Red_marker;
//ObjectData_T R_marker;
//ObjectData_T Blue_marker;
ObjectData_T Col_marker[2];
IplImage * blob_img;
IplImage * C_B;
IplImage * blob_R;
IplImage * blob_B;
IplImage * blob_RGB;
CBlobLabeling R_blob;
CBlobLabeling B_blob;


void cvShow(char *win_name, IplImage *img, int width=0, int height=0)
{
	if(width==0){
		cvNamedWindow( win_name, 1);
	} else{
		cvNamedWindow( win_name, 0);
		cvResizeWindow( win_name, width, height);
	}
	cvShowImage( win_name, img );
}

void setMarkerInfo( int updown, double cx, double cy, int area, ARMarkerInfo *marker_info ,CvPoint2D32f vertex[4])
{
    double line[4][3];
    double x[4],y[4];

    marker_info->id = 3;
    marker_info->dir = updown; //0일때: 앞 코부분, 1일 때: 밑바닥, 2일때: 밑바닥2, 3일때: 뒷부분
    marker_info->cf = 1;
    marker_info->pos[0] = cx;
    marker_info->pos[1] = cy;

    for (int i = 0;i<4;i++){
        x[i] = vertex[i].x;
        y[i] = vertex[i].y;
    }
	/*
        직선상의 두 점 (x1,y1), (x2,y2)를 알고 있을 때 
        Ax + By +c = 0 을 구하는 공식
        (y1-y2)x + (x2-x1)y + (x1y2 - x2y1) = 0
    */
    line[0][0] = y[0]-y[1];
    line[0][1] = x[1]-x[0];
    line[0][2] = (x[0]*y[1])-(x[1]*y[0]);

    line[1][0] = y[1]-y[2];
    line[1][1] = x[2]-x[1];
    line[1][2] = (x[1]*y[2])-(x[2]*y[1]);

    line[2][0] = y[2]-y[3];
    line[2][1] = x[3]-x[2];
    line[2][2] = (x[2]*y[3])-(x[3]*y[2]);

    line[3][0] = y[3]-y[0];
    line[3][1] = x[0]-x[3];
    line[3][2] = (x[3]*y[0])-(x[0]*y[3]);    

    marker_info->line[0][0] = line[0][0];
    marker_info->line[0][1] = line[0][1];
    marker_info->line[0][2] = line[0][2];
    
    marker_info->line[1][0] = line[1][0];
    marker_info->line[1][1] = line[1][1];
    marker_info->line[1][2] = line[1][2];
    
    marker_info->line[2][0] = line[2][0];
    marker_info->line[2][1] = line[2][1];
    marker_info->line[2][2] = line[2][2];
    
    marker_info->line[3][0] = line[3][0];
    marker_info->line[3][1] = line[3][1];
    marker_info->line[3][2] = line[3][2];
    
    marker_info->vertex[0][0] = vertex[0].x;
    marker_info->vertex[0][1] = vertex[0].y;

    marker_info->vertex[1][0] = vertex[1].x;
    marker_info->vertex[1][1] = vertex[1].y;

    marker_info->vertex[2][0] = vertex[2].x;
    marker_info->vertex[2][1] = vertex[2].y;

    marker_info->vertex[3][0] = vertex[3].x;
    marker_info->vertex[3][1] = vertex[3].y;

	marker_info->area = area/2;
    return;
}

void Labeling(IplImage *img)
{
	
	int b_trs[4][2] = {0,0,640,0,0,0,0,0};
	int index;
	for(int i = 0; i < img->height; i++)
	{
		for(int j = 0; j < img->widthStep; j += img->nChannels)
		{
			index = i*img->widthStep + j;
			if(((unsigned char)img->imageData[index] > 200)) //&& ((unsigned char)Left->imageData[index+2] > 90) && ((unsigned char)Left->imageData[index] > 90))
			{
				if(b_trs[0][0] == 0)
				{
					b_trs[0][0] = j;
					b_trs[0][1] = i;
					r_trs[0][0] = j;
					r_trs[0][1] = i;
				}
				if(b_trs[1][0] > j)
				{
					b_trs[1][0] = j;
					b_trs[1][1] = i;
					r_trs[1][0] = j;
					r_trs[1][1] = i;
				}
				if(b_trs[2][0] < j)
				{
					b_trs[2][0] = j;
					b_trs[2][1] = i;
					r_trs[2][0] = j;
					r_trs[2][1] = i;
				}
				if(b_trs[3][1] < i)
				{
					b_trs[3][0] = j;
					b_trs[3][1] = i;
					r_trs[3][0] = j;
					r_trs[3][1] = i;
				}

			}
		}
	}	
}


void setMarkerTrans(ObjectData_T *S_marker, CBlobLabeling *S_blob)
{
	ARMarkerInfo marker_info; //마커의 정보가 저장
	if(S_blob->m_nBlobs == 0)
	{
		S_marker->visible = 0;
		return;
	}

	for( int i=0; i < S_blob->m_nBlobs; i++ )
	{
		CvPoint	pt1 = cvPoint(	S_blob->m_recBlobs[i].x,				
								S_blob->m_recBlobs[i].y );
		CvPoint pt2 = cvPoint(	pt1.x + S_blob->m_recBlobs[i].width,	
								pt1.y + S_blob->m_recBlobs[i].height);
		CvPoint pt3 = cvPoint((pt1.x + pt2.x)/2, (pt1.y + pt2.y)/2);
		CvPoint2D32f pt_rect[4];
		pt_rect[0].x = pt1.x;
		pt_rect[0].y = pt1.y;
		pt_rect[1].x = pt2.x;
		pt_rect[1].y = pt1.y;
		pt_rect[2].x = pt2.x;
		pt_rect[2].y = pt2.y;
		pt_rect[3].x = pt1.x;
		pt_rect[3].y = pt2.y;
		/*pt_rect[0].x = S_blob->Mark_corner[0].x;
		pt_rect[0].y = S_blob->Mark_corner[0].y;
		pt_rect[1].x = S_blob->Mark_corner[2].x;
		pt_rect[1].y = S_blob->Mark_corner[2].y;
		pt_rect[2].x = S_blob->Mark_corner[1].x;
		pt_rect[2].y = S_blob->Mark_corner[1].y;
		pt_rect[3].x = S_blob->Mark_corner[3].x;
		pt_rect[3].y = S_blob->Mark_corner[3].y;*/
		int area = (pt1.x - pt2.x)*(pt1.y - pt2.y);

		setMarkerInfo(1,pt3.x,pt3.y, area, &marker_info, pt_rect);
		
		if( S_marker->visible == 0 ) 
		{
            arGetTransMat(&marker_info,S_marker->marker_center, S_marker->marker_width, S_marker->trans);
        }
        else 
		{
            arGetTransMatCont(&marker_info, S_marker->trans, S_marker->marker_center, S_marker->marker_width, S_marker->trans);
        }
        S_marker->visible = 1;
	}
}
void Marker_Rect(CBlobLabeling *blob)
{
	CvPoint		corner[4];
	for( int i=0; i < blob->m_nBlobs; i++ )
	{

	CvMemStorage* storage	= cvCreateMemStorage(0);
	CvSeq* contours			= 0;

	// 1. 윤곽 검출
	int mw	= blob->m_recBlobs[i].width;
	int mh	= blob->m_recBlobs[i].height;

	IplImage* marker = cvCreateImage( cvSize(mw, mh), 8, 1 );

	blob->GetBlobImage( marker, i );

	cvFindContours( marker, storage, &contours, sizeof (CvContour), CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);

	// 2. 윤곽선 표시 및 윤곽선 영상 생성
	//				cvDrawContours( m_pImage, contours, CV_RGB (255, 255, 0), CV_RGB (0, 255, 0), -1, 1, CV_AA, cvPoint (blob.m_recBlobs[i].x, blob.m_recBlobs[i].y));

	// 3. 꼭지점 추출
	int x;

	double fMaxDist;


	for( x=0; x < 4; x++ )		corner[x] = cvPoint(0, 0);

	// 초기 위치 설정
	CvPoint *st  = (CvPoint *)cvGetSeqElem( contours, 0 );

	corner[0].x = st->x;
	corner[0].y = st->y;
	// 첫 번 째 꼭지점 추출(최대 거리를 가지는 점 선택)
	fMaxDist = 0.0;
	for( x = 1; x < contours->total; x++ )
	{
		CvPoint* pt = (CvPoint *)cvGetSeqElem( contours, x );

		double fDist = sqrt( (double)(( st->x - pt->x ) * ( st->x - pt->x ) + ( st->y - pt->y ) * ( st->y - pt->y ) ));

		if( fDist > fMaxDist )
		{
			corner[1] = *pt;

			fMaxDist = fDist;
		}
	}
	
	// 세 번 째 꼭지점 추출(첫 번 째, 두 번 째 꼭지점에서 최대 거리를 가지는 점 선택)
	fMaxDist = 0.0;

	for( x = 0; x < contours->total; x++ )
	{
		CvPoint* pt = (CvPoint *)cvGetSeqElem( contours, x );

		double fDist =		sqrt( (double)(( corner[0].x - pt->x ) * ( corner[0].x - pt->x ) + ( corner[0].y - pt->y ) * ( corner[0].y - pt->y ) ))
						+	sqrt( (double)(( corner[1].x - pt->x ) * ( corner[1].x - pt->x ) + ( corner[1].y - pt->y ) * ( corner[1].y - pt->y ) ));

		if( fDist > fMaxDist )
		{
			corner[2] = *pt;

			fMaxDist = fDist;
		}
	}
	// 네 번 째 꼭지점 추출
	// (벡터 내적을 이용하여 좌표평면에서 사각형의 너비의 최대 값을 구한다.)
	//														 
	int x1 = corner[0].x;	int y1 = corner[0].y;			
	int x2 = corner[1].x;	int y2 = corner[1].y;
	int x3 = corner[2].x;	int y3 = corner[2].y;

	int nMaxDim = 0;

	for( x = 0; x < contours->total; x++ )
	{
		CvPoint* pt = (CvPoint *)cvGetSeqElem( contours, x );

		int x = pt->x;
		int y = pt->y;

		int nDim =		abs( ( x1 * y2 + x2 * y  + x  * y1 ) - ( x2 * y1 + x  * y2 + x1 * y  ) )
					+	abs( ( x1 * y  + x  * y3 + x3 * y1 ) - ( x  * y1 + x3 * y  + x1 * y3 ) )
					+	abs( ( x  * y2 + x2 * y3 + x3 * y  ) - ( x2 * y  + x3 * y2 + x  * y3 ) );

		if( nDim > nMaxDim )
		{
			corner[3] = *pt;

			nMaxDim = nDim;
		}
	}

	if(corner[0].x < corner[2].x || corner[1].x < corner[2].x)
	{
	}
	else
	{
		CvPoint pt = corner[3];
		corner[3] = corner[2];
		corner[2] = pt;
	}

	/*
	for( x = 1; x < contours->total; x++ )
	{
		CvPoint* pt = (CvPoint *)cvGetSeqElem( contours, x );

		double fDist = sqrt( (double)(( st->x - pt->x ) * ( st->x - pt->x ) + ( st->y - pt->y ) * ( st->y - pt->y ) ));

		if( fDist > fMaxDist )
		{
			corner[0] = *pt;

			fMaxDist = fDist;
		}
	}

	// 두 번 째 꼭지점 추출(첫 번 째 꼭지점에서 최대 거리를 가지는 점 선택)
	fMaxDist = 0.0;

	for( x = 0; x < contours->total; x++ )
	{
		CvPoint* pt = (CvPoint *)cvGetSeqElem( contours, x );

		double fDist = sqrt( (double)(( corner[0].x - pt->x ) * ( corner[0].x - pt->x ) + ( corner[0].y - pt->y ) * ( corner[0].y - pt->y ) ));

		if( fDist > fMaxDist )
		{
			corner[1] = *pt;

			fMaxDist = fDist;
		}
	}

	// 세 번 째 꼭지점 추출(첫 번 째, 두 번 째 꼭지점에서 최대 거리를 가지는 점 선택)
	fMaxDist = 0.0;

	for( x = 0; x < contours->total; x++ )
	{
		CvPoint* pt = (CvPoint *)cvGetSeqElem( contours, x );

		double fDist =		sqrt( (double)(( corner[0].x - pt->x ) * ( corner[0].x - pt->x ) + ( corner[0].y - pt->y ) * ( corner[0].y - pt->y ) ))
						+	sqrt( (double)(( corner[1].x - pt->x ) * ( corner[1].x - pt->x ) + ( corner[1].y - pt->y ) * ( corner[1].y - pt->y ) ));

		if( fDist > fMaxDist )
		{
			corner[2] = *pt;

			fMaxDist = fDist;
		}
	}

	// 네 번 째 꼭지점 추출
	// (벡터 내적을 이용하여 좌표평면에서 사각형의 너비의 최대 값을 구한다.)
	//														 thanks to 송성원
	int x1 = corner[0].x;	int y1 = corner[0].y;			
	int x2 = corner[1].x;	int y2 = corner[1].y;
	int x3 = corner[2].x;	int y3 = corner[2].y;

	int nMaxDim = 0;

	for( x = 0; x < contours->total; x++ )
	{
		CvPoint* pt = (CvPoint *)cvGetSeqElem( contours, x );

		int x = pt->x;
		int y = pt->y;

		int nDim =		abs( ( x1 * y2 + x2 * y  + x  * y1 ) - ( x2 * y1 + x  * y2 + x1 * y  ) )
					+	abs( ( x1 * y  + x  * y3 + x3 * y1 ) - ( x  * y1 + x3 * y  + x1 * y3 ) )
					+	abs( ( x  * y2 + x2 * y3 + x3 * y  ) - ( x2 * y  + x3 * y2 + x  * y3 ) );

		if( nDim > nMaxDim )
		{
			corner[3] = *pt;

			nMaxDim = nDim;
		}
	}*/

	for(int k = 0; k < 4; k++)
	{
		blob->Mark_corner[k].x = corner[k].x + blob->m_recBlobs[i].x;
		blob->Mark_corner[k].y = corner[k].y + blob->m_recBlobs[i].y;
	}


	//cvReleaseMemStorage( &storage );

	//cvReleaseImage( &marker );
	}

		//cvShow("1234",m_pImage);
}
			
void Callback_ColorDetect(IplImage* image)
{	
		cvCvtColor(image, blob_img, CV_BGR2YCrCb);
		cvCvtPixToPlane(blob_img, blob_RGB, blob_R, blob_B, NULL);
		cvThreshold(blob_R, blob_R, 170, 255, CV_THRESH_BINARY);
		cvThreshold(blob_B, blob_B, 170, 255, CV_THRESH_BINARY);
		//cvShow("1234",blob_B);
		R_blob.SetParam( blob_R, 50 );	// 레이블링 할 이미지와 최소 픽셀수 등을 설정
		R_blob.DoLabeling(); //라벨링
		B_blob.SetParam( blob_B, 50 );	// 레이블링 할 이미지와 최소 픽셀수 등을 설정
		B_blob.DoLabeling(); //라벨링
		//blob.SetParam( blob_B, 100 );	// 레이블링 할 이미지와 최소 픽셀수 등을 설정
		//blob.DoLabeling(); //라벨링
		//Marker_Rect(&B_blob);
		//Marker_Rect(&R_blob);
}
#endif
