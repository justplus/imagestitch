// Setting.cpp : 实现文件
//

#include "stdafx.h"
#include "Registration.h"
#include "Setting.h"


// CSetting 对话框

IMPLEMENT_DYNAMIC(CSetting, CDialog)

CSetting::CSetting(CWnd* pParent /*=NULL*/)
	: CDialog(CSetting::IDD, pParent)
	, cornerCount(1000)
	, patch_radius(5)
	, max_disparity(100)
	, epidis(20.0)
	, threshold(7.5)
	, initmatch(TRUE)
	, guidematch(TRUE)
	, histmatch(FALSE)
	, m_rematchthreshold(1.0)
	, m_matchType(0)
{

}

CSetting::~CSetting()
{
}

void CSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, cornerCount);
	DDX_Text(pDX, IDC_EDIT2, patch_radius);
	DDX_Text(pDX, IDC_EDIT3, max_disparity);
	DDX_Text(pDX, IDC_EDIT4, epidis);
	DDX_Text(pDX, IDC_EDIT5, threshold);
	DDX_Check(pDX, IDC_CHECK1, initmatch);
	DDX_Check(pDX, IDC_CHECK2, guidematch);
	DDX_Check(pDX, IDC_CHECK3, histmatch);
	DDX_Text(pDX, IDC_EDIT6, m_rematchthreshold);
	DDX_Radio(pDX, IDC_RADIO1, m_matchType);
}


BEGIN_MESSAGE_MAP(CSetting, CDialog)
END_MESSAGE_MAP()


// CSetting 消息处理程序
