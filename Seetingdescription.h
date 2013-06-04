#pragma once


// CSeetingdescription 对话框

class CSeetingdescription : public CDialog
{
	DECLARE_DYNAMIC(CSeetingdescription)

public:
	CSeetingdescription(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSeetingdescription();

// 对话框数据
	enum { IDD = IDD_SETTINGDESCRIPTION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_desp;
};
