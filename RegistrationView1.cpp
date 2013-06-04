// RegistrationView1.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Registration.h"
#include "RegistrationDoc.h"
#include "RegistrationView1.h"


// CRegistrationView1

IMPLEMENT_DYNCREATE(CRegistrationView1, CScrollView)

CRegistrationView1::CRegistrationView1()
{

}

CRegistrationView1::~CRegistrationView1()
{
}


BEGIN_MESSAGE_MAP(CRegistrationView1, CScrollView)
	ON_WM_SETCURSOR()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CRegistrationView1 ��ͼ

void CRegistrationView1::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: �������ͼ�ĺϼƴ�С
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

void CRegistrationView1::OnDraw(CDC* pDC)
{
	CRegistrationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: �ڴ���ӻ��ƴ���
	if(pDoc->image2Opened)
	{
		CRect rect(0,0,pDoc->showImage2->width,pDoc->showImage2->height);
		CvvImage image;
		image.CopyOf(pDoc->showImage2,3);
		HDC hdc=pDC->GetSafeHdc();
		image.DrawToHDC(hdc,&rect);
	}
}


// CRegistrationView1 ���

#ifdef _DEBUG
void CRegistrationView1::AssertValid() const
{
	CScrollView::AssertValid();
}

#ifndef _WIN32_WCE
void CRegistrationView1::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif

#endif //_DEBUG
CRegistrationDoc* CRegistrationView1::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRegistrationDoc)));
	return (CRegistrationDoc*)m_pDocument;
}

// CRegistrationView1 ��Ϣ�������

BOOL CRegistrationView1::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ����ר�ô����/����û���
	cs.lpszClass=AfxRegisterWndClass(CS_DBLCLKS|CS_HREDRAW|CS_VREDRAW,AfxGetApp()->LoadCursor(IDC_ARROW),CreateSolidBrush(RGB(116,211,211)));
	return CScrollView::PreCreateWindow(cs);
}

void CRegistrationView1::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	CRegistrationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if(pDoc->image2Opened)
	{
		SetScrollSizes(MM_TEXT,CSize(pDoc->showImage2->width,pDoc->showImage2->height));
		Invalidate(true);
	}
}

BOOL CRegistrationView1::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	SetCursor(hrcursor);
	return true;
	//return CScrollView::OnSetCursor(pWnd, nHitTest, message);
}

void CRegistrationView1::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(GetDocument()->deleteMatched)
	{
		hrcursor= LoadCursor(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDC_CURSOR1));
	}
	else if(GetDocument()->addMatched)
	{
		hrcursor= LoadCursor(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDC_CURSOR2));
	}
	else
	{
		hrcursor=LoadCursor(NULL,MAKEINTRESOURCE(IDC_ARROW));
	}
	Invalidate(false);
	CScrollView::OnMouseMove(nFlags, point);
}

void CRegistrationView1::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(GetDocument()->deleteMatched)
	{
		if(GetDocument()->matched)
		{
			for(int i=0;i<GetDocument()->m_match->rightSeq->total;i++)
			{
				CvPoint *p=(CvPoint*)cvGetSeqElem(GetDocument()->m_match->leftSeq,i);
				CvPoint *q=(CvPoint*)cvGetSeqElem(GetDocument()->m_match->rightSeq,i);
				if((point.x-q->x)*(point.x-q->x)+(point.y-q->y)*(point.y-q->y)<25)
				{
					cvCircle(GetDocument()->m_match->srcImage1,*p,4,CV_RGB(255,0,0));
					cvCircle(GetDocument()->m_match->srcImage2,*q,4,CV_RGB(255,0,0));
					cvSeqRemove(GetDocument()->m_match->initSeq1,i);
					cvSeqRemove(GetDocument()->m_match->initSeq2,i);
					CString temp;
					temp.Format("���޳�һ�������㣬��%d��",GetDocument()->m_match->leftSeq->total);
					GetDocument()->ShowState(temp);
					GetDocument()->UpdateAllViews(NULL);
				}
			}
		}
		else
			GetDocument()->ShowState("ȷ���Ƿ��ѽ���������ƥ��....");
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
					if((point.x-q->x)*(point.x-q->x)+(point.y-q->y)*(point.y-q->y)<36)
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

						cvSeqPush(GetDocument()->m_match->chooseSeq1,p);
						cvSeqPush(GetDocument()->m_match->chooseSeq2,q);
						CString temp;
						temp.Format("��ѡ��%d����",GetDocument()->m_match->chooseSeq1->total);
						GetDocument()->ShowState(temp);
						GetDocument()->UpdateAllViews(NULL);
					}
				}
			}
		}
		else
			GetDocument()->ShowState("ȷ���Ƿ��ѽ���������ƥ��....");
	}
	CScrollView::OnLButtonDown(nFlags, point);
}
