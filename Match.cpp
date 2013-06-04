#include "stdafx.h"
#include "Match.h"

CMatch::CMatch(IplImage* src1,IplImage *src2)
{
	srcImage1=cvCloneImage(src1);
	srcImage2=cvCloneImage(src2);
	grayImage1=cvCreateImage(cvGetSize(srcImage1),srcImage1->depth,1);
	grayImage2=cvCreateImage(cvGetSize(srcImage2),srcImage2->depth,1);
	cvCvtColor(srcImage1,grayImage1,CV_RGB2GRAY);
	cvCvtColor(srcImage2,grayImage2,CV_RGB2GRAY);
	lstorage=rstorage=NULL;
	lstorage1=rstorage1=NULL;
	lstorage2=rstorage2=NULL;
	//如果有设置对话框，则取消下面两句
// 	cornerCount1=1000;//define the max corner counts
// 	cornerCount2=1000;
}

CMatch::~CMatch()
{

}
void CMatch::cornerDetect(int maxcornerCount)
{
	//find the corners
	cornerCount1=cornerCount2=maxcornerCount;
	double quality_level=1e-7;
	int min_distance=3;
	IplImage* eigImage1=cvCreateImage(cvGetSize(grayImage1),IPL_DEPTH_32F,1);
	IplImage* tempImage1=cvCreateImage(cvGetSize(grayImage1),IPL_DEPTH_32F,1);
	cvGoodFeaturesToTrack(grayImage1,eigImage1,tempImage1,corner1,&cornerCount1,quality_level,min_distance);
	cvFindCornerSubPix(grayImage1,corner1,cornerCount1,cvSize(3,3),cvSize(-1,-1),
		cvTermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS,10,0.1));
	cvReleaseImage(&eigImage1);
	cvReleaseImage(&tempImage1);

	IplImage* eigImage2=cvCreateImage(cvGetSize(grayImage2),IPL_DEPTH_32F,1);
	IplImage* tempImage2=cvCreateImage(cvGetSize(grayImage2),IPL_DEPTH_32F,1);
	cvGoodFeaturesToTrack(grayImage2,eigImage2,tempImage2,corner2,&cornerCount2,quality_level,min_distance);
	cvFindCornerSubPix(grayImage2,corner2,cornerCount2,cvSize(3,3),cvSize(-1,-1),
		cvTermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS,10,0.1));
	cvReleaseImage(&eigImage2);
	cvReleaseImage(&tempImage2);

	//draw the corners
	for(int i=0;i<cornerCount1;i++)
	{
		int x=cvRound(corner1[i].x);
		int y=cvRound(corner1[i].y);
		cvLine(srcImage1,cvPoint(x-2,y),cvPoint(x+2,y),CV_RGB(255,255,255));
		cvLine(srcImage1,cvPoint(x,y-2),cvPoint(x,y+2),CV_RGB(255,255,255));
	}
	for(int j=0;j<cornerCount2;j++)
	{
		int x=cvRound(corner2[j].x);
		int y=cvRound(corner2[j].y);
		cvLine(srcImage2,cvPoint(x-2,y),cvPoint(x+2,y),CV_RGB(255,255,255));
		cvLine(srcImage2,cvPoint(x,y-2),cvPoint(x,y+2),CV_RGB(255,255,255));
	}
}

void CMatch::initMatch(int patch_radius,int max_disparity)
{
	int x1,y1,x2,y2;
	int i,j;
// 	int patch_radius=5;
// 	int max_disparity=100;
	double min_norm;
	double norm;
	int mat12[MAXCORNERS];
	int mat21[MAXCORNERS];
	IplImage *patchimg1=cvCreateImage(cvSize(patch_radius*2+1,patch_radius*2+1),IPL_DEPTH_8U,1);
	IplImage *patchimg2=cvCreateImage(cvSize(patch_radius*2+1,patch_radius*2+1),IPL_DEPTH_8U,1);
	//1->2
	for(i=0;i<cornerCount1;i++)
	{
		min_norm=1e8;
		mat12[i]=-1;
		x1=cvRound(corner1[i].x);
		y1=cvRound(corner1[i].y);
		//忽略边缘patch_radius个像素
		if(x1>patch_radius&&x1<grayImage1->width-patch_radius&&y1>patch_radius&&y1<grayImage1->height-patch_radius)
		{
			cvSetImageROI(grayImage1,cvRect(x1-patch_radius,y1-patch_radius,patch_radius*2+1,patch_radius*2+1));
			cvCopy(grayImage1,patchimg1);
			cvResetImageROI(grayImage1);
			for(j=0;j<cornerCount2;j++)
			{
				x2=cvRound(corner2[j].x);
				y2=cvRound(corner2[j].y);
				if(x2>patch_radius&&x2<grayImage2->width-patch_radius&&y2>patch_radius&&y2<grayImage2->height-patch_radius)
				{
					cvSetImageROI(grayImage2,cvRect(x2-patch_radius,y2-patch_radius,patch_radius*2+1,patch_radius*2+1));
					cvCopy(grayImage2,patchimg2);
					cvResetImageROI(grayImage2);
					if((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)<max_disparity*max_disparity)
					{
						norm=cvNorm(patchimg1,patchimg2,CV_L2);
						if(norm<min_norm)
						{
							min_norm=norm;
							mat12[i]=j;
						}
					}
				}
			}
		}
	}
	//2->1
	for(i=0;i<cornerCount2;i++)
	{
		mat21[i]=-1;
		min_norm=1e8;
		x2=cvRound(corner2[i].x);
		y2=cvRound(corner2[i].y);
		//忽略边缘patch_radius个像素
		if(x2>patch_radius&&x2<grayImage2->width-patch_radius&&y2>patch_radius&&y2<grayImage2->height-patch_radius)
		{
			cvSetImageROI(grayImage2,cvRect(x2-patch_radius,y2-patch_radius,patch_radius*2+1,patch_radius*2+1));
			cvCopy(grayImage2,patchimg2);
			cvResetImageROI(grayImage2);
			for(j=0;j<cornerCount1;j++)
			{
				x1=cvRound(corner1[j].x);
				y1=cvRound(corner1[j].y);
				if(x1>patch_radius&&x1<grayImage1->width-patch_radius&&y1>patch_radius&&y1<grayImage1->height-patch_radius)
				{
					cvSetImageROI(grayImage1,cvRect(x1-patch_radius,y1-patch_radius,patch_radius*2+1,patch_radius*2+1));
					cvCopy(grayImage1,patchimg1);
					cvResetImageROI(grayImage1);
					if((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)<max_disparity*max_disparity)
					{
						norm=cvNorm(patchimg2,patchimg1,CV_L2);
						if(norm<min_norm)
						{
							min_norm=norm;
							mat21[i]=j;
						}
					}
				}
			}
		}
	}
	//if(1->2&&2->1)
	
	if(lstorage!=NULL)
		cvClearMemStorage(lstorage);
	if(rstorage!=NULL)
		cvClearMemStorage(rstorage);
	lstorage=cvCreateMemStorage(0);
	rstorage=cvCreateMemStorage(0);
	leftSeq=cvCreateSeq(CV_SEQ_ELTYPE_POINT,sizeof(CvSeq),sizeof(CvPoint),lstorage);
	rightSeq=cvCreateSeq(CV_SEQ_ELTYPE_POINT,sizeof(CvSeq),sizeof(CvPoint),rstorage);

	
	if(lstorage1!=NULL)
		cvClearMemStorage(lstorage1);
	if(rstorage1!=NULL)
		cvClearMemStorage(rstorage1);
	lstorage1=cvCreateMemStorage(0);
	rstorage1=cvCreateMemStorage(0);
	chooseSeq1=cvCreateSeq(CV_SEQ_ELTYPE_POINT,sizeof(CvSeq),sizeof(CvPoint),lstorage1);
	chooseSeq2=cvCreateSeq(CV_SEQ_ELTYPE_POINT,sizeof(CvSeq),sizeof(CvPoint),rstorage1);

	
	if(lstorage2!=NULL)
		cvClearMemStorage(lstorage2);
	if(rstorage2!=NULL)
		cvClearMemStorage(rstorage2);
 	lstorage2=cvCreateMemStorage(0);
 	rstorage2=cvCreateMemStorage(0);
 	initSeq1=cvCreateSeq(CV_SEQ_ELTYPE_POINT,sizeof(CvSeq),sizeof(CvPoint),lstorage2);
 	initSeq2=cvCreateSeq(CV_SEQ_ELTYPE_POINT,sizeof(CvSeq),sizeof(CvPoint),rstorage2);
	for(i=0;i<cornerCount1;i++)
	{
		if(mat12[i]>=0&&mat21[mat12[i]]==i)
		{
			j=mat12[i];
			CvPoint leftpt=cvPoint(corner1[i].x,corner1[i].y);
			CvPoint rightpt=cvPoint(corner2[j].x,corner2[j].y);
			cvSeqPush(leftSeq,&leftpt);
			cvSeqPush(rightSeq,&rightpt);
//  		cvLine(srcImage1,leftpt,rightpt,CV_RGB(0,255,0));
//  		cvLine(srcImage2,leftpt,rightpt,CV_RGB(0,255,0));
		}
	}
 	initSeq1=cvCloneSeq(leftSeq);
 	initSeq2=cvCloneSeq(rightSeq);
}

void CMatch::guideMatch(double epidis)
{
/*	double epidis=20.0;*/
	CvMat *fundmental=cvCreateMat(3,3,CV_32FC1);
	CvMat *hleftmat=cvCreateMat(3,leftSeq->total,CV_32FC1);
	CvMat *hrightmat=cvCreateMat(3,leftSeq->total,CV_32FC1);
	CvMat *corrLine1=cvCreateMat(3,leftSeq->total,CV_32FC1);
	CvMat *corrLine2=cvCreateMat(3,leftSeq->total,CV_32FC1);
	for(int i=0;i<leftSeq->total;i++)
	{
		CvPoint *p=(CvPoint*)cvGetSeqElem(leftSeq,i);
		CvPoint *q=(CvPoint*)cvGetSeqElem(rightSeq,i);
		cvmSet(hleftmat,0,i,p->x);
		cvmSet(hleftmat,1,i,p->y);
		cvmSet(hleftmat,2,i,1.0);
		cvmSet(hrightmat,0,i,q->x);
		cvmSet(hrightmat,1,i,q->y);
		cvmSet(hrightmat,2,i,1.0);
	}
	cvFindFundamentalMat(hleftmat,hrightmat,fundmental,CV_FM_RANSAC,1.0,0.99,NULL);
	cvComputeCorrespondEpilines(hleftmat,1,fundmental,corrLine2);
	cvComputeCorrespondEpilines(hrightmat,2,fundmental,corrLine1);
	int j=0;
	while(j<leftSeq->total)
	{
		CvMat leftpt1,rightpt1;
		CvMat leftline1,rightline1;
		cvGetCol(hleftmat,&leftpt1,j);
		cvGetCol(corrLine1,&leftline1,j);
		double dis1=fabs(cvDotProduct(&leftpt1,&leftline1));
		cvGetCol(hrightmat,&rightpt1,j);
		cvGetCol(corrLine2,&rightline1,j);
		double dis2=fabs(cvDotProduct(&rightpt1,&rightline1));
		if(dis1>epidis||dis2>epidis)
		{
			CvPoint *p=(CvPoint*)cvGetSeqElem(leftSeq,j);
			CvPoint *q=(CvPoint*)cvGetSeqElem(rightSeq,j);
// 			cvCircle(srcImage1,cvPoint(p->x,p->y),4,CV_RGB(255,0,0));
// 			cvCircle(srcImage2,cvPoint(q->x,q->y),4,CV_RGB(255,0,0));
			cvSeqRemove(leftSeq,j);
			cvSeqRemove(rightSeq,j);
		}
		else
			j++;
	}
	cvReleaseMat(&fundmental);
	cvReleaseMat(&hleftmat);
	cvReleaseMat(&hrightmat);
	cvReleaseMat(&corrLine1);
	cvReleaseMat(&corrLine2);
}

void CMatch::histMatch(double threshold)
{
	int i,maxhist=0;
	double angle;
	int hist[36]={0};
	for(i=0;i<leftSeq->total;i++)
	{
		CvPoint *p=(CvPoint*)cvGetSeqElem(leftSeq,i);
		CvPoint *q=(CvPoint*)cvGetSeqElem(rightSeq,i);
		if(q->x==p->x)
		{
			hist[35]++;
		}
		else
		{
			double theta=atan((q->y-p->y)*1.0/(q->x-p->x))*180/CV_PI;
			int tempang=cvCeil((theta+90)/5);
			if(tempang<=0)
				tempang=0;
			else if(tempang>=35)
				tempang=35;
			hist[tempang]++;
		}
	}
	for(i=0;i<36;i++)
	{
		if(hist[i]>maxhist)
		{
			maxhist=hist[i];
			angle=-90+i*5+2.5;   //perfect angle
		}
	}	
	i=0;
	while(i<leftSeq->total)
	{
		CvPoint *p=(CvPoint*)cvGetSeqElem(leftSeq,i);
		CvPoint *q=(CvPoint*)cvGetSeqElem(rightSeq,i);
		double theta=atan((q->y-p->y)*1.0/(q->x-p->x))*180/CV_PI;
		if(fabs(theta-angle)>threshold)
		{
			cvSeqRemove(leftSeq,i);
			cvSeqRemove(rightSeq,i);
		}
		else
			i++;
	}
// 	for(int m=0;m<leftSeq->total;m++)
// 	{
// 		CvPoint *p=(CvPoint*)cvGetSeqElem(leftSeq,m);
// 		CvPoint *q=(CvPoint*)cvGetSeqElem(rightSeq,m);
// 		cvLine(srcImage1,*p,*q,CV_RGB(0,255,0));
// 		cvLine(srcImage2,*p,*q,CV_RGB(0,255,0));
// 	}
}

void CMatch::showCorre()
{
	for(int m=0;m<leftSeq->total;m++)
	{
		CvPoint *p=(CvPoint*)cvGetSeqElem(leftSeq,m);
		CvPoint *q=(CvPoint*)cvGetSeqElem(rightSeq,m);
		cvLine(srcImage1,*p,*q,CV_RGB(0,255,0));
		cvLine(srcImage2,*p,*q,CV_RGB(0,255,0));
	}
}
