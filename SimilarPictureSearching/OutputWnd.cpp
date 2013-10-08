//�·���Ϣ��
//

#include "stdafx.h"

#include "OutputWnd.h"
#include "Resource.h"
#include "MainFrm.h"
#include "minmax.h"

#include <highgui.h>

#include "SiftDialog.h"
#include "MainFrm.h"
#include "SimilarPictureSearching.h"
#include "SimilarPictureSearchingDoc.h"
#include "SimilarPictureSearchingView.h"
#include "ChildFrm.h"

#include "MyFunctions.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MYMAX(a,b)            (((a) > (b)) ? (a) : (b))

/////////////////////////////////////////////////////////////////////////////
// COutputBar

COutputWnd::COutputWnd()
{
}

COutputWnd::~COutputWnd()
{
}

BEGIN_MESSAGE_MAP(COutputWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	
END_MESSAGE_MAP()

int COutputWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// ����ѡ�����:
	if (!m_wndTabs.Create(CMFCTabCtrl::STYLE_FLAT, rectDummy, this, 1))
	{
		TRACE0("δ�ܴ������ѡ�����\n");
		return -1;      // δ�ܴ���
	}

	// �����������:
	const DWORD dwStyle = LBS_NOINTEGRALHEIGHT | WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL ;
	/*
	if (!m_wndOutputThumbNails.Create(dwStyle, rectDummy, &m_wndTabs, 2) ||
		!m_wndOutputBuild.Create(dwStyle, rectDummy, &m_wndTabs, 3) ||
		!m_wndOutputDebug.Create(dwStyle, rectDummy, &m_wndTabs, 4) ||
		!m_wndOutputFind.Create(dwStyle, rectDummy, &m_wndTabs, 5) )
		*/
	if ( !m_wndOutputThumbNails.Create(dwStyle, rectDummy, &m_wndTabs, 2) )
	{
		TRACE0("δ�ܴ����������\n");
		return -1;      // δ�ܴ���
	}
	
	UpdateFonts();

	CString strTabName;
	BOOL bNameValid;

	// ���б��ڸ��ӵ�ѡ�:
	bNameValid = strTabName.LoadString(IDS_PIC_TAB);
	ASSERT(bNameValid);
	m_wndTabs.AddTab(&m_wndOutputThumbNails, strTabName, (UINT)0);
	/*
	bNameValid = strTabName.LoadString(IDS_BUILD_TAB);
	ASSERT(bNameValid);
	m_wndTabs.AddTab(&m_wndOutputBuild, strTabName, (UINT)1);

	bNameValid = strTabName.LoadString(IDS_DEBUG_TAB);
	ASSERT(bNameValid);
	m_wndTabs.AddTab(&m_wndOutputDebug, strTabName, (UINT)2);

	bNameValid = strTabName.LoadString(IDS_FIND_TAB);
	ASSERT(bNameValid);
	m_wndTabs.AddTab(&m_wndOutputFind, strTabName, (UINT)3);
	*/

	// ʹ��һЩ�����ı���д���ѡ�(���踴������)
	//FillBuildWindow();
	//FillDebugWindow();
	//FillFindWindow();

	return 0;
}

void COutputWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	// ѡ��ؼ�Ӧ��������������:
	m_wndTabs.SetWindowPos (NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);

}

void COutputWnd::AdjustHorzScroll(CListBox& wndListBox)
{
	CClientDC dc(this);
	CFont* pOldFont = dc.SelectObject(&afxGlobalData.fontRegular);
	
	int cxExtentMax = 0;

	for (int i = 0; i < wndListBox.GetCount(); i ++)
	{
		CString strItem;
		wndListBox.GetText(i, strItem);

		//cxExtentMax = max(cxExtentMax, dc.GetTextExtent(strItem).cx);
		cxExtentMax = MYMAX(cxExtentMax, dc.GetTextExtent(strItem).cx);
	}

	wndListBox.SetHorizontalExtent(cxExtentMax);
	dc.SelectObject(pOldFont);
}

/*
void COutputWnd::FillBuildWindow()
{
	//m_wndOutputBuild.AddString(PathOpen);
	//m_wndOutputBuild.OnDrawIconicThumbnailOrLivePreview();

}

void COutputWnd::FillDebugWindow()
{
	
	m_wndOutputDebug.AddString(_T("�����������ʾ�ڴ˴���"));
	m_wndOutputDebug.AddString(_T("�������ʾ���б���ͼ������"));
	m_wndOutputDebug.AddString(_T("�������Ը�����Ҫ��������ʾ��ʽ..."));
	
}

void COutputWnd::FillFindWindow()
{
	
	m_wndOutputFind.AddString(_T("�����������ʾ�ڴ˴���"));
	m_wndOutputFind.AddString(_T("�������ʾ���б���ͼ������"));
	m_wndOutputFind.AddString(_T("�������Ը�����Ҫ��������ʾ��ʽ..."));
	
}
*/

void COutputWnd::UpdateFonts()
{
	m_wndOutputThumbNails.SetFont(&afxGlobalData.fontRegular);
	//m_wndOutputBuild.SetFont(&afxGlobalData.fontRegular);
	//m_wndOutputDebug.SetFont(&afxGlobalData.fontRegular);
	//m_wndOutputFind.SetFont(&afxGlobalData.fontRegular);
}


void COutputWnd::MyOutput(CString str)
{
	m_wndOutputThumbNails.AddString(str);
	
	/*
	if (!OutputImg.IsNull())
	{
		OutputImg.Destroy();
	}

	OutputImg.Load(L"55.jpg");

	if (!OutputImg.IsNull())
	{
		OutputImg.Draw(m_wndOutputThumbNails.GetDC()->m_hDC,0,0,OutputImg.GetWidth()/3,OutputImg.GetHeight()/3);
	}*/
}




//�·����������Ҽ��˵�������
/////////////////////////////////////////////////////////////////////////////
// COutputList1

COutputList::COutputList()
{
}

COutputList::~COutputList()
{
}

BEGIN_MESSAGE_MAP(COutputList, CListBox)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CLEAR, OnEditClear)
	ON_COMMAND(ID_VIEW_OUTPUTWND, OnViewOutput)
	ON_WM_WINDOWPOSCHANGING()
	ON_COMMAND(ID_EDIT_OPEN, OpenImagePath)
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// COutputList ��Ϣ�������

void COutputList::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CMenu menu;
	menu.LoadMenu(IDR_OUTPUT_POPUP);

	CMenu* pSumMenu = menu.GetSubMenu(0);

	if (AfxGetMainWnd()->IsKindOf(RUNTIME_CLASS(CMDIFrameWndEx)))
	{
		CMFCPopupMenu* pPopupMenu = new CMFCPopupMenu;

		if (!pPopupMenu->Create(this, point.x, point.y, (HMENU)pSumMenu->m_hMenu, FALSE, TRUE))
			return;

		((CMDIFrameWndEx*)AfxGetMainWnd())->OnShowPopupMenu(pPopupMenu);
		UpdateDialogControls(this, FALSE);
	}

	SetFocus();
}

void COutputList::OnEditCopy()
{
	MessageBox(_T("�������"));
}

void COutputList::OnEditClear()
{
	//MessageBox(_T("������"));
	ResetContent();
}

void COutputList::OnViewOutput()
{
	CDockablePane* pParentBar = DYNAMIC_DOWNCAST(CDockablePane, GetOwner());
	CMDIFrameWndEx* pMainFrame = DYNAMIC_DOWNCAST(CMDIFrameWndEx, GetTopLevelFrame());

	if (pMainFrame != NULL && pParentBar != NULL)
	{
		pMainFrame->SetFocus();
		pMainFrame->ShowPane(pParentBar, FALSE, FALSE, FALSE);
		pMainFrame->RecalcLayout();

	}
}


void COutputList::OpenImagePath()
{
	int m = GetCurSel();
	if (m != -1)
	{
		GetText( m,ImageOpenPath );
	}
	/*
	if ( !ImageOpenPath.IsEmpty() )
	{
		//MessageBox(ImageOpenPath);
		IplImage* img;
		img = cvLoadImage( CStringToCharArray(ImageOpenPath), 1);
		cvNamedWindow( "Image" , 1 );
		cvShowImage("Image" ,img);
		cvWaitKey( 0 );
		cvDestroyWindow("Image");
	}
	*/

	if ( !ImageOpenPath.IsEmpty() )
	{
		CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
		CChildFrame* pChildFrame = (CChildFrame*)pMainFrame->GetActiveFrame();
		CSimilarPictureSearchingView* pView = (CSimilarPictureSearchingView*)pChildFrame->GetActiveView();
		//HWND hwnd = pview->GetSafeHwnd();

		if(pView==NULL)
		{
			AfxMessageBox(L"�޷��򿪣�");
			return ;
		}
		pView->PostMessageW(WM_CONTROLPRINT,(WPARAM)&ImageOpenPath,0);
	}
}
