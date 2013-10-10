
// SimilarPictureSearchingView.h : CSimilarPictureSearchingView 类的接口
//
#include "PictureEx.h" 
#pragma once


class CSimilarPictureSearchingView : public CScrollView
{
protected: // 仅从序列化创建
	CSimilarPictureSearchingView();
	DECLARE_DYNCREATE(CSimilarPictureSearchingView)

// 特性
public:
	CSimilarPictureSearchingDoc* GetDocument() const;
	CPictureEx  myStatic;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CSimilarPictureSearchingView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CString BmpName;    //保存图像文件文件名
	CString extname;    //保存图像文件扩展名
	CImage img;

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg LRESULT OnControlPrint(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	afx_msg void OnFileOpen();
};

#ifndef _DEBUG  // SimilarPictureSearchingView.cpp 中的调试版本
inline CSimilarPictureSearchingDoc* CSimilarPictureSearchingView::GetDocument() const
   { return reinterpret_cast<CSimilarPictureSearchingDoc*>(m_pDocument); }
#endif

