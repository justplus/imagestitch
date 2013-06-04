#ifndef MATCH_H
#define MATCH_H

#define MAXCORNERS 2000
#include "cv.h"
#include "highgui.h"

class CMatch
{
public:
	IplImage *srcImage1;
	IplImage *srcImage2;
	IplImage *grayImage1;
	IplImage *grayImage2;
	CvSeq *leftSeq;
	CvSeq *rightSeq;
	CvSeq *chooseSeq1;
	CvSeq *chooseSeq2;
 	CvSeq *initSeq1;
 	CvSeq *initSeq2;
	CvPoint2D32f corner1[MAXCORNERS];
	CvPoint2D32f corner2[MAXCORNERS];
	int cornerCount1;//define the max corner counts
	int cornerCount2;

	CvMemStorage* lstorage,*rstorage;
	CvMemStorage* lstorage1,*rstorage1;
	CvMemStorage* lstorage2,*rstorage2;

public:
	CMatch(IplImage* src1,IplImage *src2);
	virtual ~CMatch();
	void cornerDetect(int maxcornerCount);
	void initMatch(int patch_radius,int max_disparity);          //initial match
	void guideMatch(double epidis);		   //guide match
	void histMatch(double threshold);		   //histogram match
	void showCorre();
};
#endif