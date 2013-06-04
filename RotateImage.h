#pragma once


// CRotateImage 对话框

class CRotateImage : public CDialog
{
	DECLARE_DYNAMIC(CRotateImage)

public:
	CRotateImage(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRotateImage();

// 对话框数据
	enum { IDD = IDD_ROTATEIMAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	double m_angle;
	int m_imageNo;
	int m_direction;
	int m_specifyangle;
};
