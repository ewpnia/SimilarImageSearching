#pragma once


// SURFDialog1 �Ի���

class SURFDialog1 : public CPropertyPage
{
	DECLARE_DYNAMIC(SURFDialog1)

public:
	SURFDialog1();
	virtual ~SURFDialog1();

// �Ի�������
	enum { IDD = IDD_SURFDIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
};
