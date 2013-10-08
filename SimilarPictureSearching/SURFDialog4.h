#pragma once


// SURFDialog4 对话框

class SURFDialog4 : public CPropertyPage
{
	DECLARE_DYNAMIC(SURFDialog4)

public:
	SURFDialog4();
	virtual ~SURFDialog4();

// 对话框数据
	enum { IDD = IDD_SURFDIALOG4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
	virtual BOOL OnWizardFinish();
	int isFinish;
};
