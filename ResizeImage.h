#pragma once

// CResizeImage �Ի���

class CResizeImage : public CDialog
{
	DECLARE_DYNAMIC(CResizeImage)

public:
	CResizeImage(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CResizeImage();

// �Ի�������
	enum { IDD = IDD_RESIZEIMAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int m_imageNo;
	double m_width;
	double m_widthper;
	double m_height;
	double m_heightper;
	BOOL m_maintainratio;
	double m_ratio;
	double m_oriWidth;
	double m_oriHeight;
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnEnChangeEdit4();
	CString m_interMethod;
};
