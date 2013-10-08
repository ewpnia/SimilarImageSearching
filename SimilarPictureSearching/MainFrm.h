
// MainFrm.h : CMainFrame 类的接口
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

// 特性
public:

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CMFCRibbonBar     m_wndRibbonBar;
	CMFCRibbonApplicationButton m_MainButton;
	CMFCToolBarImages m_PanelImages;
	CMFCRibbonStatusBar  m_wndStatusBar;
	COutputWnd        m_wndOutput;                   //下方栏
	CPropertiesWnd    m_wndProperties;               //右侧属性栏
	COutlookBar       m_wndNavigationBar;            //左侧文件目录
	CMFCShellTreeCtrl m_wndTree;                     //文件树形浏览
	CCalendarBar      m_wndCalendar;                 //日历栏
	CMFCCaptionBar    m_wndCaptionBar;

// 生成的消息映射函数
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


