// SURFDialog1.cpp : 实现文件
//

#include "stdafx.h"
#include "SimilarPictureSearching.h"
#include "SURFDialog1.h"
#include "afxdialogex.h"


// SURFDialog1 对话框

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


// SURFDialog1 消息处理程序

BOOL SURFDialog1::OnSetActive()
{
	// 获得父窗口，即属性表CPropertySheet类   
	CPropertySheet* psheet = (CPropertySheet*) GetParent();   
	// 设置属性表只有“下一步”按钮   
	//psheet->SetWizardButtons(PSWIZB_NEXT);  
	// 设置属性表“上一步”“下一步”按钮  
	psheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_NEXT); 
	return CPropertyPage::OnSetActive();
}
