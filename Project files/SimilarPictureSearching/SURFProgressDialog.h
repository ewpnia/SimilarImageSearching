#pragma once


// SURFProgressDialog 对话框

class SURFProgressDialog : public CDialogEx
{
	DECLARE_DYNAMIC(SURFProgressDialog)

public:
	SURFProgressDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~SURFProgressDialog();
	virtual BOOL OnInitDialog(void);

// 对话框数据
	enum { IDD = IDD_SURFPROGRESSD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	CProgressCtrl m_pro;
	int m_progessMax;
	int m_progessStep;

	void MyProgressStepLength(CString openDir);
	void MyProgressStep();
};
