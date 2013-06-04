// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "Registration.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_STATEINFO,
// 	ID_INDICATOR_CAPS,
// 	ID_INDICATOR_NUM,
// 	ID_INDICATOR_SCRL,
};


// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	splited=false;
	needSplite=true;
}

CMainFrame::~CMainFrame()
{
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}

	// TODO: 如果不需要可停靠工具栏，则删除这三行
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	m_wndStatusBar.SetPaneInfo(0,ID_SEPARATOR,0,200);
	m_wndStatusBar.SetPaneInfo(1,ID_INDICATOR_STATEINFO,0,700);
	bitmap.LoadBitmap(IDB_BITMAP1);
	GetMenu()->GetSubMenu(0)->SetMenuItemBitmaps(0,MF_BYPOSITION,&bitmap,&bitmap);
	bitmap.LoadBitmap(IDB_BITMAP2);
	GetMenu()->GetSubMenu(0)->SetMenuItemBitmaps(1,MF_BYPOSITION,&bitmap,&bitmap);
	bitmap.LoadBitmap(IDB_BITMAP3);
	GetMenu()->GetSubMenu(2)->SetMenuItemBitmaps(0,MF_BYPOSITION,&bitmap,&bitmap);
	bitmap.LoadBitmap(IDB_BITMAP4);
	GetMenu()->GetSubMenu(2)->SetMenuItemBitmaps(1,MF_BYPOSITION,&bitmap,&bitmap);
	bitmap.LoadBitmap(IDB_BITMAP5);
	GetMenu()->GetSubMenu(2)->SetMenuItemBitmaps(2,MF_BYPOSITION,&bitmap,&bitmap);
	bitmap.LoadBitmap(IDB_BITMAP6);
	GetMenu()->GetSubMenu(2)->SetMenuItemBitmaps(5,MF_BYPOSITION,&bitmap,&bitmap);
	bitmap.LoadBitmap(IDB_BITMAP7);
	GetMenu()->GetSubMenu(2)->SetMenuItemBitmaps(4,MF_BYPOSITION,&bitmap,&bitmap);
	bitmap.LoadBitmap(IDB_BITMAP8);
	GetMenu()->GetSubMenu(3)->GetSubMenu(0)->SetMenuItemBitmaps(1,MF_BYPOSITION,&bitmap,&bitmap);
	bitmap.LoadBitmap(IDB_BITMAP9);
	GetMenu()->GetSubMenu(3)->SetMenuItemBitmaps(1,MF_BYPOSITION,&bitmap,&bitmap);
	bitmap.LoadBitmap(IDB_BITMAP10);
	GetMenu()->GetSubMenu(3)->SetMenuItemBitmaps(2,MF_BYPOSITION,&bitmap,&bitmap);
	bitmap.LoadBitmap(IDB_BITMAP11);
	GetMenu()->GetSubMenu(4)->SetMenuItemBitmaps(0,MF_BYPOSITION,&bitmap,&bitmap);
	bitmap.LoadBitmap(IDB_BITMAP12);
	GetMenu()->GetSubMenu(6)->SetMenuItemBitmaps(0,MF_BYPOSITION,&bitmap,&bitmap);
	return 0;
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{
// 	return m_wndSplitter.Create(this,
// 		2, 2,               // TODO: 调整行数和列数
// 		CSize(10, 10),      // TODO: 调整最小窗格大小
// 		pContext);
	if(m_wndSplitter.CreateStatic(this,1,2)==NULL)
		return false;
	CRect rect;
	GetClientRect(&rect);
	m_wndSplitter.CreateView(0,0,RUNTIME_CLASS(CRegistrationView),CSize(rect.Width()/2,0),pContext);
	m_wndSplitter.CreateView(0,1,RUNTIME_CLASS(CRegistrationView1),CSize(rect.Width()/2,0),pContext);
	splited=true;
	return true;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	return TRUE;
}


// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG


// CMainFrame 消息处理程序




void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
	CFrameWnd::OnSize(nType, cx, cy);
	setView(needSplite);	
// 	CRect rect;
// 	GetClientRect(&rect);
// 
// 	if(splited)
// 	{
// 		m_wndSplitter.SetColumnInfo(0,rect.Width()/2-4,10);//"-4"为消除分割栏宽度影响
// 		m_wndSplitter.SetColumnInfo(1,rect.Width()/2,10);
// 		m_wndSplitter.RecalcLayout();
// 	}
}

void CMainFrame::setView(bool needSplite)
{
	if(needSplite==false)
	{
		CRect rect;
		GetClientRect(&rect);
		if(splited)
		{
			m_wndSplitter.SetRowInfo(0, rect.Height(), 10); 
			m_wndSplitter.SetColumnInfo(0,rect.Width(),10);
			m_wndSplitter.SetColumnInfo(1,0,0);
			m_wndSplitter.RecalcLayout();
		}
	}
	else if(needSplite==true)
	{
		CRect rect;
		GetClientRect(&rect);
		if(splited)
		{
			m_wndSplitter.SetRowInfo(0, rect.Height(), 10); 
			m_wndSplitter.SetColumnInfo(0,rect.Width()/2,10);
			m_wndSplitter.SetColumnInfo(1,rect.Width()/2,10);
			m_wndSplitter.RecalcLayout();
		}
	}
}