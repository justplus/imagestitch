// RegistrationView.h : CRegistrationView ��Ľӿ�
//


#pragma once
#include "RegistrationDoc.h"

class CRegistrationView : public CScrollView
{
protected: // �������л�����
	CRegistrationView();
	DECLARE_DYNCREATE(CRegistrationView)

// ����
public:
	CRegistrationDoc* GetDocument() const;
	HCURSOR hlcursor;
// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // ������һ�ε���
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CRegistrationView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
public:
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // RegistrationView.cpp �еĵ��԰汾
inline CRegistrationDoc* CRegistrationView::GetDocument() const
   { return reinterpret_cast<CRegistrationDoc*>(m_pDocument); }
#endif

