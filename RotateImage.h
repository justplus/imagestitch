#pragma once


// CRotateImage �Ի���

class CRotateImage : public CDialog
{
	DECLARE_DYNAMIC(CRotateImage)

public:
	CRotateImage(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRotateImage();

// �Ի�������
	enum { IDD = IDD_ROTATEIMAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	double m_angle;
	int m_imageNo;
	int m_direction;
	int m_specifyangle;
};
