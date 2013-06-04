// Seetingdescription.cpp : 实现文件
//

#include "stdafx.h"
#include "Registration.h"
#include "Seetingdescription.h"


// CSeetingdescription 对话框

IMPLEMENT_DYNAMIC(CSeetingdescription, CDialog)

CSeetingdescription::CSeetingdescription(CWnd* pParent /*=NULL*/)
	: CDialog(CSeetingdescription::IDD, pParent)
{
	//m_desp="max cornerCount:\n      角点数目的最大值（建议默认）\n\ninit-match:基于灰度互相关性的初始匹配\n";
	m_desp.Format("%s\n%s\n\n%s\n%s\n%s\n\n%s\n%s\n\n%s\n%s\n\n%s\n%s","corner detect:特征点提取\n--------------------------------","max cornerCount\n    角点数目的最大值",
		"init-match:基于灰度互相关性的初始匹配\n--------------------------------","patch size\n    邻域块的大小,此处设置为半径",
		"max disparity\n搜索窗大小,检测到的两角点距离需要小于此值","guide-match:基于对极线约束来剔除误匹配点\n--------------------------------",
		"epidis\n    点到对极线的最小距离，超过此值算作误匹配点","angle hist-match:\n基于角度直方图约束来剔除误匹配点(仅适用于部分匹配线一致的图像)\n--------------------------------",
		"threshold\n    角度一致阈值（最佳角度阈值）","rematch:重匹配\n--------------------------------","threshold\n    单应约束后对应点欧式距离差，超过此值剔除改对匹配点");
}

CSeetingdescription::~CSeetingdescription()
{
}

void CSeetingdescription::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_RICHEDIT21, m_desp);
}


BEGIN_MESSAGE_MAP(CSeetingdescription, CDialog)
END_MESSAGE_MAP()


// CSeetingdescription 消息处理程序
