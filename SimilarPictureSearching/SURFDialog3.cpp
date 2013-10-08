// SURFDialog3.cpp : 实现文件
//

#include "stdafx.h"
#include "SimilarPictureSearching.h"
#include "SURFDialog3.h"
#include "afxdialogex.h"


// SURFDialog3 对话框

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


// SURFDialog3 消息处理程序


void SURFDialog3::OnEnChangeSurfeditbrowse2()
{
}


BOOL SURFDialog3::OnSetActive()
{
	// 获得父窗口，即属性表CPropertySheet类   
	CPropertySheet* psheet = (CPropertySheet*) GetParent();   
	// 设置属性表只有“下一步”按钮   
	//psheet->SetWizardButtons(PSWIZB_NEXT);  
	// 设置属性表“上一步”“下一步”按钮  
	psheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_NEXT); 

	return CPropertyPage::OnSetActive();
}
