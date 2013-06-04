#pragma once


// COpenImage 对话框

class COpenImage : public CDialog
{
	DECLARE_DYNAMIC(COpenImage)

public:
	COpenImage(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~COpenImage();
public:
	CString imagePath1;
	CString imagePath2;
// 对话框数据
	enum { IDD = IDD_IMAGEOPEN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
