// FilterImage.cpp : 实现文件
//

#include "stdafx.h"
#include "Registration.h"
#include "FilterImage.h"


// CFilterImage 对话框

IMPLEMENT_DYNAMIC(CFilterImage, CDialog)

CFilterImage::CFilterImage(CWnd* pParent /*=NULL*/)
	: CDialog(CFilterImage::IDD, pParent)
	, m_imageNo(0)
	, m_smoothMethod(_T("gaussian blur"))
	, m_filterSize(0)
	, m_sigma(0)
{
}

CFilterImage::~CFilterImage()
{
}

void CFilterImage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO4, m_imageNo);
	DDX_CBString(pDX, IDC_COMBO2, m_smoothMethod);
	DDX_Radio(pDX, IDC_RADIO1, m_filterSize);
	DDX_Text(pDX, IDC_EDIT1, m_sigma);
}


BEGIN_MESSAGE_MAP(CFilterImage, CDialog)
END_MESSAGE_MAP()


// CFilterImage 消息处理程序
