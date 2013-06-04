#pragma once


// CSetting �Ի���

class CSetting : public CDialog
{
	DECLARE_DYNAMIC(CSetting)

public:
	CSetting(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSetting();

// �Ի�������
	enum { IDD = IDD_SETTING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
