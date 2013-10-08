
// SimilarPictureSearchingView.h : CSimilarPictureSearchingView ��Ľӿ�
//
#include "PictureEx.h" 
#pragma once


class CSimilarPictureSearchingView : public CScrollView
{
protected: // �������л�����
	CSimilarPictureSearchingView();
	DECLARE_DYNCREATE(CSimilarPictureSearchingView)

// ����
public:
	CSimilarPictureSearchingDoc* GetDocument() const;
	CPictureEx  myStatic;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // ������һ�ε���
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CSimilarPictureSearchingView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CString BmpName;    //����ͼ���ļ��ļ���
	CString extname;    //����ͼ���ļ���չ��
	CImage img;

// ���ɵ���Ϣӳ�亯��
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

#ifndef _DEBUG  // SimilarPictureSearchingView.cpp �еĵ��԰汾
inline CSimilarPictureSearchingDoc* CSimilarPictureSearchingView::GetDocument() const
   { return reinterpret_cast<CSimilarPictureSearchingDoc*>(m_pDocument); }
#endif

