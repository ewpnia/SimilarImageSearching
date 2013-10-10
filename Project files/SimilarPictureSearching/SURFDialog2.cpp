// SURFDialog2.cpp : 实现文件
//

#include "stdafx.h"
#include "SimilarPictureSearching.h"
#include "SURFDialog2.h"
#include "afxdialogex.h"


// SURFDialog2 对话框

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


// SURFDialog2 消息处理程序


void SURFDialog2::OnEnChangeSurfeditbrowse1()
{
}

BOOL SURFDialog2::OnSetActive()
{
	// 获得父窗口，即属性表CPropertySheet类   
	CPropertySheet* psheet = (CPropertySheet*) GetParent();   
	// 设置属性表只有“下一步”按钮   
	//psheet->SetWizardButtons(PSWIZB_NEXT);  
	// 设置属性表“上一步”“下一步”按钮  
	psheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_NEXT); 

	return CPropertyPage::OnSetActive();
}
