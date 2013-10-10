// SimilarPictureSearchingView.cpp : CSimilarPictureSearchingView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "SimilarPictureSearching.h"
#endif

#include "SimilarPictureSearchingDoc.h"
#include "SimilarPictureSearchingView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSimilarPictureSearchingView

IMPLEMENT_DYNCREATE(CSimilarPictureSearchingView, CScrollView)

BEGIN_MESSAGE_MAP(CSimilarPictureSearchingView, CScrollView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CSimilarPictureSearchingView::OnFilePrintPreview)
	ON_COMMAND(ID_FILE_OPEN, &CSimilarPictureSearchingView::OnFileOpen)
	ON_MESSAGE(WM_CONTROLPRINT, OnControlPrint)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CSimilarPictureSearchingView ����/����

CSimilarPictureSearchingView::CSimilarPictureSearchingView()
{
	//�ڴ˴���ӹ������

}

CSimilarPictureSearchingView::~CSimilarPictureSearchingView()
{
}

BOOL CSimilarPictureSearchingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// �˴�ͨ���޸�
	// CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CScrollView::PreCreateWindow(cs);
}

// CSimilarPictureSearchingView ����

void CSimilarPictureSearchingView::OnDraw(CDC* pDC)
{
	CSimilarPictureSearchingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	if (!pDoc->img.IsNull())
	{
		pDoc->img.Draw(pDC->m_hDC,0,0);
	}

	CSize sizeTotal(myStatic.GetSize().cx,myStatic.GetSize().cy);
	SetScrollSizes(MM_TEXT,sizeTotal);    // ���ù�������Χ
	
}

void CSimilarPictureSearchingView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// �������ͼ�ĺϼƴ�С	
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);

	myStatic.Create(_T("my static"), WS_CHILD|WS_VISIBLE|SS_CENTER|SS_ICON, CRect(0,0,150,50),this,0);
	myStatic.ShowWindow(0);
}



// CSimilarPictureSearchingView ��ӡ


void CSimilarPictureSearchingView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CSimilarPictureSearchingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CSimilarPictureSearchingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CSimilarPictureSearchingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CSimilarPictureSearchingView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CSimilarPictureSearchingView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CSimilarPictureSearchingView ���

#ifdef _DEBUG
void CSimilarPictureSearchingView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CSimilarPictureSearchingView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CSimilarPictureSearchingDoc* CSimilarPictureSearchingView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSimilarPictureSearchingDoc)));
	return (CSimilarPictureSearchingDoc*)m_pDocument;
}
#endif //_DEBUG


// CSimilarPictureSearchingView ��Ϣ�������

BOOL CSimilarPictureSearchingView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: �ڴ����ר�ô����/����û���

	return CScrollView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

void CSimilarPictureSearchingView::OnFileOpen()
{
	// TODO: �ڴ���������������
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("�����ļ�(*.*)|*.*|λͼ�ļ�(*.BMP)|*.BMP|JPG�ļ�(*.JPG)|*.jpg|�����ļ�(*.GIF)|*.gif||")); 
	if (IDOK==dlg.DoModal())
	{
		BmpName.Format(_T("%s"),dlg.GetPathName());
		extname = dlg.GetFileExt(); 
		extname.MakeLower();
		if (0 == extname.Compare(_T("jpg"))||0 == extname.Compare(_T("jpeg"))||0 == extname.Compare(_T("gif"))|| 0==extname.Compare(_T("bmp")) )
		{
			//myStatic.Create(_T("my static"), WS_CHILD|WS_VISIBLE|SS_CENTER, CRect(0,0,150,50),this,0);
			/*
			if (0==extname.Compare(_T("png")))
			{
				if (!img.IsNull())
					img.Destroy();
				img.Load(BmpName);
				//myStatic.DestroyWindow();
				myStatic.ShowWindow(0);
			}
			*/
			if (myStatic.Load(BmpName))
			{
				myStatic.ShowWindow(1);
				myStatic.Draw();
			}
			Invalidate();	
		}
		else
			AfxMessageBox(_T("���ļ������ݲ�֧�֣�"));

		BmpName.Empty();
	}


}


LRESULT  CSimilarPictureSearchingView::OnControlPrint(WPARAM wParam, LPARAM lParam)
{
	//if(wParam==0 && lParam==0)
		//AfxMessageBox(L"HelloWorld!");
	CString* rmsg = (CString*)wParam;
	//MessageBox(*rmsg);
	CString mymsg = rmsg->GetBuffer();
	//MessageBox(mymsg);
	myStatic.Load(mymsg);
	myStatic.ShowWindow(1);
	myStatic.Draw();
	Invalidate();

	return 0;
}