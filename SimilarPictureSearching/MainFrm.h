
// MainFrm.h : CMainFrame ��Ľӿ�
//

#pragma once
#include "OutputWnd.h"
#include "PropertiesWnd.h"
#include "CalendarBar.h"
#include "Resource.h"
#include "SiftDialog.h"

class COutlookBar : public CMFCOutlookBar
{
	virtual BOOL AllowShowOnPaneMenu() const { return TRUE; }
	virtual void GetPaneName(CString& strName) const { BOOL bNameValid = strName.LoadString(IDS_OUTLOOKBAR); ASSERT(bNameValid); if (!bNameValid) strName.Empty(); }
};

class CMainFrame : public CMDIFrameWndEx
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CMFCRibbonBar     m_wndRibbonBar;
	CMFCRibbonApplicationButton m_MainButton;
	CMFCToolBarImages m_PanelImages;
	CMFCRibbonStatusBar  m_wndStatusBar;
	COutputWnd        m_wndOutput;                   //�·���
	CPropertiesWnd    m_wndProperties;               //�Ҳ�������
	COutlookBar       m_wndNavigationBar;            //����ļ�Ŀ¼
	CMFCShellTreeCtrl m_wndTree;                     //�ļ��������
	CCalendarBar      m_wndCalendar;                 //������
	CMFCCaptionBar    m_wndCaptionBar;

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnWindowManager();
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	afx_msg void OnViewCaptionBar();
	afx_msg void OnUpdateViewCaptionBar(CCmdUI* pCmdUI);
	afx_msg void OnOptions();
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	DECLARE_MESSAGE_MAP()

	BOOL CreateDockingWindows();
	void SetDockingWindowIcons(BOOL bHiColorIcons);
	BOOL CreateOutlookBar(CMFCOutlookBar& bar, UINT uiID, CMFCShellTreeCtrl& tree, CCalendarBar& calendar, int nInitialWidth);
	BOOL CreateCaptionBar();

	int FindFocusedOutlookWnd(CMFCOutlookBarTabCtrl** ppOutlookWnd);

	CMFCOutlookBarTabCtrl* FindOutlookParent(CWnd* pWnd);
	CMFCOutlookBarTabCtrl* m_pCurrOutlookWnd;
	CMFCOutlookBarPane*    m_pCurrOutlookPage;
	

public:

	int SAselected;
	BOOL SIFTDrawFeatures;
	BOOL m_bCheck1;
	BOOL SIFTPU;
	BOOL m_bCheck2;
	BOOL SURFPU;
	BOOL m_bCheck3;
	int EditNumber;


	void ShowMatchResult(CString sourcePicture, std::vector<CString> MatchPictureList,
						 int PastTime,CString AlgName,int ImageSum,int SimilarImageSum);
	
	afx_msg void OnSiftfeatures();
	afx_msg void OnSpssift();
	afx_msg void OnSpssurf();
	afx_msg void OnSearchingselect();
	afx_msg void OnShowpic();
	afx_msg void OnSurfcheck();
	afx_msg void OnUpdateSURFPopUp(CCmdUI *pCmdUI);
	afx_msg void OnSiftcheck();
	afx_msg void OnUpdateSiftcheck(CCmdUI *pCmdUI);
	afx_msg void SIFTPopUp();
	afx_msg void OnUpdateSIFTPopUp(CCmdUI *pCmdUI);
	afx_msg void OnNumrange();
};


