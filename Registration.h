// Registration.h : Registration 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号


// CRegistrationApp:
// 有关此类的实现，请参阅 Registration.cpp
//

class CRegistrationApp : public CWinApp
{
public:
	CRegistrationApp();
	double image1Width;
	double image1Height;
	double image2Width;
	double image2Height;

// 重写
public:
	virtual BOOL InitInstance();

// 实现
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CRegistrationApp theApp;