// Registration.h : Registration Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CRegistrationApp:
// �йش����ʵ�֣������ Registration.cpp
//

class CRegistrationApp : public CWinApp
{
public:
	CRegistrationApp();
	double image1Width;
	double image1Height;
	double image2Width;
	double image2Height;

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CRegistrationApp theApp;