#pragma once
#include "resource.h"
#include "ini.h"


// SiftDialog 对话框

class SiftDialog : public CDialogEx
{
	DECLARE_DYNAMIC(SiftDialog)

public:
	SiftDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~SiftDialog();

// 对话框数据
	enum { IDD = IDD_SiftDialog };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:

	CIni ini;
	CString m_pathOpen;
	CString m_pathSave;
	CString m_pathSource;

	int m_progessMax;
	int m_progessStep;

	virtual BOOL OnInitDialog(void);

	CProgressCtrl m_pro;

	afx_msg void OnEnChangeOnenchangepathtarget();
	afx_msg void OnEnChangeOnenchangepathsave();
	afx_msg void OnBnClickedOk();

};




