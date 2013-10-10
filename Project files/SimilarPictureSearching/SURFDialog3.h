#pragma once
#include "ini.h"

// SURFDialog3 对话框

class SURFDialog3 : public CPropertyPage
{
	DECLARE_DYNAMIC(SURFDialog3)

public:
	SURFDialog3();
	virtual ~SURFDialog3();

// 对话框数据
	enum { IDD = IDD_SURFDIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	CString m_pathOpen;
	afx_msg void OnEnChangeSurfeditbrowse2();
	virtual BOOL OnSetActive();
};
