#pragma once
#include "resource.h"


// ���������� ���� TCPForm
void thread_Proc2();
class TCPForm : public CDialog
{
	DECLARE_DYNAMIC(TCPForm)

public:
	TCPForm(CWnd* pParent = NULL);   // ����������� �����������
	void TCPForm::HideLabel();
	virtual ~TCPForm();

// ������ ����������� ����
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
};
