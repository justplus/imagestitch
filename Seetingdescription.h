#pragma once


// CSeetingdescription �Ի���

class CSeetingdescription : public CDialog
{
	DECLARE_DYNAMIC(CSeetingdescription)

public:
	CSeetingdescription(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSeetingdescription();

// �Ի�������
	enum { IDD = IDD_SETTINGDESCRIPTION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_desp;
};
