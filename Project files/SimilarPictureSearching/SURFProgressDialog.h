#pragma once


// SURFProgressDialog �Ի���

class SURFProgressDialog : public CDialogEx
{
	DECLARE_DYNAMIC(SURFProgressDialog)

public:
	SURFProgressDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~SURFProgressDialog();
	virtual BOOL OnInitDialog(void);

// �Ի�������
	enum { IDD = IDD_SURFPROGRESSD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	CProgressCtrl m_pro;
	int m_progessMax;
	int m_progessStep;

	void MyProgressStepLength(CString openDir);
	void MyProgressStep();
};
