#pragma once


// CSetting 对话框

class CSetting : public CDialog
{
	DECLARE_DYNAMIC(CSetting)

public:
	CSetting(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSetting();

// 对话框数据
	enum { IDD = IDD_SETTING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int cornerCount;
	int patch_radius;
	int max_disparity;
	double epidis;
	double threshold;
	BOOL initmatch;
	BOOL guidematch;
	BOOL histmatch;
	double m_rematchthreshold;
	int m_matchType;
};
