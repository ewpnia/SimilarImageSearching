#pragma once

// CAddSheet
#include "resource.h"
#include "SURFDialog1.h"
#include "SURFDialog2.h"
#include "SURFDialog3.h"
#include "SURFDialog4.h"
#include "SURFProgressDialog.h"
#include "ini.h"

class CAddSheet : public CPropertySheet
{

	SURFDialog1    m_surfDialog1;
	SURFDialog2    m_surfDialog2;
	SURFDialog3    m_surfDialog3;
	SURFDialog4    m_surfDialog4;
	DECLARE_DYNAMIC(CAddSheet)

public:
	CAddSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CAddSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~CAddSheet();


protected:
	DECLARE_MESSAGE_MAP()

public:

	SURFProgressDialog *m_SPDlg;
	CIni ini;

	void StartSurf( BOOL PopUp, int MatchNum );

};


