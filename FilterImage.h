#pragma once


// CFilterImage �Ի���

class CFilterImage : public CDialog
{
	DECLARE_DYNAMIC(CFilterImage)

public:
	CFilterImage(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFilterImage();

// �Ի�������
	enum { IDD = IDD_FILTERIMAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int m_imageNo;
	CString m_smoothMethod;
	int m_filterSize;
	double m_sigma;
};
