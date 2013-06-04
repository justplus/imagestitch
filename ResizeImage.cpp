// ResizeImage.cpp : 实现文件
//

#include "stdafx.h"
#include "Registration.h"
#include "ResizeImage.h"

// CResizeImage 对话框

IMPLEMENT_DYNAMIC(CResizeImage, CDialog)

CResizeImage::CResizeImage(CWnd* pParent /*=NULL*/)
	: CDialog(CResizeImage::IDD, pParent)
	, m_interMethod(_T(""))
{
	m_imageNo=0;
// 	CRegistrationApp* app=(CRegistrationApp*)AfxGetApp();
// 	m_width=app->image1Width;
// 	m_height=app->image1Height;
// 	m_heightper=100;
// 	m_widthper=100;
// 	m_maintainratio=true;
//	m_ratio=m_width*1.0/m_height;
}

CResizeImage::~CResizeImage()
{
	
}

void CResizeImage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_imageNo);
	DDX_Text(pDX, IDC_EDIT1, m_width);
	DDX_Text(pDX, IDC_EDIT2, m_widthper);
	DDX_Text(pDX, IDC_EDIT3, m_height);
	DDX_Text(pDX, IDC_EDIT4, m_heightper);
	DDX_Check(pDX, IDC_CHECK1, m_maintainratio);
	DDX_Text(pDX, IDC_STATIC1, m_ratio);
	DDX_CBString(pDX, IDC_COMBO1, m_interMethod);
}


BEGIN_MESSAGE_MAP(CResizeImage, CDialog)
	ON_BN_CLICKED(IDC_RADIO1, &CResizeImage::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CResizeImage::OnBnClickedRadio2)
	ON_WM_CREATE()
	ON_EN_CHANGE(IDC_EDIT1, &CResizeImage::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &CResizeImage::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, &CResizeImage::OnEnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT4, &CResizeImage::OnEnChangeEdit4)
END_MESSAGE_MAP()


// CResizeImage 消息处理程序

void CResizeImage::OnBnClickedRadio1()
{
	UpdateData(true);
	CRegistrationApp* app=(CRegistrationApp*)AfxGetApp();
	m_width=app->image1Width;
	m_height=app->image1Height;
	m_oriWidth=app->image1Width;
	m_oriHeight=app->image1Height;
	m_heightper=100;
	m_widthper=100;
	m_maintainratio=true;
	m_ratio=m_width*1.0/m_height;
	UpdateData(false);
}

void CResizeImage::OnBnClickedRadio2()
{
	UpdateData(true);
	CRegistrationApp* app=(CRegistrationApp*)AfxGetApp();
	m_width=app->image2Width;
	m_height=app->image2Height;
	m_oriWidth=app->image2Width;
	m_oriHeight=app->image2Height;
	m_heightper=100;
	m_widthper=100;
	m_maintainratio=true;
	m_ratio=m_width*1.0/m_height;
	UpdateData(false);
}

int CResizeImage::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRegistrationApp* app=(CRegistrationApp*)AfxGetApp();
 	m_width=app->image1Width;
 	m_height=app->image1Height;
	m_oriWidth=app->image1Width;
	m_oriHeight=app->image1Height;
	m_heightper=100;
	m_widthper=100;
	m_maintainratio=true;
	m_ratio=m_width*1.0/m_height;
	m_interMethod="cubic";
	return 0;
}

void CResizeImage::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	UpdateData(true);
	m_widthper=m_width*100.0/m_oriWidth;
	if(m_maintainratio)
	{
		m_height=m_width*m_oriHeight/m_oriWidth;
		m_heightper=m_widthper;
	}
	UpdateData(false);
}

void CResizeImage::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	UpdateData(true);
	m_width=m_widthper/100*m_oriWidth;
	if(m_maintainratio)
	{
		m_height=m_width*m_oriHeight/m_oriWidth;
		m_heightper=m_widthper;
	}
	UpdateData(false);
}

void CResizeImage::OnEnChangeEdit3()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	UpdateData(true);
	m_heightper=m_height*100.0/m_oriHeight;
	if(m_maintainratio)
	{
		m_width=m_height*m_oriWidth/m_oriHeight;
		m_widthper=m_heightper;
	}
	UpdateData(false);
}

void CResizeImage::OnEnChangeEdit4()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	UpdateData(true);
	m_height=m_heightper/100*m_oriHeight;
	if(m_maintainratio)
	{
		m_width=m_height*m_oriWidth/m_oriHeight;
		m_widthper=m_heightper;
	}
	UpdateData(false);
}
