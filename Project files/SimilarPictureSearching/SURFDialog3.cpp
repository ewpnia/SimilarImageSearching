// SURFDialog3.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SimilarPictureSearching.h"
#include "SURFDialog3.h"
#include "afxdialogex.h"


// SURFDialog3 �Ի���

IMPLEMENT_DYNAMIC(SURFDialog3, CPropertyPage)

SURFDialog3::SURFDialog3()
	: CPropertyPage(SURFDialog3::IDD)
{

}

SURFDialog3::~SURFDialog3()
{
}

void SURFDialog3::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SURFEDITBROWSE2, m_pathOpen);
}


BEGIN_MESSAGE_MAP(SURFDialog3, CPropertyPage)
	ON_EN_CHANGE(IDC_SURFEDITBROWSE2, &SURFDialog3::OnEnChangeSurfeditbrowse2)
END_MESSAGE_MAP()


// SURFDialog3 ��Ϣ�������


void SURFDialog3::OnEnChangeSurfeditbrowse2()
{
}


BOOL SURFDialog3::OnSetActive()
{
	// ��ø����ڣ������Ա�CPropertySheet��   
	CPropertySheet* psheet = (CPropertySheet*) GetParent();   
	// �������Ա�ֻ�С���һ������ť   
	//psheet->SetWizardButtons(PSWIZB_NEXT);  
	// �������Ա���һ��������һ������ť  
	psheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_NEXT); 

	return CPropertyPage::OnSetActive();
}
