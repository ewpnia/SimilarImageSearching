// SimilarPictureSearchingView.cpp : CSimilarPictureSearchingView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CSimilarPictureSearchingView::OnFilePrintPreview)
	ON_COMMAND(ID_FILE_OPEN, &CSimilarPictureSearchingView::OnFileOpen)
	ON_MESSAGE(WM_CONTROLPRINT, OnControlPrint)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CSimilarPictureSearchingView 构造/析构

CSimilarPictureSearchingView::CSimilarPictureSearchingView()
{
	//在此处添加构造代码

}

CSimilarPictureSearchingView::~CSimilarPictureSearchingView()
{
}

BOOL CSimilarPictureSearchingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// 此处通过修改
	// CREATESTRUCT cs 来修改窗口类或样式

	return CScrollView::PreCreateWindow(cs);
}

// CSimilarPictureSearchingView 绘制

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
	SetScrollSizes(MM_TEXT,sizeTotal);    // 设置滚动条范围
	
}

void CSimilarPictureSearchingView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// 计算此视图的合计大小	
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);

	myStatic.Create(_T("my static"), WS_CHILD|WS_VISIBLE|SS_CENTER|SS_ICON, CRect(0,0,150,50),this,0);
	myStatic.ShowWindow(0);
}



// CSimilarPictureSearchingView 打印


void CSimilarPictureSearchingView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CSimilarPictureSearchingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CSimilarPictureSearchingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CSimilarPictureSearchingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
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


// CSimilarPictureSearchingView 诊断

#ifdef _DEBUG
void CSimilarPictureSearchingView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CSimilarPictureSearchingView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CSimilarPictureSearchingDoc* CSimilarPictureSearchingView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSimilarPictureSearchingDoc)));
	return (CSimilarPictureSearchingDoc*)m_pDocument;
}
#endif //_DEBUG


// CSimilarPictureSearchingView 消息处理程序

BOOL CSimilarPictureSearchingView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: 在此添加专用代码和/或调用基类

	return CScrollView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

void CSimilarPictureSearchingView::OnFileOpen()
{
	// TODO: 在此添加命令处理程序代码
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("所有文件(*.*)|*.*|位图文件(*.BMP)|*.BMP|JPG文件(*.JPG)|*.jpg|动画文件(*.GIF)|*.gif||")); 
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
			AfxMessageBox(_T("该文件类型暂不支持！"));

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