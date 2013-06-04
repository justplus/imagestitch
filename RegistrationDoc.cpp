// RegistrationDoc.cpp : CRegistrationDoc 类的实现
//

#include "stdafx.h"
#include "Registration.h"
#include "RegistrationDoc.h"
#include "MainFrm.h"
#include "Seetingdescription.h"
#include <fstream>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRegistrationDoc

IMPLEMENT_DYNCREATE(CRegistrationDoc, CDocument)

BEGIN_MESSAGE_MAP(CRegistrationDoc, CDocument)
	ON_COMMAND(ID_RESIZEIMAGE, &CRegistrationDoc::OnResizeimage)
	ON_COMMAND(ID_ROTATEIMAGE, &CRegistrationDoc::OnRotateimage)
	ON_COMMAND(ID_FILTERIMAGE, &CRegistrationDoc::OnFilterimage)
	ON_COMMAND(ID_FILE_OPEN, &CRegistrationDoc::OnFileOpen)
	ON_COMMAND(ID_OPERATE_RESET, &CRegistrationDoc::OnOperateReset)
	ON_COMMAND(ID_COLOR_GRAYSCAL, &CRegistrationDoc::OnColorGrayscal)
	ON_COMMAND(ID_COLOR_24, &CRegistrationDoc::OnColor24)
	ON_COMMAND(ID_FILE_SAVE, &CRegistrationDoc::OnFileSave)
	ON_COMMAND(ID_FILE_SAVE_AS, &CRegistrationDoc::OnFileSaveAs)
	ON_COMMAND(ID_CORNERS, &CRegistrationDoc::OnCorners)	ON_COMMAND(ID_MATCH, &CRegistrationDoc::OnMatch)
	ON_COMMAND(ID_DELMATCHED, &CRegistrationDoc::OnDelmatched)
	ON_UPDATE_COMMAND_UI(ID_DELMATCHED, &CRegistrationDoc::OnUpdateDelmatched)
	ON_COMMAND(ID_ADDMATCHED, &CRegistrationDoc::OnAddmatched)
	ON_UPDATE_COMMAND_UI(ID_ADDMATCHED, &CRegistrationDoc::OnUpdateAddmatched)
	ON_COMMAND(ID_REGISTRATION, &CRegistrationDoc::OnRegistration)
	ON_COMMAND(ID_SETTING_SETTING, &CRegistrationDoc::OnSettingSetting)
	ON_COMMAND(ID_HELP_DESCRIPTION, &CRegistrationDoc::OnHelpDescription)
	ON_COMMAND(ID_REMATCH, &CRegistrationDoc::OnRematch)
	ON_COMMAND(ID_EXPORT2DPOINTS, &CRegistrationDoc::OnExport2dpoints)
	ON_COMMAND(ID_HELPDOCUMENT, &CRegistrationDoc::OnHelpdocument)
	ON_COMMAND(ID_EXPORT3DPOINTS, &CRegistrationDoc::OnExport3dpoints)
	ON_COMMAND(ID_REMATCH_ACCURATEPOINTS, &CRegistrationDoc::OnRematchAccuratepoints)
	ON_COMMAND(ID_REMATCH_DENSEPOINTS, &CRegistrationDoc::OnRematchDensepoints)
END_MESSAGE_MAP()


// CRegistrationDoc 构造/析构

CRegistrationDoc::CRegistrationDoc()
{
	srcImage1=NULL;
	srcImage2=NULL;
	showImage1=NULL;
	showImage2=NULL;
	image1Opened=false;
	image2Opened=false;
	deleteMatched=false;
	addMatched=false;
	freematch=false;
	rematched=false;

	cornerdetected=false;
	matched=false;
	fused=false;
	H=NULL;
	F=NULL;
	//matchType=1;//透视模式
}

CRegistrationDoc::~CRegistrationDoc()
{
	if(freematch)
		delete m_match;
	cvReleaseImage(&srcImage1);
	cvReleaseImage(&srcImage2);
	cvReleaseImage(&showImage1);
	cvReleaseImage(&showImage2);
}

BOOL CRegistrationDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)
	SetTitle(_T("Image Registrtion"));
	return TRUE;
}




// CRegistrationDoc 序列化

void CRegistrationDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}


// CRegistrationDoc 诊断

#ifdef _DEBUG
void CRegistrationDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CRegistrationDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CRegistrationDoc 命令

void CRegistrationDoc::OnResizeimage()
{
	if(m_resizeImage.DoModal()==IDOK)
	{
		if(m_resizeImage.m_imageNo==0)
		{
			if(!image1Opened)
				ShowState("请先打开图像!!");
			else
			{
				IplImage* tempImage;
				tempImage=cvCreateImage(cvSize(m_resizeImage.m_width,m_resizeImage.m_height),srcImage1->depth,srcImage1->nChannels);
				if(m_resizeImage.m_interMethod.Compare("the nearest neighbor"))
				{
					cvResize(srcImage1,tempImage,CV_INTER_NN);
				}
				else if(m_resizeImage.m_interMethod.Compare("linear"))
				{
					cvResize(srcImage1,tempImage,CV_INTER_LINEAR);
				}
				else if(m_resizeImage.m_interMethod.Compare("area"))
				{
					cvResize(srcImage1,tempImage,CV_INTER_AREA);
				}
				else if(m_resizeImage.m_interMethod.Compare("cubic"))
				{
					cvResize(srcImage1,tempImage,CV_INTER_CUBIC);
				}
				showImage1=NULL;
				showImage1=cvCloneImage(tempImage);
				UpdateAllViews(NULL);
				cvReleaseImage(&tempImage);
			}
		}
		else if(m_resizeImage.m_imageNo==1)
		{
			if(!image2Opened)
				ShowState("请先打开图像!!");
			else
			{
				IplImage* tempImage;
				tempImage=cvCreateImage(cvSize(m_resizeImage.m_width,m_resizeImage.m_height),srcImage2->depth,srcImage2->nChannels);
				if(m_resizeImage.m_interMethod.Compare("the nearest neighbor"))
				{
					cvResize(srcImage2,tempImage,CV_INTER_NN);
				}
				else if(m_resizeImage.m_interMethod.Compare("linear"))
				{
					cvResize(srcImage2,tempImage,CV_INTER_LINEAR);
				}
				else if(m_resizeImage.m_interMethod.Compare("area"))
				{
					cvResize(srcImage2,tempImage,CV_INTER_AREA);
				}
				else if(m_resizeImage.m_interMethod.Compare("cubic"))
				{
					cvResize(srcImage2,tempImage,CV_INTER_CUBIC);
				}
				showImage2=NULL;
				showImage2=cvCloneImage(tempImage);
				UpdateAllViews(NULL);
				cvReleaseImage(&tempImage);
			}
		}
	}
}

void CRegistrationDoc::OnRotateimage()
{
	if(m_rotateImage.DoModal()==IDOK)
	{
		float m_degree=0;
		if(m_rotateImage.m_specifyangle==0)
			m_degree=90;
		else if(m_rotateImage.m_specifyangle==1)
			m_degree=180;
		else if(m_rotateImage.m_specifyangle==2)
			m_degree=270;
		else if(m_rotateImage.m_specifyangle==3)
			m_degree=m_rotateImage.m_angle;
		if(m_rotateImage.m_direction==0)
			m_degree=(-1)*m_degree;
		double m_angle=m_degree*CV_PI/180;
		double a=sin(m_angle);
		double b=cos(m_angle);
		int srcwidth,srcheight,dstwidth,dstheight;
		double map[6];
		
		if(m_rotateImage.m_imageNo==0)
		{
			if(!image1Opened)
				ShowState("请先打开图像!!");
			else
			{
				srcwidth=showImage1->width;
				srcheight=showImage1->height;
				dstwidth=int(srcheight*fabs(a)+srcwidth*fabs(b));
				dstheight=int(srcwidth*fabs(a)+srcheight*fabs(b));
				CvMat map_matrix=cvMat(2,3,CV_64FC1,map);
				CvPoint2D32f pt = cvPoint2D32f(srcwidth/2,srcheight/2);
				cv2DRotationMatrix(pt, m_degree, 1.0, &map_matrix);
				map[2] += (dstwidth - srcwidth) / 2;
				map[5] += (dstheight - srcheight) / 2;
				IplImage *tempImage;
				tempImage=cvCreateImage(cvSize(dstwidth,dstheight),8,srcImage1->nChannels);
				//showImage1=NULL;
				cvWarpAffine(showImage1,tempImage,&map_matrix);
				showImage1=NULL;
				showImage1=cvCloneImage(tempImage);
				cvReleaseImage(&tempImage);
				UpdateAllViews(NULL);
			}
		}
		else if(m_rotateImage.m_imageNo==1)
		{
			if(!image2Opened)
				ShowState("请先打开图像!!");
			else
			{
				srcwidth=showImage2->width;
				srcheight=showImage2->height;
				dstwidth=int(srcheight*fabs(a)+srcwidth*fabs(b));
				dstheight=int(srcwidth*fabs(a)+srcheight*fabs(b));
				CvMat map_matrix=cvMat(2,3,CV_64FC1,map);
				CvPoint2D32f pt = cvPoint2D32f(srcwidth/2,srcheight/2);
				cv2DRotationMatrix(pt, m_degree, 1.0, &map_matrix);
				map[2] += (dstwidth - srcwidth) / 2;
				map[5] += (dstheight - srcheight) / 2;
				IplImage *tempImage;
				tempImage=cvCreateImage(cvSize(dstwidth,dstheight),8,srcImage1->nChannels);
				//showImage1=NULL;
				cvWarpAffine(showImage2,tempImage,&map_matrix);
				showImage2=NULL;
				showImage2=cvCloneImage(tempImage);
				cvReleaseImage(&tempImage);
				UpdateAllViews(NULL);
			}
		}
	}
}

void CRegistrationDoc::OnFilterimage()
{
	if(m_filterImage.DoModal()==IDOK)
	{
		int para=m_filterImage.m_filterSize*2+3;
		if(m_filterImage.m_imageNo==0)
		{
			if(!image1Opened)
				ShowState("请先打开图像!!");
			else 
			{
				IplImage* tempImage=cvCreateImage(cvGetSize(srcImage1),srcImage1->depth,srcImage1->nChannels);
				if(m_filterImage.m_smoothMethod.Compare("simple blur"))
					cvSmooth(showImage1,tempImage,CV_BLUR,para,para);
				else if(m_filterImage.m_smoothMethod.Compare("median blur"))
					cvSmooth(showImage1,tempImage,CV_MEDIAN,para,para);
				else if(m_filterImage.m_smoothMethod.Compare("gaussian blur"))
					cvSmooth(showImage1,tempImage,CV_GAUSSIAN,para,para,m_filterImage.m_sigma);
				showImage1=NULL;
				showImage1=cvCloneImage(tempImage);
				UpdateAllViews(NULL);
			}	
		}
		else if(m_filterImage.m_imageNo==1)
		{
			if(!image2Opened)
				ShowState("请先打开图像!!");
			else 
			{
				IplImage* tempImage=cvCreateImage(cvGetSize(srcImage2),srcImage2->depth,srcImage2->nChannels);
				if(m_filterImage.m_smoothMethod.Compare("simple blur"))
					cvSmooth(showImage2,tempImage,CV_BLUR,para,para);
				else if(m_filterImage.m_smoothMethod.Compare("median blur"))
					cvSmooth(showImage2,tempImage,CV_MEDIAN,para,para);
				else if(m_filterImage.m_smoothMethod.Compare("gaussian blur"))
					cvSmooth(showImage2,tempImage,CV_GAUSSIAN,para,para,m_filterImage.m_sigma);
				showImage2=NULL;
				showImage2=cvCloneImage(tempImage);
				UpdateAllViews(NULL);
			}	
		}
	}
}

void CRegistrationDoc::OnFileOpen()
{
	if(m_openImage.DoModal()==IDOK)
	{ 
		CMainFrame *pFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;
		pFrame->needSplite=true;
		pFrame->setView(true);
		srcImage1=cvLoadImage(m_openImage.imagePath1);
		srcImage2=cvLoadImage(m_openImage.imagePath2);
		showImage1=cvCloneImage(srcImage1);
		showImage2=cvCloneImage(srcImage2);
		image1Opened=true;
		image2Opened=true;
		CRegistrationApp* app=(CRegistrationApp*)AfxGetApp();
		app->image1Width=srcImage1->width;
		app->image1Height=srcImage1->height;
		app->image2Width=srcImage2->width;
		app->image2Height=srcImage2->height;
		UpdateAllViews(NULL);
		cornerdetected=false;
		matched=false;
		fused=false;
		//free(pFrame);
	}
}

//在状态栏显示信息
void CRegistrationDoc::ShowState(CString stateinfo)
{
	CStatusBar *pFrame=(CStatusBar*)AfxGetMainWnd();   
	CStatusBar *pStatusBar=(CStatusBar*)pFrame->GetDescendantWindow(AFX_IDW_STATUS_BAR);       
	pStatusBar->SetPaneText(1,stateinfo,true);
}

void CRegistrationDoc::OnOperateReset()
{
	showImage1=NULL;
	showImage1=cvCloneImage(srcImage1);
	showImage2=NULL;
	showImage2=cvCloneImage(srcImage2);
	UpdateAllViews(NULL);
}

void CRegistrationDoc::OnColorGrayscal()
{
	if(image1Opened&&showImage1->nChannels==3)
	{
		IplImage *tempImage=cvCreateImage(cvSize(srcImage1->width,srcImage1->height),8,1);
		cvCvtColor(showImage1,tempImage,CV_RGB2GRAY);
		showImage1=NULL;
		showImage1=cvCloneImage(tempImage);
		cvReleaseImage(&tempImage);
	}
	if(image2Opened&&showImage2->nChannels==3)
	{
		IplImage *tempImage=cvCreateImage(cvSize(srcImage2->width,srcImage2->height),8,1);
		cvCvtColor(showImage2,tempImage,CV_RGB2GRAY);
		showImage2=NULL;
		showImage2=cvCloneImage(tempImage);
		cvReleaseImage(&tempImage);
	}
	UpdateAllViews(NULL);
}

void CRegistrationDoc::OnColor24()
{
	if(image1Opened&&showImage1->nChannels==1)
	{
		IplImage *tempImage=cvCreateImage(cvSize(srcImage1->width,srcImage1->height),8,3);
		cvCvtColor(showImage1,tempImage,CV_GRAY2RGB);
		showImage1=NULL;
		showImage1=cvCloneImage(tempImage);
		cvReleaseImage(&tempImage);
	}
	if(image2Opened&&showImage2->nChannels==1)
	{
		IplImage *tempImage=cvCreateImage(cvSize(srcImage2->width,srcImage2->height),8,3);
		cvCvtColor(showImage2,tempImage,CV_GRAY2RGB);
		showImage2=NULL;
		showImage2=cvCloneImage(tempImage);
		cvReleaseImage(&tempImage);
	}
	UpdateAllViews(NULL);
}

void CRegistrationDoc::OnFileSave()
{
	if(image1Opened&&image2Opened)
	{
		CString debugPath=AfxGetApp()->m_pszHelpFilePath;
		debugPath=debugPath.Left(debugPath.ReverseFind('\\')); 
		debugPath+= _T("\\");

		SYSTEMTIME st;//系统时间
		GetLocalTime(&st);
		CString Filelast1,Filelast2;
		Filelast1.Format("%2d-%2d-img1.bmp",st.wMinute,st.wSecond);
		Filelast2.Format("%2d-%2d-img2.bmp",st.wMinute,st.wSecond);

		cvSaveImage(debugPath+Filelast1,showImage1);
		cvSaveImage(debugPath+Filelast2,showImage2);
		CString tempstring;
		tempstring.Format("图像已经保存在目录%s下了",debugPath);
		ShowState(tempstring);
	}
	else
		ShowState("请检查是否打开两幅图像！！");
}

void CRegistrationDoc::OnFileSaveAs()
{
	if(image1Opened&&image2Opened)
	{
		CString filter="Bitmap Files(*.bmp)|*.bmp|JPEG Files(*.jpg)|*.jpg|PNG Files(*.png)|*.png|All Files(*.*)|*.*||";
		CFileDialog SaveImageDlg(false,"*.bmp","img1",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,filter,NULL);
		CString FilePath1,FilePath2;
		if(SaveImageDlg.DoModal()==IDOK)
		{
			FilePath1.Format("1-%s",SaveImageDlg.GetPathName());
			FilePath1.Format("2-%s",SaveImageDlg.GetPathName());
			cvSaveImage(FilePath1,showImage1);
			cvSaveImage(FilePath2,showImage2);
		}
	}
	else
		ShowState("请检查是否打开两幅图像！！");
}

void CRegistrationDoc::OnCorners()
{
	if(image1Opened&&image2Opened)
	{
		if(freematch)
			delete m_match;
		m_match=new CMatch(srcImage1,srcImage2);
		freematch=true;
		//freematch=((m_match==NULL)?false:true);
		m_match->cornerDetect(setDlg.cornerCount);
		showImage1=NULL;
		showImage1=m_match->srcImage1;
		showImage2=NULL;
		showImage2=m_match->srcImage2;
		CString temp;
		temp.Format("图像1的角点数量:%d;图像2的角点数量:%d",m_match->cornerCount1,m_match->cornerCount2);
		ShowState(temp);
		cornerdetected=true;
		matched=false;
		fused=false;
		UpdateAllViews(NULL);
	}
	else
		ShowState("请检查是否已经打开两幅图像");
}

void CRegistrationDoc::OnMatch()
{
	if(!cornerdetected)
	{
		ShowState("请先完成特征点检测....");
		return;
	}
	m_match->initMatch(setDlg.patch_radius,setDlg.max_disparity);
	if(setDlg.histmatch)
		m_match->histMatch(setDlg.threshold);
	if(setDlg.guidematch)
		m_match->guideMatch(setDlg.epidis);
	m_match->showCorre();
	showImage1=NULL;
	showImage1=m_match->srcImage1;
	showImage2=NULL;
	showImage2=m_match->srcImage2;
	CString temp;
	temp.Format("匹配点对:%d",m_match->leftSeq->total);
	ShowState(temp);
	matched=true;
	fused=false;
	UpdateAllViews(NULL);
}

void CRegistrationDoc::OnDelmatched()
{
	if(deleteMatched)
		deleteMatched=false;
	else
	{
		deleteMatched=true;
		addMatched=false;
	}
}

void CRegistrationDoc::OnUpdateDelmatched(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(deleteMatched);
}

void CRegistrationDoc::OnAddmatched()
{
	
	if(addMatched)
		addMatched=false;
	else
	{
		addMatched=true;
		deleteMatched=false;
	}
}

void CRegistrationDoc::OnUpdateAddmatched(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(addMatched);
}

void CRegistrationDoc::OnRegistration()
{
	if(!matched)
	{
		ShowState("请先完成特征点匹配....");
		return;
	}

	if(m_match->chooseSeq1->total==0)
	{
		int retResult;
		if(setDlg.m_matchType==0)
		{
			retResult=AfxMessageBox("是否在不选定至少3对引导点的情况下进行配准？",MB_YESNO);
		}
		else if(setDlg.m_matchType==1)
		{
			retResult=AfxMessageBox("是否在不选定至少4对引导点的情况下进行配准？",MB_YESNO);
		}
		if(retResult==IDNO)
		{
			return;
		}
	}
	//if(k<3)
	else if(setDlg.m_matchType==0)
	{
		if(m_match->chooseSeq1->total<3)
		{
			ShowState("请先手动选取不少余3对的特征点...");
			return;
		}
		int i=0;
		CvMat *H0=cvCreateMat(2,3,CV_32FC1);
		//cvGetAffineTransform(leftpoint,rightpoint,H0);
		H0=findHMatrix(m_match->chooseSeq1,m_match->chooseSeq2);
		double a1=cvmGet(H0,0,0);
		double a2=cvmGet(H0,0,1);
		double a3=cvmGet(H0,1,0);
		double a4=cvmGet(H0,1,1);
		double tx=cvmGet(H0,0,2);
		double ty=cvmGet(H0,1,2);
		//for(int i=0;i<leftSeq->total;i++)
		while(i<m_match->leftSeq->total)
		{
			CvPoint *p=(CvPoint *)cvGetSeqElem(m_match->leftSeq,i);
			CvPoint *q=(CvPoint *)cvGetSeqElem(m_match->rightSeq,i);
			double disx=a1*p->x+a2*p->y+tx;
			double disy=a3*p->x+a4*p->y+ty;
			if((disx-q->x)*(disx-q->x)+(disy-q->y)*(disy-q->y)>2*2)
			{
				cvSeqRemove(m_match->leftSeq,i);
				cvSeqRemove(m_match->rightSeq,i);
			}
			else
				i++;
		}
		cvReleaseMat(&H0);
	}
	else if(setDlg.m_matchType==1)
	{
		if(m_match->chooseSeq1->total<4)
		{
			ShowState("请先手动选取不少余4对的特征点...");
			return;
		}
		int i=0;
		CvMat *H0=cvCreateMat(3,3,CV_32FC1);
		H0=findHMatrix(m_match->chooseSeq1,m_match->chooseSeq2);
		double a1=cvmGet(H0,0,0);
		double a2=cvmGet(H0,0,1);
		double a3=cvmGet(H0,1,0);
		double a4=cvmGet(H0,1,1);
		double tx=cvmGet(H0,0,2);
		double ty=cvmGet(H0,1,2);
		double u1=cvmGet(H0,2,0);
		double u2=cvmGet(H0,2,1);
		//for(int i=0;i<leftSeq->total;i++)
		while(i<m_match->leftSeq->total)
		{
			CvPoint *p=(CvPoint *)cvGetSeqElem(m_match->leftSeq,i);
			CvPoint *q=(CvPoint *)cvGetSeqElem(m_match->rightSeq,i);
			double disx=(a1*p->x+a2*p->y+tx)/(u1*p->x+u2*p->y+1);
			double disy=(a3*p->x+a4*p->y+ty)/(u1*p->x+u2*p->y+1);
			if((disx-q->x)*(disx-q->x)+(disy-q->y)*(disy-q->y)>0.25*1)
			{
				cvSeqRemove(m_match->leftSeq,i);
				cvSeqRemove(m_match->rightSeq,i);
			}
			else
				i++;
		}
		cvReleaseMat(&H0);
	}

	
	CMainFrame *pFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;
	pFrame->needSplite=false;
	pFrame->setView(false);
	if(H!=NULL)
		cvReleaseMat(&H);
	if(setDlg.m_matchType==0)
	{
		H=cvCreateMat(2,3,CV_32FC1);
		H=findHMatrix(m_match->leftSeq,m_match->rightSeq);
		//对图像的四个顶点进行映射，以自适应的确定边界
		int wi=srcImage1->width;
		int he=srcImage1->height;
		// 	float quard[]={0,wi,0,wi,0,0,he,he,1,1,1,1};
		// 	CvMat src;
		// 	cvInitMatHeader(&src,3,4,CV_32FC1,quard);
		//	double tem=cvmGet(&src,0,1);
		CvMat *src=cvCreateMat(3,4,CV_32FC1);
		cvZero(src);
		cvmSet(src,0,1,wi);
		cvmSet(src,0,3,wi);
		cvmSet(src,1,2,he);
		cvmSet(src,1,3,he);
		cvmSet(src,2,0,1.0);
		cvmSet(src,2,1,1.0);
		cvmSet(src,2,2,1.0);
		cvmSet(src,2,3,1.0);
		CvMat *dst=cvCreateMat(2,4,CV_32FC1);
		cvmMul(H,src,dst);

		double leftv,rightv,topv,bottomv;
		CvMat *row=cvCreateMat(1,4,CV_32FC1);
		cvGetRow(dst,row,0);
		cvMinMaxLoc(row,&leftv,&rightv);
		cvGetRow(dst,row,1);
		cvMinMaxLoc(row,&topv,&bottomv);
		int fl,fr,ft,fb;
		// 	fl=min(leftv,0);
		// 	fr=max(rightv,srcImage2->width);
		// 	ft=min(topv,0);
		// 	fb=max(bottomv,srcImage2->height);
		fl=((leftv>0)?0:leftv);
		fr=((rightv>srcImage2->width)?rightv:srcImage2->width);
		ft=((topv>0)?0:topv);
		fb=((bottomv>srcImage2->height)?bottomv:srcImage2->height);

		CvMat *tempAdd=cvCreateMat(2,3,CV_32FC1);
		cvZero(tempAdd);
		cvmSet(tempAdd,0,2,fl);
		cvmSet(tempAdd,1,2,ft);
		CvMat *HF=cvCreateMat(2,3,CV_32FC1);
		cvSub(H,tempAdd,HF);
		showImage1=NULL;
		showImage1=cvCreateImage(cvSize(fr-fl,fb-ft),8,3);
		cvWarpAffine(srcImage1,showImage1,HF,CV_INTER_LINEAR|CV_WARP_FILL_OUTLIERS,cvScalar(0));
		IplImage *fushion=cvCreateImage(cvSize(fr-fl,fb-ft),8,3);
		cvSetImageROI(fushion,cvRect(-fl,-ft,srcImage2->width,srcImage2->height));
		cvCopy(srcImage2,fushion);
		cvResetImageROI(fushion);

		double alpha,beta;
		CvScalar scalar1,scalar2;
		for(int i=0;i<fb-ft;i++)
			for(int j=0;j<fr-fl;j++)
			{
				alpha=beta=0.5;
				scalar1=cvGet2D(showImage1,i,j);
				scalar2=cvGet2D(fushion,i,j);
				if(scalar1.val[0]+scalar1.val[1]+scalar1.val[2]<1)
				{
					alpha=0;
					beta=1.0;
				}
				else if(scalar2.val[0]+scalar2.val[1]+scalar2.val[2]<1)
				{
					alpha=1.0;
					beta=0;
				}
				cvSetImageROI(showImage1,cvRect(j,i,1,1));
				cvSetImageROI(fushion,cvRect(j,i,1,1));
				cvAddWeighted(showImage1,alpha,fushion,beta,0,showImage1);
				cvResetImageROI(showImage1);
				cvResetImageROI(fushion);
			}
			UpdateAllViews(NULL);
			cvReleaseMat(&tempAdd);
			cvReleaseMat(&HF);
	}
	else if(setDlg.m_matchType==1)
	{
		H=cvCreateMat(3,3,CV_32FC1);
		H=findHMatrix(m_match->leftSeq,m_match->rightSeq);
		//对图像的四个顶点进行映射，以自适应的确定边界
		int wi=srcImage1->width;
		int he=srcImage1->height;
		// 	float quard[]={0,wi,0,wi,0,0,he,he,1,1,1,1};
		// 	CvMat src;
		// 	cvInitMatHeader(&src,3,4,CV_32FC1,quard);
		/*	double tem=cvmGet(&src,0,1);*/
		CvMat *src=cvCreateMat(3,4,CV_32FC1);
		cvZero(src);
		cvmSet(src,0,1,wi);
		cvmSet(src,0,3,wi);
		cvmSet(src,1,2,he);
		cvmSet(src,1,3,he);
		cvmSet(src,2,0,1.0);
		cvmSet(src,2,1,1.0);
		cvmSet(src,2,2,1.0);
		cvmSet(src,2,3,1.0);
		CvMat *dst=cvCreateMat(3,4,CV_32FC1);
		cvmMul(H,src,dst);

		cvmSet(dst,0,0,cvmGet(dst,0,0)/cvmGet(dst,2,0));
		cvmSet(dst,1,0,cvmGet(dst,1,0)/cvmGet(dst,2,0));
		cvmSet(dst,0,1,cvmGet(dst,0,1)/cvmGet(dst,2,1));
		cvmSet(dst,1,1,cvmGet(dst,1,1)/cvmGet(dst,2,1));
		cvmSet(dst,0,2,cvmGet(dst,0,2)/cvmGet(dst,2,2));
		cvmSet(dst,1,2,cvmGet(dst,1,2)/cvmGet(dst,2,2));
		cvmSet(dst,0,3,cvmGet(dst,0,3)/cvmGet(dst,2,3));
		cvmSet(dst,1,3,cvmGet(dst,1,3)/cvmGet(dst,2,3));
		double leftv,rightv,topv,bottomv;
		CvMat *row=cvCreateMat(1,4,CV_32FC1);
		cvGetRow(dst,row,0);
		cvMinMaxLoc(row,&leftv,&rightv);
		cvGetRow(dst,row,1);
		cvMinMaxLoc(row,&topv,&bottomv);
		int fl,fr,ft,fb;
		fl=((leftv>0)?0:leftv);
		fr=((rightv>srcImage2->width)?rightv:srcImage2->width);
		ft=((topv>0)?0:topv);
		fb=((bottomv>srcImage2->height)?bottomv:srcImage2->height);

		CvMat *tempAdd=cvCreateMat(3,3,CV_32FC1);
		cvZero(tempAdd);
		cvmSet(tempAdd,0,2,fl);
		cvmSet(tempAdd,1,2,ft);
		CvMat *HF=cvCreateMat(3,3,CV_32FC1);
		cvSub(H,tempAdd,HF);
		showImage1=cvCreateImage(cvSize(fr-fl,fb-ft),8,3);
		cvWarpPerspective(srcImage1,showImage1,HF,CV_INTER_LINEAR|CV_WARP_FILL_OUTLIERS,cvScalar(0));
		IplImage *fushion=cvCreateImage(cvSize(fr-fl,fb-ft),8,3);
		cvSetImageROI(fushion,cvRect(-fl,-ft,srcImage2->width,srcImage2->height));
		cvCopy(srcImage2,fushion);
		cvResetImageROI(fushion);

		double alpha,beta;
		CvScalar scalar1,scalar2;
		for(int i=0;i<fb-ft;i++)
			for(int j=0;j<fr-fl;j++)
			{
				alpha=beta=0.5;
				scalar1=cvGet2D(showImage1,i,j);
				scalar2=cvGet2D(fushion,i,j);
				if(scalar1.val[0]+scalar1.val[1]+scalar1.val[2]<1)
				{
					alpha=0;
					beta=1.0;
				}
				else if(scalar2.val[0]+scalar2.val[1]+scalar2.val[2]<1)
				{
					alpha=1.0;
					beta=0;
				}
				cvSetImageROI(showImage1,cvRect(j,i,1,1));
				cvSetImageROI(fushion,cvRect(j,i,1,1));
				cvAddWeighted(showImage1,alpha,fushion,beta,0,showImage1);
				cvResetImageROI(showImage1);
				cvResetImageROI(fushion);
			}
			cvReleaseMat(&HF);
			//cvReleaseMat(&H);
			cvReleaseMat(&tempAdd);
	}
	ShowState("图像配准/拼接完成！！");
	fused=true;
}

void CRegistrationDoc::OnSettingSetting()
{
// 	if(setDlg.DoModal()==IDOK)
// 	{
// 		setDlg.
// 	}
	setDlg.DoModal();
}

void CRegistrationDoc::OnHelpDescription()
{
// 	CDescription des;
// 	des.DoModal();
	CSeetingdescription des;
	des.DoModal();
}

CvMat* CRegistrationDoc::findHMatrix(CvSeq *seq1,CvSeq *seq2)
{
	if(seq1->total!=seq2->total)
		return NULL;
	if(setDlg.m_matchType==0)
	{
		int cornerPair=seq1->total;
		CvMat *A=cvCreateMat(2*cornerPair,6,CV_32FC1);
		CvMat *B=cvCreateMat(2*cornerPair,1,CV_32FC1);
		CvMat *HOR=cvCreateMat(6,1,CV_32FC1);
		CvMat *H=cvCreateMat(2,3,CV_32FC1);
		cvZero(A);
		cvZero(B);
		for(int i=0;i<cornerPair;i++)
		{
			CvPoint *p=(CvPoint *)cvGetSeqElem(seq1,i);
			CvPoint *q=(CvPoint *)cvGetSeqElem(seq2,i);
			cvmSet(A,i,0,p->x);
			cvmSet(A,i,1,p->y);
			cvmSet(A,i,4,1.0);
			cvmSet(A,i+cornerPair,2,p->x);
			cvmSet(A,i+cornerPair,3,p->y);
			cvmSet(A,i+cornerPair,5,1.0);

			cvmSet(B,i,0,q->x);
			cvmSet(B,i+cornerPair,0,q->y);
		}
		CvMat *temp=cvCreateMat(6,2*cornerPair,CV_32FC1);
		cvInvert(A,temp,CV_SVD);
		cvmMul(temp,B,HOR);
		cvmSet(H,0,0,cvmGet(HOR,0,0));
		cvmSet(H,0,1,cvmGet(HOR,1,0));
		cvmSet(H,0,2,cvmGet(HOR,4,0));
		cvmSet(H,1,0,cvmGet(HOR,2,0));
		cvmSet(H,1,1,cvmGet(HOR,3,0));
		cvmSet(H,1,2,cvmGet(HOR,5,0));
		cvReleaseMat(&temp);
		cvReleaseMat(&A);
		cvReleaseMat(&B);
		cvReleaseMat(&HOR);
		return H;
	}
	else if(setDlg.m_matchType==1)
	{
		int cornerPair=seq1->total;
		CvMat *A=cvCreateMat(3*cornerPair,8,CV_32FC1);
		CvMat *B=cvCreateMat(3*cornerPair,1,CV_32FC1);
		CvMat *HOR=cvCreateMat(8,1,CV_32FC1);
		CvMat *H=cvCreateMat(3,3,CV_32FC1);
		cvZero(A);
		cvZero(B);
		for(int i=0;i<cornerPair;i++)
		{
			CvPoint *p=(CvPoint *)cvGetSeqElem(seq1,i);
			CvPoint *q=(CvPoint *)cvGetSeqElem(seq2,i);
			cvmSet(A,i,0,p->x);
			cvmSet(A,i,1,p->y);
			cvmSet(A,i,2,1.0);
			cvmSet(A,i+cornerPair,3,p->x);
			cvmSet(A,i+cornerPair,4,p->y);
			cvmSet(A,i+cornerPair,5,1.0);
			cvmSet(A,i+2*cornerPair,6,p->x);
			cvmSet(A,i+2*cornerPair,7,p->y);
			//cvmSet(A,i+2*cornerPair,8,1.0);

			cvmSet(B,i,0,q->x);
			cvmSet(B,i+cornerPair,0,q->y);
			cvmSet(B,i+2*cornerPair,0,0);
		}
		CvMat *temp=cvCreateMat(8,3*cornerPair,CV_32FC1);
		cvInvert(A,temp,CV_SVD);
		cvmMul(temp,B,HOR);
		cvmSet(H,0,0,cvmGet(HOR,0,0));
		cvmSet(H,0,1,cvmGet(HOR,1,0));
		cvmSet(H,0,2,cvmGet(HOR,2,0));
		cvmSet(H,1,0,cvmGet(HOR,3,0));
		cvmSet(H,1,1,cvmGet(HOR,4,0));
		cvmSet(H,1,2,cvmGet(HOR,5,0));
		cvmSet(H,2,0,cvmGet(HOR,6,0));
		cvmSet(H,2,1,cvmGet(HOR,7,0));
		cvmSet(H,2,2,1.0);
		cvReleaseMat(&temp);
		cvReleaseMat(&A);
		cvReleaseMat(&B);
		cvReleaseMat(&HOR);
		return H;
	}
}
void CRegistrationDoc::OnRematch()
{

}

void CRegistrationDoc::OnRematchAccuratepoints()
{
	if(!fused)
	{
		ShowState("强烈建议你先完成图像拼接后再执行该步操作...");
		return;
	}
	CMainFrame *pFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;
	pFrame->needSplite=true;
	pFrame->setView(true);
	OnCorners();
	m_match->initMatch(setDlg.patch_radius,setDlg.max_disparity);

	double threshold=setDlg.m_rematchthreshold;//set the threshold
	int i=0;
	if(setDlg.m_matchType==0)
	{
		while(i<m_match->initSeq1->total)
		{
			CvPoint *p=(CvPoint *)cvGetSeqElem(m_match->initSeq1,i);
			CvPoint *q=(CvPoint *)cvGetSeqElem(m_match->initSeq2,i);
			CvMat *mat=cvCreateMat(3,1,CV_32FC1);
			CvMat *result=cvCreateMat(2,1,CV_32FC1);
			cvmSet(mat,0,0,p->x);
			cvmSet(mat,1,0,p->y);
			cvmSet(mat,2,0,1.0);
			cvmMul(H,mat,result);
			double x,y;
			x=cvmGet(result,0,0);
			y=cvmGet(result,1,0);
			if(((x-q->x)*(x-q->x)+(y-q->y)*(y-q->y))>=threshold)
			{
			cvSeqRemove(m_match->initSeq1,i);
			cvSeqRemove(m_match->initSeq2,i);
			}
			else
			i++;
			cvReleaseMat(&mat);
			cvReleaseMat(&result);
		}
	}
	else if(setDlg.m_matchType==1)
	{
		while(i<m_match->initSeq1->total)
		{
			CvPoint *p=(CvPoint *)cvGetSeqElem(m_match->initSeq1,i);
			CvPoint *q=(CvPoint *)cvGetSeqElem(m_match->initSeq2,i);

			CvMat *mat=cvCreateMat(3,1,CV_32FC1);
			CvMat *result=cvCreateMat(3,1,CV_32FC1);
			cvmSet(mat,0,0,p->x);
			cvmSet(mat,1,0,p->y);
			cvmSet(mat,2,0,1.0);
			cvmMul(H,mat,result);
			double x,y,z;
			x=cvmGet(result,0,0);
			y=cvmGet(result,1,0);
			z=cvmGet(result,2,0);
			if(((x/z-q->x)*(x/z-q->x)+(y/z-q->y)*(y/z-q->y))>=threshold)
			{
			cvSeqRemove(m_match->initSeq1,i);
			cvSeqRemove(m_match->initSeq2,i);
			}
			else
			i++;
			cvReleaseMat(&mat);
			cvReleaseMat(&result);
		}

	}
	m_match->leftSeq=cvCloneSeq(m_match->initSeq1);
	m_match->rightSeq=cvCloneSeq(m_match->initSeq2);
	for(i=0;i<m_match->initSeq1->total;i++)
	{
		CvPoint *p=(CvPoint *)cvGetSeqElem(m_match->initSeq1,i);
		CvPoint *q=(CvPoint *)cvGetSeqElem(m_match->initSeq2,i);
		cvLine(showImage1,*p,*q,CV_RGB(0,255,0));
		cvLine(showImage2,*p,*q,CV_RGB(0,255,0));
	}
	// 	UpdateAllViews(NULL);
	CString temp;
	temp.Format("%d对匹配点",m_match->initSeq1->total);
	ShowState(temp);
	cornerdetected=true;
	matched=true;
	rematched=true;
	fused=false;
}

void CRegistrationDoc::OnRematchDensepoints()
{
	if(!fused)
	{
		ShowState("强烈建议你先完成图像拼接后再执行该步操作...");
		return;
	}
	CMainFrame *pFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;
	pFrame->needSplite=true;
	pFrame->setView(true);
	OnCorners();
	m_match->initMatch(setDlg.patch_radius,setDlg.max_disparity);

	double threshold=setDlg.m_rematchthreshold;//set the threshold
	int i=0;
	if(setDlg.m_matchType==0)
	{
		cvClearSeq(m_match->initSeq1);
		cvClearSeq(m_match->initSeq2);
		for(i=0;i<m_match->cornerCount1;i++)
		{
			CvPoint p,q;
			p.x=m_match->corner1[i].x;
			p.y=m_match->corner1[i].y;

			CvMat *mat=cvCreateMat(3,1,CV_32FC1);
			CvMat *result=cvCreateMat(2,1,CV_32FC1);
			cvmSet(mat,0,0,p.x);
			cvmSet(mat,1,0,p.y);
			cvmSet(mat,2,0,1.0);
			cvmMul(H,mat,result);
			double x,y;
			x=cvmGet(result,0,0);
			y=cvmGet(result,1,0);
			for(int j=0;j<m_match->cornerCount2;j++)
			{
				q.x=m_match->corner2[j].x;
				q.y=m_match->corner2[j].y;
				if((x-q.x)*(x-q.x)+(y-q.y)*(y-q.y)<=threshold)
				{
					cvSeqPush(m_match->initSeq1,&p);
					cvSeqPush(m_match->initSeq2,&q);
					break;
				}
			}
			cvReleaseMat(&mat);
			cvReleaseMat(&result);
		}
	}
	else if(setDlg.m_matchType==1)
	{
		cvClearSeq(m_match->initSeq1);
		cvClearSeq(m_match->initSeq2);
		for(i=0;i<m_match->cornerCount1;i++)
		{
			CvPoint p,q;
			p.x=m_match->corner1[i].x;
			p.y=m_match->corner1[i].y;

			CvMat *mat=cvCreateMat(3,1,CV_32FC1);
			CvMat *result=cvCreateMat(3,1,CV_32FC1);
			cvmSet(mat,0,0,p.x);
			cvmSet(mat,1,0,p.y);
			cvmSet(mat,2,0,1.0);
			cvmMul(H,mat,result);
			double x,y,z;
			x=cvmGet(result,0,0);
			y=cvmGet(result,1,0);
			z=cvmGet(result,2,0);
			for(int j=0;j<m_match->cornerCount2;j++)
			{
				q.x=m_match->corner2[j].x;
				q.y=m_match->corner2[j].y;
				if((x/z-q.x)*(x/z-q.x)+(y/z-q.y)*(y/z-q.y)<=threshold)
				{
					cvSeqPush(m_match->initSeq1,&p);
					cvSeqPush(m_match->initSeq2,&q);
					break;
				}
			}
			cvReleaseMat(&mat);
			cvReleaseMat(&result);
		}

	}
	m_match->leftSeq=cvCloneSeq(m_match->initSeq1);
	m_match->rightSeq=cvCloneSeq(m_match->initSeq2);
	for(i=0;i<m_match->initSeq1->total;i++)
	{
		CvPoint *p=(CvPoint *)cvGetSeqElem(m_match->initSeq1,i);
		CvPoint *q=(CvPoint *)cvGetSeqElem(m_match->initSeq2,i);
		cvLine(showImage1,*p,*q,CV_RGB(0,255,0));
		cvLine(showImage2,*p,*q,CV_RGB(0,255,0));
	}
	// 	UpdateAllViews(NULL);
	CString temp;
	temp.Format("%d对匹配点",m_match->initSeq1->total);
	ShowState(temp);
	cornerdetected=true;
	matched=true;
	rematched=true;
	fused=false;
}

void CRegistrationDoc::OnExport2dpoints()
{
	if(!rematched)
	{
		ShowState("为了得到更为准确的匹配点对，请先完成角点重匹配！");
		return;
	}
	ofstream pleft("left.txt");
	ofstream pright("right.txt");
	for(int i=0;i<m_match->initSeq1->total;i++)
	{
		CvPoint *p=(CvPoint *)cvGetSeqElem(m_match->initSeq1,i);
		CvPoint *q=(CvPoint *)cvGetSeqElem(m_match->initSeq2,i);
		pleft<<p->x<<" "<<p->y<<endl;
		pright<<q->x<<" "<<q->y<<endl;
	}
	ShowState("2D匹配点对导出完毕！保存在根目录下的left.txt和right.txt中...");
}

void CRegistrationDoc::OnHelpdocument()
{
	ShellExecute(NULL,"OPEN","Note.txt",NULL,NULL,SW_SHOW);
}

void CRegistrationDoc::OnExport3dpoints()
{
	ofstream fmatrix("F.txt");
	if(!rematched)
	{
		ShowState("为了得到更为准确的匹配点对，请先完成角点重匹配！");
		return;
	}
	if(F!=NULL)
		cvReleaseMat(&F);
	int total=m_match->initSeq1->total;
	CvMat *point1=cvCreateMat(total,2,CV_32FC1);
	CvMat *point2=cvCreateMat(total,2,CV_32FC1);
	F=cvCreateMat(3,3,CV_64FC1);
	for(int i=0;i<m_match->initSeq1->total;i++)
	{
		CvPoint *p=(CvPoint *)cvGetSeqElem(m_match->initSeq1,i);
		CvPoint *q=(CvPoint *)cvGetSeqElem(m_match->initSeq2,i);
		cvmSet(point1,i,0,p->x);
		cvmSet(point1,i,1,p->y);
		cvmSet(point2,i,0,q->x);
		cvmSet(point2,i,1,q->y);
	}
	cvFindFundamentalMat(point1,point2,F,CV_FM_RANSAC,1.5,0.99,0);
	fmatrix<<cvmGet(F,0,0)<<" "<<cvmGet(F,0,1)<<" "<<cvmGet(F,0,2)<<endl
		<<cvmGet(F,1,0)<<" "<<cvmGet(F,1,1)<<" "<<cvmGet(F,1,2)<<endl
		<<cvmGet(F,2,0)<<" "<<cvmGet(F,2,1)<<" "<<cvmGet(F,2,2)<<endl;

	//3D reconstrction using the Essential Matrix
	double b[9],c[9],d[9],e[9];
	double k[]={653.485,0,320,0,664.615,240,0,0,1};//intrinsic parameters
	CvMat K,U,V,W,E;
	cvInitMatHeader( &K, 3, 3, CV_32FC1, k);
	cvInitMatHeader( &U, 3, 3, CV_32FC1, b);
	cvInitMatHeader( &V, 3, 3, CV_32FC1, c);
	cvInitMatHeader( &W, 3, 3, CV_32FC1, d);
	cvInitMatHeader( &E, 3, 3, CV_32FC1, e);
	//cvGEMM(&K,F,1,NULL,0,&E,CV_GEMM_A_T);
	cvTranspose(&K,&E);
	cvmMul(&E,F,&E);
	//cvGEMM(&E,&K,1,NULL,0,&E,0);
	cvSVD(&E,&W,&U,&V);

	double r1,s,t;
	r1=cvmGet(&W,0,0);
	s=cvmGet(&W,1,1);
	t=(r1+s)/2;
	double a2[]={t,0,0,0,t,0,0,0,0};
	double b2[9];
	CvMat D2,E2;
	cvInitMatHeader(&D2,3,3,CV_32FC1,a2);
	cvInitMatHeader(&E2,3,3,CV_32FC1,b2);
	cvGEMM(&U,&D2,1,NULL,0,&E2,0);
	cvGEMM(&E2,&V,1,NULL,0,&E2,CV_GEMM_B_T);

	double u1[9],v1[9],w1[9];
	CvMat U1,V1,W1;
	cvInitMatHeader( &U1, 3, 3, CV_32FC1, u1);
	cvInitMatHeader( &V1, 3, 3, CV_32FC1, v1);
	cvInitMatHeader( &W1, 3, 3, CV_32FC1, w1);
	cvSVD(&E2,&W1,&U1,&V1);

	double a3[]={0,-1,0,1,0,0,0,0,1};
	double b3[]={0,0,1};
	double ro[9],tr[3];
	CvMat A3,B3,RO,TR;
	cvInitMatHeader( &A3, 3, 3, CV_32FC1, a3);
	cvInitMatHeader( &B3, 3, 1, CV_32FC1, b3);
	cvInitMatHeader( &RO, 3, 3, CV_32FC1, ro);
	cvInitMatHeader( &TR, 3, 1, CV_32FC1, tr);
	cvGEMM(&U1,&A3,1,NULL,0,&E2,0);
	cvGEMM(&E2,&V1,1,NULL,0,&RO,CV_GEMM_B_T);
	cvGEMM(&U1,&B3,1,NULL,0,&TR,0);

	CvMat *P1,*P2,Ma,Mb;
	P1=cvCreateMat(3,4,CV_32FC1);
	P2=cvCreateMat(3,4,CV_32FC1);
	double a4[]={1,0,0,0,0,1,0,0,0,0,1,0};
	double b4[]={cvmGet(&RO,0,0),cvmGet(&RO,0,1),cvmGet(&RO,0,2),cvmGet(&TR,0,0),
	cvmGet(&RO,1,0),cvmGet(&RO,1,1),cvmGet(&RO,1,2),cvmGet(&TR,1,0),
	cvmGet(&RO,2,0),cvmGet(&RO,2,1),cvmGet(&RO,2,2),cvmGet(&TR,2,0)};
	cvInitMatHeader( &Ma, 3, 4, CV_32FC1, a4);
	cvInitMatHeader( &Mb, 3, 4, CV_32FC1, b4);
	cvGEMM(&K,&Ma,1,NULL,0,P1,0);
	cvGEMM(&K,&Mb,1,NULL,0,P2,0);

	ofstream outpt("3dpt.txt");
	//	double l[1000];
	//	double r[1000];
	double value1,value2,value3,value4;
	CvMat C4;
	CvMat *U2,*W2,*V2;
	U2=cvCreateMat(4,4,CV_32FC1);
	V2=cvCreateMat(4,4,CV_32FC1);
	W2=cvCreateMat(4,4,CV_32FC1);
	for(int i=0;i<m_match->initSeq1->total;i++)
	{
		CvPoint *p=(CvPoint *)cvGetSeqElem(m_match->initSeq1,i);
		CvPoint *q=(CvPoint *)cvGetSeqElem(m_match->initSeq2,i);
		value1=p->x;
		value2=p->y;
		value3=q->x;
		value4=q->y;
		double c4[]={cvmGet(P1,2,0)*value1-cvmGet(P1,0,0),cvmGet(P1,2,1)*value1-cvmGet(P1,0,1),
		cvmGet(P1,2,2)*value1-cvmGet(P1,0,2),cvmGet(P1,2,3)*value1-cvmGet(P1,0,3),
		cvmGet(P1,2,0)*value2-cvmGet(P1,1,0),cvmGet(P1,2,1)*value2-cvmGet(P1,1,1),
		cvmGet(P1,2,2)*value2-cvmGet(P1,1,2),cvmGet(P1,2,3)*value2-cvmGet(P1,1,3),
		cvmGet(P2,2,0)*value3-cvmGet(P2,0,0),cvmGet(P2,2,1)*value3-cvmGet(P2,0,1),
		cvmGet(P2,2,2)*value3-cvmGet(P2,0,2),cvmGet(P2,2,3)*value3-cvmGet(P2,0,3),
		cvmGet(P2,2,0)*value4-cvmGet(P2,1,0),cvmGet(P2,2,1)*value4-cvmGet(P2,1,1),
		cvmGet(P2,2,2)*value4-cvmGet(P2,1,2),cvmGet(P2,2,3)*value4-cvmGet(P2,1,3)};
		cvInitMatHeader(&C4,4,4,CV_32FC1,c4);
		cvSVD(&C4,W2,U2,V2);
		outpt<<cvmGet(V2,0,4)/cvmGet(V2,3,4)<<" "<<cvmGet(V2,1,4)/cvmGet(V2,3,4)<<" "<<cvmGet(V2,2,4)/cvmGet(V2,3,4)<<endl;
	}
	cvReleaseMat(&U2);
	cvReleaseMat(&V2);
	cvReleaseMat(&W2);
	cvReleaseMat(&P1);
	cvReleaseMat(&P2);
	ShowState("3D坐标点生成完成！保存在根目录下的3dpt.txt和中...");
}