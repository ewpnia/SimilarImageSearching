// SURFDialog2.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SimilarPictureSearching.h"
#include "SURFDialog2.h"
#include "afxdialogex.h"


// SURFDialog2 �Ի���

IMPLEMENT_DYNAMIC(SURFDialog2, CPropertyPage)

SURFDialog2::SURFDialog2()
	: CPropertyPage(SURFDialog2::IDD)
{ 
}

SURFDialog2::~SURFDialog2()
{
}

void SURFDialog2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SURFEDITBROWSE1, m_pathSource);
}


BEGIN_MESSAGE_MAP(SURFDialog2, CPropertyPage)
	ON_EN_CHANGE(IDC_SURFEDITBROWSE1, &SURFDialog2::OnEnChangeSurfeditbrowse1)
END_MESSAGE_MAP()


// SURFDialog2 ��Ϣ�������


void SURFDialog2::OnEnChangeSurfeditbrowse1()
{
}

BOOL SURFDialog2::OnSetActive()
{
	// ��ø����ڣ������Ա�CPropertySheet��   
	CPropertySheet* psheet = (CPropertySheet*) GetParent();   
	// �������Ա�ֻ�С���һ������ť   
	//psheet->SetWizardButtons(PSWIZB_NEXT);  
	// �������Ա���һ��������һ������ť  
	psheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_NEXT); 

	return CPropertyPage::OnSetActive();
}
