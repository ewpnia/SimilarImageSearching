// SURFDialog4.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SimilarPictureSearching.h"
#include "SURFDialog4.h"
#include "afxdialogex.h"


// SURFDialog4 �Ի���

IMPLEMENT_DYNAMIC(SURFDialog4, CPropertyPage)

SURFDialog4::SURFDialog4()
	: CPropertyPage(SURFDialog4::IDD)
{

}

SURFDialog4::~SURFDialog4()
{
}

void SURFDialog4::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(SURFDialog4, CPropertyPage)
END_MESSAGE_MAP()


// SURFDialog4 ��Ϣ�������


BOOL SURFDialog4::OnSetActive()
{
	// ��ø����ڣ������Ա�CPropertySheet��   
	CPropertySheet* psheet = (CPropertySheet*) GetParent();   
	//�������Ա�ֻ�С���ɡ���ť   
	psheet->SetFinishText(_T("��ʼ"));   

	return CPropertyPage::OnSetActive();
}


BOOL SURFDialog4::OnWizardFinish()
{
	//MessageBox(_T("������ɣ�"));
	isFinish = 1;

	return CPropertyPage::OnWizardFinish();
}
