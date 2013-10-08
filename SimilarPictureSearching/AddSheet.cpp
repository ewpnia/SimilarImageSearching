// AddSheet.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SimilarPictureSearching.h"
#include "AddSheet.h"
#include "SURF.h"
#include "MyFunctions.h"

#include <time.h>


// CAddSheet

IMPLEMENT_DYNAMIC(CAddSheet, CPropertySheet)

CAddSheet::CAddSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	
	AddPage(&m_surfDialog1);
	AddPage(&m_surfDialog2);
	AddPage(&m_surfDialog3);
	AddPage(&m_surfDialog4);

	m_SPDlg = NULL;
}

CAddSheet::CAddSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	
	AddPage(&m_surfDialog1);
	AddPage(&m_surfDialog2);
	AddPage(&m_surfDialog3);
	AddPage(&m_surfDialog4);
	
	m_SPDlg = NULL;
}

CAddSheet::~CAddSheet()
{
}


BEGIN_MESSAGE_MAP(CAddSheet, CPropertySheet)
END_MESSAGE_MAP()


// CAddSheet ��Ϣ�������

void CAddSheet::StartSurf( BOOL PopUp, int MatchNum )
{ 
	if (m_surfDialog2.m_pathSource.IsEmpty() ||
		m_surfDialog3.m_pathOpen.IsEmpty() ||
		(m_surfDialog4.isFinish != 1) )
	{
		return;
	}


	ini.sourcePicture = m_surfDialog2.m_pathSource;
	ini.openDir = m_surfDialog3.m_pathOpen;

	CFileFind finder;
	CString &openDir = ini.openDir;
	CString &sourcePicture = ini.sourcePicture;
	CString fileName;

	//MessageBox(openDir);
	//MessageBox(sourcePicture);

	BOOL haveNext = finder.FindFile(openDir + "\\*.*");

	if(haveNext)
	{
		if(PathIsDirectory(sourcePicture))
		{
			MessageBox(L"Ŀ��ͼƬ·������ȷ��");
			return;
		}
		
		if(!PathIsDirectory(openDir))
		{
			MessageBox(L"����ͼƬĿ¼·������ȷ��");
			return;
		}
	}
	else
	{
		MessageBox(L"����ͼƬĿ¼��û�з���ͼƬ�ļ���");
	}

	if ( m_SPDlg == NULL )   
	{   
		// ������ģ̬�Ի���ʵ��   
		m_SPDlg = new SURFProgressDialog();   
		m_SPDlg->Create(IDD_SURFPROGRESSD, this);
	}   
	// ��ʾ��ģ̬�Ի���   
	m_SPDlg->ShowWindow(SW_SHOW); 
	m_SPDlg->RedrawWindow();

	m_SPDlg->MyProgressStepLength(openDir);
	// �����ؼ��е����ݱ��浽��Ӧ�ı���   
	//UpdateData(TRUE); 
	m_SPDlg->MyProgressStep();

	//��clock()����ʱ  ����  
	clock_t  clockBegin, clockEnd;  
	clockBegin = clock(); 

	while(haveNext) 
	{ 
		BOOL isMatch; 
		haveNext = finder.FindNextFile(); 
		if(finder.IsDirectory()) 
			continue;

		fileName = finder.GetFileName();
		CString targetPicture = openDir;
		targetPicture.Append(L"\\");
		targetPicture.Append(fileName);

		const char* sourceP = CStringToCharArray(sourcePicture);
		const char* targetP = CStringToCharArray(targetPicture);

		isMatch = DoSURF( sourceP, targetP, PopUp, MatchNum );

		
		if (isMatch)
		{
			ini.MatchPictureList.push_back(targetPicture);
			//MessageBox(targetPicture);
		}
		else
		{
			ini.NoMatch = 1;
		}

		m_SPDlg->MyProgressStep();
	}

	ini.ImageSum = ( FileCount( openDir, L".jpg" ) );

	clockEnd = clock(); 
	int intms = clockEnd - clockBegin;
	ini.PastTime = intms;
	//CString ms;
	//ms.Format(_T("%d"), intms);
	//MessageBox(ms);

	if ( m_SPDlg != NULL )   
	{   
		// ɾ����ģ̬�Ի������   
		delete m_SPDlg;   
	}   

	MessageBox(L"SURF����ͼ��ƥ������ɣ�");
}
