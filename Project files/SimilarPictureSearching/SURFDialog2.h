#pragma once
#include "ini.h"

// SURFDialog2 �Ի���

class SURFDialog2 : public CPropertyPage
{
	DECLARE_DYNAMIC(SURFDialog2)

public:
	SURFDialog2();
	virtual ~SURFDialog2();

// �Ի�������
	enum { IDD = IDD_SURFDIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_pathSource;
	afx_msg void OnEnChangeSurfeditbrowse1();
	virtual BOOL OnSetActive();
};
