// SURFDialog4.cpp : 实现文件
//

#include "stdafx.h"
#include "SimilarPictureSearching.h"
#include "SURFDialog4.h"
#include "afxdialogex.h"


// SURFDialog4 对话框

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


// SURFDialog4 消息处理程序


BOOL SURFDialog4::OnSetActive()
{
	// 获得父窗口，即属性表CPropertySheet类   
	CPropertySheet* psheet = (CPropertySheet*) GetParent();   
	//设置属性表只有“完成”按钮   
	psheet->SetFinishText(_T("开始"));   

	return CPropertyPage::OnSetActive();
}


BOOL SURFDialog4::OnWizardFinish()
{
	//MessageBox(_T("向导已完成！"));
	isFinish = 1;

	return CPropertyPage::OnWizardFinish();
}
