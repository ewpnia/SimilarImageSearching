#pragma once


// SURFDialog4 �Ի���

class SURFDialog4 : public CPropertyPage
{
	DECLARE_DYNAMIC(SURFDialog4)

public:
	SURFDialog4();
	virtual ~SURFDialog4();

// �Ի�������
	enum { IDD = IDD_SURFDIALOG4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
	virtual BOOL OnWizardFinish();
	int isFinish;
};
