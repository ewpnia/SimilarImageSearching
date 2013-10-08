
// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "SimilarPictureSearching.h"
#include "MainFrm.h"
#include "AddSheet.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND(ID_WINDOW_MANAGER, &CMainFrame::OnWindowManager)
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnUpdateApplicationLook)
	ON_COMMAND(ID_VIEW_CAPTION_BAR, &CMainFrame::OnViewCaptionBar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_CAPTION_BAR, &CMainFrame::OnUpdateViewCaptionBar)
	ON_COMMAND(ID_TOOLS_OPTIONS, &CMainFrame::OnOptions)
	ON_WM_SETTINGCHANGE()

	ON_COMMAND(ID_SiftFeatures, &CMainFrame::OnSiftfeatures)
	ON_COMMAND(ID_SPSsift, &CMainFrame::OnSpssift)
	ON_COMMAND(ID_SPSsurf, &CMainFrame::OnSpssurf)
	ON_COMMAND(ID_SearchingSelect, &CMainFrame::OnSearchingselect)

	ON_COMMAND(ID_ShowPIC, &CMainFrame::OnShowpic)

	ON_COMMAND(ID_SURFCHECK, &CMainFrame::OnSurfcheck)
	ON_UPDATE_COMMAND_UI(ID_SURFCHECK, &CMainFrame::OnUpdateSURFPopUp)

	ON_COMMAND(ID_SIFTCHECK, &CMainFrame::OnSiftcheck)
	ON_UPDATE_COMMAND_UI(ID_SIFTCHECK, &CMainFrame::OnUpdateSiftcheck)
	
	ON_COMMAND(ID_SIFTCHECK2, &CMainFrame::SIFTPopUp)
	ON_UPDATE_COMMAND_UI(ID_SIFTCHECK2, &CMainFrame::OnUpdateSIFTPopUp)

	ON_COMMAND(IDC_NumRange, &CMainFrame::OnNumrange)
END_MESSAGE_MAP()

// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_OFF_2007_BLUE);
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;
	// ���ڳ־�ֵ�����Ӿ�����������ʽ
	OnApplicationLook(theApp.m_nAppLook);

	CMDITabInfo mdiTabParams;
	mdiTabParams.m_style = CMFCTabCtrl::STYLE_3D_ONENOTE; // ����������ʽ...
	mdiTabParams.m_bActiveTabCloseButton = TRUE;      // ����Ϊ FALSE �Ὣ�رհ�ť������ѡ�������Ҳ�
	mdiTabParams.m_bTabIcons = FALSE;    // ����Ϊ TRUE ���� MDI ѡ��������ĵ�ͼ��
	mdiTabParams.m_bAutoColor = TRUE;    // ����Ϊ FALSE ������ MDI ѡ����Զ���ɫ
	mdiTabParams.m_bDocumentMenu = TRUE; // ��ѡ�������ұ�Ե�����ĵ��˵�
	EnableMDITabbedGroups(TRUE, mdiTabParams);

	m_wndRibbonBar.Create(this);
	m_wndRibbonBar.LoadFromResource(IDR_RIBBON);

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
	}
	
	
	//�ײ�����1��2��ֵ�޸���String Table��
	CString strTitlePane1;
	CString strTitlePane2;
	bNameValid = strTitlePane1.LoadString(IDS_STATUS_PANE1);
	ASSERT(bNameValid);
	bNameValid = strTitlePane2.LoadString(IDS_STATUS_PANE2);
	ASSERT(bNameValid);
	m_wndStatusBar.AddElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE1, strTitlePane1, TRUE), strTitlePane1);
	m_wndStatusBar.AddExtendedElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE2, strTitlePane2, TRUE), strTitlePane2);

	// ���� Visual Studio 2005 ��ʽͣ��������Ϊ
	CDockingManager::SetDockingMode(DT_SMART);
	// ���� Visual Studio 2005 ��ʽͣ�������Զ�������Ϊ
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// �������񽫴�������࣬��˽���ʱ��������ͣ��:
	EnableDocking(CBRS_ALIGN_TOP | CBRS_ALIGN_BOTTOM | CBRS_ALIGN_RIGHT);

	// ���������á�Outlook��������:
	if (!CreateOutlookBar(m_wndNavigationBar, ID_VIEW_NAVIGATION, m_wndTree, m_wndCalendar, 250))
	{
		TRACE0("δ�ܴ�����������\n");
		return -1;      // δ�ܴ���
	}

	// ����������:
	if (!CreateCaptionBar())
	{
		TRACE0("δ�ܴ���������\n");
		return -1;      // δ�ܴ���
	}

	// �Ѵ��� Outlook ����Ӧ���������ͣ����
	EnableDocking(CBRS_ALIGN_LEFT);
	EnableAutoHidePanes(CBRS_ALIGN_RIGHT);

	// ����ͣ������
	if (!CreateDockingWindows())
	{
		TRACE0("δ�ܴ���ͣ������\n");
		return -1;
	}

	m_wndOutput.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndOutput);
	m_wndProperties.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndProperties);


	// ������ǿ�Ĵ��ڹ���Ի���
	EnableWindowsDialog(ID_WINDOW_MANAGER, ID_WINDOW_MANAGER, TRUE);

	// ���ĵ�����Ӧ�ó��������ڴ��ڱ������ϵ�˳����н�������
	// ���Ľ��������Ŀ����ԣ���Ϊ��ʾ���ĵ�����������ͼ��
	ModifyStyle(0, FWS_PREFIXTITLE);

	m_bCheck1 = FALSE;
	m_bCheck2 = FALSE;
	SIFTDrawFeatures = FALSE;
	SIFTPU = FALSE;
	SURFPU = FALSE;
	m_bCheck3 = FALSE;
	EditNumber = 10;

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return TRUE;
}

BOOL CMainFrame::CreateDockingWindows()
{
	BOOL bNameValid;
	// �����������
	CString strOutputWnd;
	bNameValid = strOutputWnd.LoadString(IDS_OUTPUT_WND);
	ASSERT(bNameValid);
	if (!m_wndOutput.Create(strOutputWnd, this, CRect(0, 0, 100, 100), TRUE, ID_VIEW_OUTPUTWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI))
	{
		TRACE0("δ�ܴ����������\n");
		return FALSE; // δ�ܴ���
	}

	// �������Դ���
	CString strPropertiesWnd;
	bNameValid = strPropertiesWnd.LoadString(IDS_PROPERTIES_WND);
	ASSERT(bNameValid);
	if (!m_wndProperties.Create(strPropertiesWnd, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_PROPERTIESWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
	{
		TRACE0("δ�ܴ��������ԡ�����\n");
		return FALSE; // δ�ܴ���
	}

	SetDockingWindowIcons(theApp.m_bHiColorIcons);
	return TRUE;
}

void CMainFrame::SetDockingWindowIcons(BOOL bHiColorIcons)
{
	HICON hOutputBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_OUTPUT_WND_HC : IDI_OUTPUT_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndOutput.SetIcon(hOutputBarIcon, FALSE);

	HICON hPropertiesBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_PROPERTIES_WND_HC : IDI_PROPERTIES_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndProperties.SetIcon(hPropertiesBarIcon, FALSE);

	UpdateMDITabbedBarsIcons();
}

BOOL CMainFrame::CreateOutlookBar(CMFCOutlookBar& bar, UINT uiID, CMFCShellTreeCtrl& tree, CCalendarBar& calendar, int nInitialWidth)
{
	bar.SetMode2003();

	BOOL bNameValid;
	CString strTemp;
	bNameValid = strTemp.LoadString(IDS_SHORTCUTS);
	ASSERT(bNameValid);
	if (!bar.Create(strTemp, this, CRect(0, 0, nInitialWidth, 32000), uiID, WS_CHILD | WS_VISIBLE | CBRS_LEFT))
	{
		return FALSE; // δ�ܴ���
	}

	CMFCOutlookBarTabCtrl* pOutlookBar = (CMFCOutlookBarTabCtrl*)bar.GetUnderlyingWindow();

	if (pOutlookBar == NULL)
	{
		ASSERT(FALSE);
		return FALSE;
	}

	pOutlookBar->EnableInPlaceEdit(TRUE);

	static UINT uiPageID = 1;

	// �ɸ��������Զ����أ��ɵ�����С�������ܹر�
	DWORD dwStyle = AFX_CBRS_FLOAT | AFX_CBRS_AUTOHIDE | AFX_CBRS_RESIZE;

	CRect rectDummy(0, 0, 0, 0);
	const DWORD dwTreeStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS;

	tree.Create(dwTreeStyle, rectDummy, &bar, 1200);
	bNameValid = strTemp.LoadString(IDS_FOLDERS);
	ASSERT(bNameValid);
	pOutlookBar->AddControl(&tree, strTemp, 2, TRUE, dwStyle);
	
	calendar.Create(rectDummy, &bar, 1201);
	bNameValid = strTemp.LoadString(IDS_CALENDAR);
	ASSERT(bNameValid);
	pOutlookBar->AddControl(&calendar, strTemp, 3, TRUE, dwStyle);

	bar.SetPaneStyle(bar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	pOutlookBar->SetImageList(theApp.m_bHiColorIcons ? IDB_PAGES_HC : IDB_PAGES, 24);
	pOutlookBar->SetToolbarImageList(theApp.m_bHiColorIcons ? IDB_PAGES_SMALL_HC : IDB_PAGES_SMALL, 16);
	pOutlookBar->RecalcLayout();

	BOOL bAnimation = theApp.GetInt(_T("OutlookAnimation"), TRUE);
	CMFCOutlookBarTabCtrl::EnableAnimation(bAnimation);

	bar.SetButtonsFont(&afxGlobalData.fontBold);

	return TRUE;
}

BOOL CMainFrame::CreateCaptionBar()
{
	if (!m_wndCaptionBar.Create(WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS, this, ID_VIEW_CAPTION_BAR, -1, TRUE))
	{
		TRACE0("δ�ܴ���������\n");
		return FALSE;
	}

	BOOL bNameValid;

	CString strTemp, strTemp2;
	bNameValid = strTemp.LoadString(IDS_CAPTION_BUTTON);
	ASSERT(bNameValid);
	m_wndCaptionBar.SetButton(strTemp, ID_TOOLS_OPTIONS, CMFCCaptionBar::ALIGN_LEFT, FALSE);
	bNameValid = strTemp.LoadString(IDS_CAPTION_BUTTON_TIP);
	ASSERT(bNameValid);
	m_wndCaptionBar.SetButtonToolTip(strTemp);

	bNameValid = strTemp.LoadString(IDS_CAPTION_TEXT);
	ASSERT(bNameValid);
	m_wndCaptionBar.SetText(strTemp, CMFCCaptionBar::ALIGN_LEFT);

	m_wndCaptionBar.SetBitmap(IDB_INFO, RGB(255, 255, 255), FALSE, CMFCCaptionBar::ALIGN_LEFT);
	bNameValid = strTemp.LoadString(IDS_CAPTION_IMAGE_TIP);
	ASSERT(bNameValid);
	bNameValid = strTemp2.LoadString(IDS_CAPTION_IMAGE_TEXT);
	ASSERT(bNameValid);
	m_wndCaptionBar.SetImageToolTip(strTemp, strTemp2);

	return TRUE;
}

// CMainFrame ���

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame ��Ϣ�������

void CMainFrame::OnWindowManager()
{
	ShowWindowsDialog();
}

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_VS_2008:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2008));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_WINDOWS_7:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(TRUE);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
	}

	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);
}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}

void CMainFrame::OnViewCaptionBar()
{
	m_wndCaptionBar.ShowWindow(m_wndCaptionBar.IsVisible() ? SW_HIDE : SW_SHOW);
	RecalcLayout(FALSE);
}

void CMainFrame::OnUpdateViewCaptionBar(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_wndCaptionBar.IsVisible());
}

void CMainFrame::OnOptions()
{
	CMFCRibbonCustomizeDialog *pOptionsDlg = new CMFCRibbonCustomizeDialog(this, &m_wndRibbonBar);
	ASSERT(pOptionsDlg != NULL);

	pOptionsDlg->DoModal();
	delete pOptionsDlg;
}

void CMainFrame::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CMDIFrameWndEx::OnSettingChange(uFlags, lpszSection);
	m_wndOutput.UpdateFonts();
}




/***********************************************************************************/
/**************************SIFT     ���********************************************/
/**********************************************************************************/
void CMainFrame::OnSpssift()
{
	if ( SAselected <= 0 )
	{
		//MessageBox(_T("δѡ��ƥ���㷨��ʹ��KD-Tree����"));
		SAselected = 1;
	}
	else if ( SAselected == 0 )
	{
		MessageBox(_T("ŷ�Ͼ���"));
	}
	else if ( SAselected == 1 )
	{
		//MessageBox(_T("KD-Tree"));

	}
	else if ( SAselected == 2 )
	{
		MessageBox(_T("K-means"));
	}

	OnSiftfeatures();
}


void CMainFrame::OnSiftfeatures()
{
	SiftDialog  Dlg;
	m_wndTree.GetItemPath(Dlg.m_pathOpen);
	Dlg.ini.openDir = Dlg.m_pathOpen;
	Dlg.ini.SAselected = SAselected;

	if (SIFTDrawFeatures == TRUE)
	{
		Dlg.ini.drawFeatures = TRUE;
	}
	else
		Dlg.ini.drawFeatures = FALSE;
	
	if (SIFTPU == TRUE)
	{
		Dlg.ini.IsPopUp = 1;
	}
	else
		Dlg.ini.IsPopUp = 0;

	Dlg.ini.SIFTEditNum = EditNumber;

	Dlg.DoModal();

	if ( !Dlg.ini.MatchPictureList.empty() )
	{
		CString AlgName = _T("���μ���ʹ�� SIFT ����");
		int SimilarImageSum = Dlg.ini.MatchPictureList.size();
		ShowMatchResult( Dlg.ini.sourcePicture, Dlg.ini.MatchPictureList, Dlg.ini.PastTime, AlgName, Dlg.ini.ImageSum, SimilarImageSum );
	}
	else if( Dlg.ini.NoMatch == 1 )
	{
		CString str1 = _T("δ�ҵ�����ͼ��");
		CString str2 = _T("");
		m_wndOutput.MyOutput(str1);
		m_wndOutput.MyOutput(str2);
	}
}


void CMainFrame::OnSiftcheck()
{
	m_bCheck1 = !m_bCheck1;
	SIFTDrawFeatures = !SIFTDrawFeatures;
}


void CMainFrame::OnUpdateSiftcheck(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_bCheck1);
}


void CMainFrame::SIFTPopUp()
{
	m_bCheck2 = !m_bCheck2;
	SIFTPU = !SIFTPU;
}

void CMainFrame::OnUpdateSIFTPopUp(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_bCheck2);
}



/***********************************************************************************/
/**************************SURF     ���********************************************/
/**********************************************************************************/

void CMainFrame::OnSpssurf()
{
	// �������Ա����   
	CAddSheet sheet(_T("")); 

	// �������ԶԻ���Ϊ�򵼶Ի���
	sheet.SetWizardMode();
	
	// ��ģ̬Y�򵼶Ի���   
	sheet.DoModal(); 

	sheet.StartSurf( SURFPU, EditNumber );
	
	if ( !sheet.ini.MatchPictureList.empty() )
	{
		CString AlgName = _T("���μ���ʹ�� SURF ����");
		int SimilarImageSum = sheet.ini.MatchPictureList.size();
		ShowMatchResult( sheet.ini.sourcePicture, sheet.ini.MatchPictureList, sheet.ini.PastTime, AlgName, sheet.ini.ImageSum, SimilarImageSum );
	}
	else if( sheet.ini.NoMatch == 1 )
	{
		CString str1 = _T("δ�ҵ�����ͼ��");
		CString str2 = _T("");
		m_wndOutput.MyOutput(str1);
		m_wndOutput.MyOutput(str2);
	}
}


void CMainFrame::OnSurfcheck()
{
	m_bCheck3 = !m_bCheck3;
	SURFPU = !SURFPU;
}

void CMainFrame::OnUpdateSURFPopUp(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_bCheck3);
}




/***********************************************************************************/
/**************************��         ��********************************************/
/**********************************************************************************/

void CMainFrame::OnSearchingselect()
{
	//SAselected = 0;

	 // ��ȡCombo Box�ؼ���ָ��  
	CMFCRibbonComboBox* pComboBox = 
		DYNAMIC_DOWNCAST(CMFCRibbonComboBox, m_wndRibbonBar.FindByID(ID_SearchingSelect)); 

	// ��ȡCombo Box�ؼ���ǰѡ���������   
	SAselected = pComboBox->GetCurSel();  

	/*
	if (SAselected >= 0)   
	{   
		// ����������ڵ���0����˵����ѡ��������Ի�����ʾѡ�������Ϣ   
		MessageBox(pComboBox->GetItem(SAselected));   
	}   
	else  
	{   
		// �������С��0����˵��û��ѡ��������Ի�����ʾ�û�����ѡ��   
		MessageBox(_T("��ѡ��һ��ƥ���㷨��"));   
	}*/

	/*
	if (SAselected == 0)   
	{   
		//ŷ�Ͼ���
		//MessageBox(pComboBox->GetItem(SAselected));  
		MessageBox(_T("ŷ�Ͼ���"));
	}   
	else if (SAselected == 1)   
	{   
		//KD-Tree
		//MessageBox(pComboBox->GetItem(SAselected));  
		MessageBox(_T("KD-Tree"));
	}  
	else if (SAselected == 2)   
	{   
		//K-means
		//MessageBox(pComboBox->GetItem(SAselected));  
		MessageBox(_T("K-means"));
	}  
	else  
	{   
		// �������С��0����˵��û��ѡ��������Ի�����ʾ�û�����ѡ��   
		MessageBox(_T("��ѡ��һ��ƥ���㷨��"));   
	}
	*/
}

void CMainFrame::OnShowpic()
{
	
}

void CMainFrame::ShowMatchResult( CString sourcePicture, std::vector<CString> MatchPictureList, 
								  int PastTime, CString AlgName,int ImageSum,int SimilarImageSum)
{
	/*
	CString pathOpen;
	m_wndTree.GetItemPath(pathOpen);
	m_wndOutput.MyOutput(pathOpen);
	*/
	m_wndOutput.UpdateWindow();
	m_wndOutput.Invalidate(TRUE);

	CString str1 = _T("Դ�ļ���");
	CString str2 = _T("");
	CString str3 = _T("����ͼ��");
	CString str4 = _T("��ʱ��");
	CString str5 = _T("�������� ");
	CString str6 = _T("�������� ");
	CString str7 = _T("***********************************************************");

	CString imageSum;
	imageSum.Format(L"%d", ImageSum);
	imageSum.Append(L" ��ͼ��");
	str5.Append(imageSum.GetBuffer());

	CString similarImageSum;
	similarImageSum.Format(L"%d", SimilarImageSum);
	similarImageSum.Append(L" ������ͼ��");
	str6.Append(similarImageSum.GetBuffer());

	CString pastTime;
	pastTime.Format(L"%d", PastTime);
	pastTime.Append(L" ms");

	m_wndOutput.MyOutput(AlgName);
	m_wndOutput.MyOutput(str5);
	m_wndOutput.MyOutput(str6);
	m_wndOutput.MyOutput(str2);
	m_wndOutput.MyOutput(str1);
	m_wndOutput.MyOutput(sourcePicture);
	m_wndOutput.MyOutput(str2);
	m_wndOutput.MyOutput(str3);
	while (!MatchPictureList.empty())
	{
		m_wndOutput.MyOutput(MatchPictureList.back());
		MatchPictureList.pop_back();
	}
	m_wndOutput.MyOutput(str2);
	m_wndOutput.MyOutput(str4);
	m_wndOutput.MyOutput(pastTime);
	m_wndOutput.MyOutput(str2);
	m_wndOutput.MyOutput(str7);
	m_wndOutput.MyOutput(str2);

	MatchPictureList.clear();
}


void CMainFrame::OnNumrange()
{
	CString EditNum ;
	CMFCRibbonEdit* pEdit =
		DYNAMIC_DOWNCAST(CMFCRibbonEdit, m_wndRibbonBar.FindByID(IDC_NumRange)); 

	EditNum = pEdit->GetEditText();
	//MessageBox(EditNum);

	int EditN = 10;
	EditN = _ttoi(EditNum);

	if ( EditN > 200 || EditN < 10 )
	{
		MessageBox(_T( "��ֵ���볬����Χ����ʹ��10-200���������") );
	}
	else
		EditNumber = EditN;
}
