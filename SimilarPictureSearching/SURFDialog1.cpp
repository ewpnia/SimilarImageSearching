// SURFDialog1.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SimilarPictureSearching.h"
#include "SURFDialog1.h"
#include "afxdialogex.h"


// SURFDialog1 �Ի���

IMPLEMENT_DYNAMIC(SURFDialog1, CPropertyPage)

SURFDialog1::SURFDialog1()
	: CPropertyPage(SURFDialog1::IDD)
{

}

SURFDialog1::~SURFDialog1()
{
}

void SURFDialog1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(SURFDialog1, CPropertyPage)
END_MESSAGE_MAP()


// SURFDialog1 ��Ϣ�������

BOOL SURFDialog1::OnSetActive()
{
	// ��ø����ڣ������Ա�CPropertySheet��   
	CPropertySheet* psheet = (CPropertySheet*) GetParent();   
	// �������Ա�ֻ�С���һ������ť   
	//psheet->SetWizardButtons(PSWIZB_NEXT);  
	// �������Ա���һ��������һ������ť  
	psheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_NEXT); 
	return CPropertyPage::OnSetActive();
}
