// RotateImage.cpp : 实现文件
//

#include "stdafx.h"
#include "Registration.h"
#include "RotateImage.h"


// CRotateImage 对话框

IMPLEMENT_DYNAMIC(CRotateImage, CDialog)

CRotateImage::CRotateImage(CWnd* pParent /*=NULL*/)
	: CDialog(CRotateImage::IDD, pParent)
	, m_angle(0)
	, m_imageNo(0)
	, m_direction(0)
	, m_specifyangle(0)
{
}

CRotateImage::~CRotateImage()
{
}

void CRotateImage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_angle);
	DDX_Radio(pDX, IDC_RADIO7, m_imageNo);
	DDX_Radio(pDX, IDC_RADIO1, m_direction);
	DDX_Radio(pDX, IDC_RADIO3, m_specifyangle);
}


BEGIN_MESSAGE_MAP(CRotateImage, CDialog)

END_MESSAGE_MAP()


// CRotateImage 消息处理程序

