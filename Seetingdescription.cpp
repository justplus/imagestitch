// Seetingdescription.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Registration.h"
#include "Seetingdescription.h"


// CSeetingdescription �Ի���

IMPLEMENT_DYNAMIC(CSeetingdescription, CDialog)

CSeetingdescription::CSeetingdescription(CWnd* pParent /*=NULL*/)
	: CDialog(CSeetingdescription::IDD, pParent)
{
	//m_desp="max cornerCount:\n      �ǵ���Ŀ�����ֵ������Ĭ�ϣ�\n\ninit-match:���ڻҶȻ�����Եĳ�ʼƥ��\n";
	m_desp.Format("%s\n%s\n\n%s\n%s\n%s\n\n%s\n%s\n\n%s\n%s\n\n%s\n%s","corner detect:��������ȡ\n--------------------------------","max cornerCount\n    �ǵ���Ŀ�����ֵ",
		"init-match:���ڻҶȻ�����Եĳ�ʼƥ��\n--------------------------------","patch size\n    �����Ĵ�С,�˴�����Ϊ�뾶",
		"max disparity\n��������С,��⵽�����ǵ������ҪС�ڴ�ֵ","guide-match:���ڶԼ���Լ�����޳���ƥ���\n--------------------------------",
		"epidis\n    �㵽�Լ��ߵ���С���룬������ֵ������ƥ���","angle hist-match:\n���ڽǶ�ֱ��ͼԼ�����޳���ƥ���(�������ڲ���ƥ����һ�µ�ͼ��)\n--------------------------------",
		"threshold\n    �Ƕ�һ����ֵ����ѽǶ���ֵ��","rematch:��ƥ��\n--------------------------------","threshold\n    ��ӦԼ�����Ӧ��ŷʽ����������ֵ�޳��Ķ�ƥ���");
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


// CSeetingdescription ��Ϣ�������
