#pragma once

#include "RegistrationDoc.h"
// CRegistrationView1 视图

class CRegistrationView1 : public CScrollView
{
	DECLARE_DYNCREATE(CRegistrationView1)

protected:
	CRegistrationView1();           // 动态创建所使用的受保护的构造函数
	virtual ~CRegistrationView1();
public:
	CRegistrationDoc* GetDocument() const;
	HCURSOR hrcursor;
public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void OnDraw(CDC* pDC);      // 重写以绘制该视图
	virtual void OnInitialUpdate();     // 构造后的第一次

	DECLARE_MESSAGE_MAP()
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
public:
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};


