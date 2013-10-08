#pragma once


// SURFDialog1 对话框

class SURFDialog1 : public CPropertyPage
{
	DECLARE_DYNAMIC(SURFDialog1)

public:
	SURFDialog1();
	virtual ~SURFDialog1();

// 对话框数据
	enum { IDD = IDD_SURFDIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
};
