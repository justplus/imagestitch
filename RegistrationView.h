// RegistrationView.h : CRegistrationView 类的接口
//


#pragma once
#include "RegistrationDoc.h"

class CRegistrationView : public CScrollView
{
protected: // 仅从序列化创建
	CRegistrationView();
	DECLARE_DYNCREATE(CRegistrationView)

// 属性
public:
	CRegistrationDoc* GetDocument() const;
	HCURSOR hlcursor;
// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CRegistrationView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
public:
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // RegistrationView.cpp 中的调试版本
inline CRegistrationDoc* CRegistrationView::GetDocument() const
   { return reinterpret_cast<CRegistrationDoc*>(m_pDocument); }
#endif

