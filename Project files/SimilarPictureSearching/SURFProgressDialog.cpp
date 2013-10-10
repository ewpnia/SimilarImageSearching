// SURFProgressDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "SimilarPictureSearching.h"
#include "SURFProgressDialog.h"
#include "afxdialogex.h"
#include "MyFunctions.h"


// SURFProgressDialog 对话框

IMPLEMENT_DYNAMIC(SURFProgressDialog, CDialogEx)

SURFProgressDialog::SURFProgressDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(SURFProgressDialog::IDD, pParent)
{

}

SURFProgressDialog::~SURFProgressDialog()
{
}

void SURFProgressDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SURFPROGRESS, m_pro);
}


BEGIN_MESSAGE_MAP(SURFProgressDialog, CDialogEx)
END_MESSAGE_MAP()


BOOL SURFProgressDialog::OnInitDialog(void)
{
	CDialogEx::OnInitDialog();
	m_pro.SetRange(0,10000);
	m_progessMax = 10000;

	return 0;
}

// SURFProgressDialog 消息处理程序

void SURFProgressDialog::MyProgressStepLength(CString openDir)
{
	m_progessStep = m_progessMax / (FileCount( openDir, L".jpg" ) );
	m_pro.SetStep(m_progessStep);
}

void SURFProgressDialog::MyProgressStep()
{
	if (m_progessStep > 0)
	{
		m_pro.StepIt();
	}	
}


