// OpenImage.cpp : 实现文件
//

#include "stdafx.h"
#include "Registration.h"
#include "OpenImage.h"


// COpenImage 对话框

IMPLEMENT_DYNAMIC(COpenImage, CDialog)

COpenImage::COpenImage(CWnd* pParent /*=NULL*/)
	: CDialog(COpenImage::IDD, pParent)
{

}

COpenImage::~COpenImage()
{
}

void COpenImage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(COpenImage, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &COpenImage::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &COpenImage::OnBnClickedButton2)
END_MESSAGE_MAP()


// COpenImage 消息处理程序

void COpenImage::OnBnClickedButton1()
{
	LPCTSTR lpszFilters;
	lpszFilters=_T("Image Files(*.jpg,*.bmp,*png,*tif)|*.jpg;*.bmp;*png;*tif|All Files(*.*)|*.*||");

	CFileDialog* filedialog=new CFileDialog(true,_T("jpg"),NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,lpszFilters,NULL);
	if(filedialog->DoModal()==IDOK)
	{
		imagePath1=filedialog->GetPathName();
		GetDlgItem(IDC_EDIT1)->SetWindowText(imagePath1);
	}
	delete(filedialog);
}

void COpenImage::OnBnClickedButton2()
{
	LPCTSTR lpszFilters;
	lpszFilters=_T("Image Files(*.jpg,*.bmp,*png,*tif)|*.jpg;*.bmp;*png;*tif|All Files(*.*)|*.*||");

	CFileDialog* filedialog=new CFileDialog(true,_T("jpg"),NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,lpszFilters,NULL);
	if(filedialog->DoModal()==IDOK)
	{
		imagePath2=filedialog->GetPathName();
		GetDlgItem(IDC_EDIT2)->SetWindowText(imagePath2);
	}
	delete(filedialog);
}
