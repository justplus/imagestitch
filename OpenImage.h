#pragma once


// COpenImage �Ի���

class COpenImage : public CDialog
{
	DECLARE_DYNAMIC(COpenImage)

public:
	COpenImage(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~COpenImage();
public:
	CString imagePath1;
	CString imagePath2;
// �Ի�������
	enum { IDD = IDD_IMAGEOPEN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
