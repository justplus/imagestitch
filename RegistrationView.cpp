// RegistrationView.cpp : CRegistrationView 类的实现
//

#include "stdafx.h"
#include "Registration.h"

#include "RegistrationDoc.h"
#include "RegistrationView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRegistrationView

IMPLEMENT_DYNCREATE(CRegistrationView, CScrollView)

BEGIN_MESSAGE_MAP(CRegistrationView, CScrollView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_WM_SETCURSOR()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CRegistrationView 构造/析构

CRegistrationView::CRegistrationView()
{
	// TODO: 在此处添加构造代码
}

CRegistrationView::~CRegistrationView()
{
}

BOOL CRegistrationView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	cs.lpszClass=AfxRegisterWndClass(CS_DBLCLKS|CS_HREDRAW|CS_VREDRAW,AfxGetApp()->LoadCursor(IDC_ARROW),CreateSolidBrush(RGB(116,211,211)));
	return CScrollView::PreCreateWindow(cs);
}

// CRegistrationView 绘制

void CRegistrationView::OnDraw(CDC* pDC)
{
	CRegistrationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	if(pDoc->image1Opened)
	{
		CRect rect(0,0,pDoc->showImage1->width,pDoc->showImage1->height);
		CvvImage image;
		image.CopyOf(pDoc->showImage1,3);
		HDC hdc=pDC->GetSafeHdc();
		image.DrawToHDC(hdc,&rect);
	}
	// TODO: 在此处为本机数据添加绘制代码
}

void CRegistrationView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 计算此视图的合计大小
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CRegistrationView 打印

BOOL CRegistrationView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CRegistrationView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CRegistrationView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CRegistrationView 诊断

#ifdef _DEBUG
void CRegistrationView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CRegistrationView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CRegistrationDoc* CRegistrationView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRegistrationDoc)));
	return (CRegistrationDoc*)m_pDocument;
}
#endif //_DEBUG


// CRegistrationView 消息处理程序

void CRegistrationView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	CRegistrationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if(pDoc->image1Opened)
	{
		SetScrollSizes(MM_TEXT,CSize(pDoc->showImage1->width,pDoc->showImage1->height));
// 		m_frame1.Create(pDoc->srcImage1->width,pDoc->srcImage1->height,24);
// 		showImage1=m_frame1.GetImage();
		Invalidate(true);
	}
}

BOOL CRegistrationView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SetCursor(hlcursor);
	return true;
	//return CScrollView::OnSetCursor(pWnd, nHitTest, message);
}

void CRegistrationView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(GetDocument()->deleteMatched)
	{
		hlcursor= LoadCursor(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDC_CURSOR1));
	}
	else if(GetDocument()->addMatched)
	{
		hlcursor=LoadCursor(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDC_CURSOR2));
	}
	else
	{
		hlcursor=LoadCursor(NULL,MAKEINTRESOURCE(IDC_ARROW));
	}
	Invalidate(false);
	CScrollView::OnMouseMove(nFlags, point);
}

void CRegistrationView::OnLButtonDown(UINT nFlags, CPoint point)
{
	//删除误匹配点对
	if(GetDocument()->deleteMatched)
	{
		if(GetDocument()->matched)
		{
			for(int i=0;i<GetDocument()->m_match->leftSeq->total;i++)
			{
				CvPoint *p=(CvPoint*)cvGetSeqElem(GetDocument()->m_match->leftSeq,i);
				CvPoint *q=(CvPoint*)cvGetSeqElem(GetDocument()->m_match->rightSeq,i);
				if((point.x-p->x)*(point.x-p->x)+(point.y-p->y)*(point.y-p->y)<25)
				{
					cvCircle(GetDocument()->m_match->srcImage1,*p,4,CV_RGB(255,0,0));
					cvCircle(GetDocument()->m_match->srcImage2,*q,4,CV_RGB(255,0,0));
					cvSeqRemove(GetDocument()->m_match->initSeq1,i);
					cvSeqRemove(GetDocument()->m_match->initSeq2,i);
					CString temp;
					temp.Format("已剔除一对特征点，共%d对",GetDocument()->m_match->leftSeq->total);
					GetDocument()->ShowState(temp);
					GetDocument()->UpdateAllViews(NULL);
				}
			}
		}
		else
			GetDocument()->ShowState("确认是否已进行特征点匹配....");
	}
	else if(GetDocument()->addMatched)
	{
		if(GetDocument()->matched)
		{
			//int m=GetDocument()->k;
			if(GetDocument()->m_match->leftSeq->total>0)
			{
				for(int i=0;i<GetDocument()->m_match->leftSeq->total;i++)
				{
					CvPoint *p=(CvPoint*)cvGetSeqElem(GetDocument()->m_match->leftSeq,i);
					CvPoint *q=(CvPoint*)cvGetSeqElem(GetDocument()->m_match->rightSeq,i);
					if((point.x-p->x)*(point.x-p->x)+(point.y-p->y)*(point.y-p->y)<36)
					{
						cvLine( GetDocument()->m_match->srcImage1, cvPoint(p->x-5,p->y), cvPoint(p->x+5,p->y), CV_RGB(255,0,0) );
						cvLine( GetDocument()->m_match->srcImage1, cvPoint(p->x,p->y-5), cvPoint(p->x,p->y+5),  CV_RGB(255,0,0));
						cvLine( GetDocument()->m_match->srcImage1, cvPoint(p->x-5,p->y-1), cvPoint(p->x+5,p->y+1),  CV_RGB(255,0,0) );
						cvLine( GetDocument()->m_match->srcImage1, cvPoint(p->x-1,p->y-5), cvPoint(p->x+1,p->y+5),  CV_RGB(255,0,0) );
						cvLine( GetDocument()->m_match->srcImage1, cvPoint(p->x-5,p->y+1), cvPoint(p->x+5,p->y-1), CV_RGB(255,0,0) );
						cvLine( GetDocument()->m_match->srcImage1, cvPoint(p->x+1,p->y-5), cvPoint(p->x-1,p->y+5),  CV_RGB(255,0,0) );

						cvLine( GetDocument()->m_match->srcImage2, cvPoint(q->x-5,q->y), cvPoint(q->x+5,q->y), CV_RGB(255,0,0) );
						cvLine( GetDocument()->m_match->srcImage2, cvPoint(q->x,q->y-5), cvPoint(q->x,q->y+5),  CV_RGB(255,0,0));
						cvLine( GetDocument()->m_match->srcImage2, cvPoint(q->x-5,q->y-1), cvPoint(q->x+5,q->y+1),  CV_RGB(255,0,0) );
						cvLine( GetDocument()->m_match->srcImage2, cvPoint(q->x-1,q->y-5), cvPoint(q->x+1,q->y+5),  CV_RGB(255,0,0) );
						cvLine( GetDocument()->m_match->srcImage2, cvPoint(q->x-5,q->y+1), cvPoint(q->x+5,q->y-1), CV_RGB(255,0,0) );
						cvLine( GetDocument()->m_match->srcImage2, cvPoint(q->x+1,q->y-5), cvPoint(q->x-1,q->y+5),  CV_RGB(255,0,0) );
// 						GetDocument()->leftpoint[m]=cvPoint2D32f(p->x,p->y);
// 						GetDocument()->rightpoint[m]=cvPoint2D32f(q->x,q->y);
						cvSeqPush(GetDocument()->m_match->chooseSeq1,p);
						cvSeqPush(GetDocument()->m_match->chooseSeq2,q);
						CString temp;
						temp.Format("已选中%d个点",GetDocument()->m_match->chooseSeq1->total);
						GetDocument()->ShowState(temp);
						//GetDocument()->k++;
						GetDocument()->UpdateAllViews(NULL);
					}
				}
			}
		}
		else
			GetDocument()->ShowState("确认是否已进行特征点匹配....");
	}
		
	
	CScrollView::OnLButtonDown(nFlags, point);
}
