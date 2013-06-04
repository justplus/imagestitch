#pragma once


// CFilterImage 对话框

class CFilterImage : public CDialog
{
	DECLARE_DYNAMIC(CFilterImage)

public:
	CFilterImage(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFilterImage();

// 对话框数据
	enum { IDD = IDD_FILTERIMAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_imageNo;
	CString m_smoothMethod;
	int m_filterSize;
	double m_sigma;
};
