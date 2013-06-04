// RegistrationDoc.h : CRegistrationDoc ��Ľӿ�
//


#pragma once
#include "ResizeImage.h"
#include "RotateImage.h"
#include "FilterImage.h"
#include "OpenImage.h"
#include "Setting.h"

#include "cv.h"
#include "highgui.h"
#include "Match.h"

class CRegistrationDoc : public CDocument
{
protected: // �������л�����
	CRegistrationDoc();
	DECLARE_DYNCREATE(CRegistrationDoc)

// ����
public:
	CResizeImage m_resizeImage;
	CRotateImage m_rotateImage;
	CFilterImage m_filterImage;
	COpenImage m_openImage;
	CSetting setDlg;

	IplImage* srcImage1;
	IplImage* srcImage2;
	IplImage* showImage1;
	IplImage* showImage2;
	bool image1Opened;
	bool image2Opened;

	bool deleteMatched;
	BOOL addMatched;

	CMatch* m_match;
	bool freematch;

	bool cornerdetected;
	bool matched;
	bool fused;
	bool rematched;
	CvMat *H;//��Ӧ����
	CvMat *F;//��������

// ����
public:
	void ShowState(CString stateinfo);
	CvMat* findHMatrix(CvSeq *seq1,CvSeq *seq2);
// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CRegistrationDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnResizeimage();
	afx_msg void OnRotateimage();
	afx_msg void OnFilterimage();
	afx_msg void OnFileOpen();
	afx_msg void OnOperateReset();
	afx_msg void OnColorGrayscal();
	afx_msg void OnColor24();
	afx_msg void OnFileSave();
	afx_msg void OnFileSaveAs();
	afx_msg void OnCorners();
	afx_msg void OnMatch();
	afx_msg void OnDelmatched();
	afx_msg void OnUpdateDelmatched(CCmdUI *pCmdUI);
	afx_msg void OnAddmatched();
	afx_msg void OnUpdateAddmatched(CCmdUI *pCmdUI);
	afx_msg void OnRegistration();
	afx_msg void OnSettingSetting();
	afx_msg void OnHelpDescription();
	afx_msg void OnRematch();
	afx_msg void OnExport2dpoints();
	afx_msg void OnHelpdocument();
	afx_msg void OnExport3dpoints();
	afx_msg void OnRematchAccuratepoints();
	afx_msg void OnRematchDensepoints();
};


